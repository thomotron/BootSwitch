#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

#include "io_macros.h"

//#define DEBUG

#define TX_PIN B, 1
#define RX_PIN B, 0

#define SW_PIN B, 3

#define START LOW
#define STOP HIGH
#define BIT_WIDTH_US 104
#define BIT_WIDTH_HALF_US (BIT_WIDTH_US/2)

void init();
unsigned char recv_byte();
void send_byte(unsigned char byte);
bool compare_phrase();
inline bool uart_ready();
void handle_boot();
void data_append(char byte);
int main();

const unsigned char BOOT_PHRASE[] = "the ^ and v keys";
#define BOOT_PHRASE_LENGTH 16

// Ring buffer to store the incoming data
char data[BOOT_PHRASE_LENGTH];
int data_index = 0;

// Whether a byte has been received and is ready to be processed
volatile bool byte_received = false;

// The incoming byte
volatile unsigned char incoming_byte = 0;

// Pin change interrupt
ISR(PCINT0_vect)
{
    // Only handle the start bit
    if (!uart_ready()) return;

    // Synchronise to the middle of the bit and jump to the first data bit
    _delay_us(BIT_WIDTH_HALF_US);
    _delay_us(BIT_WIDTH_US);

    // Read in the byte
    incoming_byte = recv_byte();

    // Signal that a byte was received
    byte_received = true;
}

// Initialises the microcontroller
void init()
{
    cli();

    // Enable pullups
    MCUCR &= ~(1 << PUD);

    // Enable pin change interrupt for the RX pin
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << PCINT0);

    // Set pin directons
    PinMode(TX_PIN, OUTPUT);
    PinMode(RX_PIN, INPUT);
    PinMode(SW_PIN, INPUT);

    // Set initial pin states
    DigitalWrite(SW_PIN, HIGH); // Enable pullup
    DigitalWrite(TX_PIN, STOP);

    // Clear the data buffer
    memset(data, 0, BOOT_PHRASE_LENGTH);

    sei();
}

// Receives a byte from UART
unsigned char recv_byte()
{
    // Create a buffer to store the incoming byte in
    unsigned char recv_buf = 0;

    // Receive the next 8 bits
    for (unsigned char i = 0b00000001; i > 0; i <<= 1)
    {
        if (DigitalRead(RX_PIN)) recv_buf |= i;
        _delay_us(BIT_WIDTH_US);
    }

    // Wait for the stop bit to pass by
    //_delay_us(BIT_WIDTH_US);

    // Return the byte
    return recv_buf;
}

// Transmits a single byte over UART
void send_byte(unsigned char byte)
{
    // Send the start bit
    DigitalWrite(TX_PIN, START);
    _delay_us(BIT_WIDTH_US);

    // Send each bit LSB-first
    for (unsigned char i = 0b00000001; i > 0; i <<= 1)
    {
        DigitalWrite(TX_PIN, (byte & i));
        _delay_us(BIT_WIDTH_US);
    }

    // Send the stop bit
    DigitalWrite(TX_PIN, STOP);
    _delay_us(BIT_WIDTH_US);
}

// Compares the phrase to the ring buffer
bool compare_phrase()
{
    // Start at the data index, wrap around, and stop just before it
    int i = data_index;
    int j = 0;
    do
    {
        if (BOOT_PHRASE[j] != data[i]) return false;

        // Increment iterator and wrap around if necessary
        i++; j++;
        if (i == BOOT_PHRASE_LENGTH) i = 0;
    } while (i != data_index);

    return true;
}

// Checks whether the UART line is ready to send
inline bool uart_ready()
{
    return DigitalRead(RX_PIN) == START;
}

// Handle the boot response based on switch position
void handle_boot()
{
    // Disable interrupts while transmitting
    cli();

    if (DigitalRead(SW_PIN))
    {
        // Switch on, boot into Windows
        send_byte(0x76); // v
        send_byte(0x76); // v
        send_byte(0x76); // v
        send_byte(0x0D); // CR
    }
    else
    {
        // Switch off, boot into Linux
        send_byte(0x0D); // CR
    }

    // Re-enable interrupts
    sei();
}

// Appends a character to the data buffer
void data_append(char byte)
{
    // Data index is the current WRITE POSITION which will be overwritten on the next byte.
    // It is effectively at the head of the buffer, with the tail being one position behind it

    // Append the byte and advance the index
    data[data_index] = byte;
    data_index++;

    // Wrap around if necessary
    if (data_index == BOOT_PHRASE_LENGTH) data_index = 0;
}

int main()
{
    init();

    while (true)
    {
        // Wait until there is data available
        while (!byte_received);

        // Processing now, clear the flag
        byte_received = false;

        // Append the byte to the buffer
        data_append(incoming_byte);

        // Compare the ring buffer to the boot phrase
        if (compare_phrase())
        {
            // Make a boot selection
            handle_boot();
        }

#ifdef DEBUG
        // Print the current contents of the ring buffer
        for (int i = 0; i < BOOT_PHRASE_LENGTH; i++)
        {
            send_byte(data[i]);
        }
        send_byte('\r');
        send_byte('\n');
        // and a caret under the position of data_index
        for (int i = 0; i < data_index; i++)
        {
            send_byte(' ');
        }
        if (compare_phrase()) send_byte('!');
        else send_byte('^');
        send_byte('\r');
        send_byte('\n');
#endif
    }
}
