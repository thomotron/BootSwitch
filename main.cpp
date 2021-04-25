#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define BOOT_PHRASE "Use the ^ and v keys to change the selection."
#define BOOT_PHRASE_LENGTH 45

#define START 0
#define STOP 1
#define BIT_WIDTH_US 104
#define BIT_WIDTH_HALF_US (BIT_WIDTH_US/2)

char data[BOOT_PHRASE_LENGTH];
int data_index = 0;

// Receives a byte from UART
char recv_byte()
{
    // Create a buffer to store the incoming byte in
    char recv_buf = 0;

    // Receive the next 8 bits
    for (char i = 0; i < 8; i++)
    {
        recv_buf >>= PINB0;
        _delay_us(BIT_WIDTH_US);
    }

    // Wait for the stop bit to pass by
    _delay_us(BIT_WIDTH_US);

    // Return the byte
    return recv_buf;
}

// Clears the data buffer
void clear_data()
{
    memset(data, 0, BOOT_PHRASE_LENGTH);
}

// Compares the phrase to the ring buffer
bool compare_phrase()
{
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
bool uart_ready()
{
    return PINB0 == START;
}

// Handle the boot response based on switch position
void handle_boot()
{
    // TODO: Sample switch position and send keystrokes
    return;
}

int main()
{
    while (true)
    {
        // Wait until there is data available
        while (!uart_ready());

        // Wait out the state change and confirm if it is the start bit
        _delay_us(BIT_WIDTH_HALF_US);
        if (uart_ready())
        {
            // Wait until the next bit is received and process the incoming byte
            _delay_us(BIT_WIDTH_US);
            char incoming = recv_byte();

            // Append the byte to the data array
            data[data_index] = incoming;
            data_index++;
            if (data_index == BOOT_PHRASE_LENGTH) data_index = 0;
        }

        // Compare the ring buffer to the boot phrase
        if (compare_phrase())
        {
            // Do the boot thing
            handle_boot();
        }
    }
}
