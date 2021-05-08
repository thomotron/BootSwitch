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
inline void start_timer();
inline void stop_timer();
inline bool timer_running();
int main();

const unsigned char BOOT_PHRASE[] = "the ^ and v keys";
#define BOOT_PHRASE_LENGTH 16

// Ring buffer to store the incoming data
char data[BOOT_PHRASE_LENGTH];
int data_index = 0;

// Mask used by the timer for assembling an incoming byte
char timer_incoming_mask = 0b00000001;

// Incoming byte being built by the timer
char timer_incoming_byte = 0;

// Timer0A interrupt
ISR(TIM0_COMPA_vect)
{
    // AND the RX pin against the mask and OR it against the incoming byte buffer
    timer_incoming_byte |= (DigitalRead(RX_PIN) & timer_incoming_mask);

    // Shift the mask across one
    timer_incoming_mask <<= 1;

    // Stop the timer if the last bit has been read and the mask has shifted to zero
    if (timer_incoming_mask == 0)
    {
        // Append the byte that's been built and disable the timer
        data_append(timer_incoming_byte);
        stop_timer();

        // Reset the byte and mask for the next run
        timer_incoming_byte = 0;
        timer_incoming_mask = 0b00000001;
    }
}

// Initialises the microcontroller
void init()
{
    // Enable pullups
    MCUCR &= ~(1 << PUD);

    // Set up Timer0
    TCCR0A |= (1 << WGM01); // Count up to OCR0A and reset (CTC mode)
    //TCCR0B |= (1 << CS01);  // Prescale by /8
    OCR0A = 104; // Count up to 104 before resetting, ~9615 Hz @ 8MHz clock with /8 prescaler
    TIMSK |= (1 << OCIE0A); // Enable interrupt on OCR0A

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

// Appends a character to the data buffer
void data_append(char byte)
{
    // Data index is the current WRITE POSITION which will be overwritten on the next byte.
    // It is effectively at the head of the buffer, with the tail being one position behind it

    data[data_index] = byte;
    data_index++;
    if (data_index == BOOT_PHRASE_LENGTH) data_index = 0;
}

// Starts Timer0
inline void start_timer()
{
    TCCR0B |= (1 << CS01);
}

// Stops Timer0
inline void stop_timer()
{
    TCCR0B &= ~(1 << CS01);
}

// Returns if Timer0 is running
inline bool timer_running()
{
    return TCCR0B & 0b00000111;
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

        // Start the timer and wait until it stops itself
        start_timer();
        while (timer_running());

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
