#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "io_macros.h"

#define BOOT_PHRASE_LENGTH 45

#define TX_PIN B, 1
#define RX_PIN B, 0

#define SW_PIN B, 3

#define START 0
#define STOP 1
#define BIT_WIDTH_US 104
#define BIT_WIDTH_HALF_US (BIT_WIDTH_US/2)

void init();
char recv_byte();
void send_byte(char byte);
bool compare_phrase();
inline bool uart_ready();
void handle_boot();
int main();

char BOOT_PHRASE[] = "Use the ^ and v keys to change the selection.";

// Ring buffer to store the incoming data
char data[BOOT_PHRASE_LENGTH];
int data_index = 0;

// Initialises the microcontroller
void init()
{
    // Enable pullups
    MCUCR &= ~(1 << PUD);

    // Set pin directons
    PinMode(TX_PIN, OUTPUT);
    PinMode(RX_PIN, INPUT);
    PinMode(SW_PIN, INPUT);

    // Set initial pin states
    DigitalWrite(SW_PIN, HIGH); // Enable pullup
    DigitalWrite(TX_PIN, STOP);

    // Clear the data buffer
    memset(data, 0, BOOT_PHRASE_LENGTH);
}

// Receives a byte from UART
char recv_byte()
{
    // Create a buffer to store the incoming byte in
    char recv_buf = 0;

    // Receive the next 8 bits
    for (char i = 0b00000001; i > 0; i <<= 1)
    {
        if (DigitalRead(RX_PIN)) recv_buf |= i;
        _delay_us(BIT_WIDTH_US);
    }

    // Wait for the stop bit to pass by
    _delay_us(BIT_WIDTH_US);

    // Return the byte
    return recv_buf;
}

// Transmits a single byte over UART
void send_byte(char byte)
{
    // Send the start bit
    DigitalWrite(TX_PIN, START);
    _delay_us(BIT_WIDTH_US);

    // Send each bit LSB-first
    for (char i = 0b00000001; i > 0; i <<= 1)
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
    do
    {
        if (BOOT_PHRASE[i] != data[i]) return false;

        // Increment iterator and wrap around if necessary
        i++;
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
}

int main()
{
    init();

    while (true)
    {
        // Wait until there is data available
        while (!uart_ready());

        // Synchronise to the middle of the clock cycle and confirm if it is still the start bit
        _delay_us(BIT_WIDTH_HALF_US);
        if (!uart_ready()) continue; // Not the start bit, go back

        // Wait until the next bit is received and process the incoming byte
        _delay_us(BIT_WIDTH_US);
        char incoming = recv_byte();

        // Append the byte to the data array
        data[data_index] = incoming;
        data_index++;
        if (data_index == BOOT_PHRASE_LENGTH) data_index = 0;

        // Compare the ring buffer to the boot phrase
        if (compare_phrase())
        {
            // Make a boot selection
            handle_boot();
        }
    }
}
