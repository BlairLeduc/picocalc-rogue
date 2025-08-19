#include "pdcpicocalc.h"
#include <drivers/southbridge.h>

// Modifier key states
static bool key_control = false; // control key state
static bool key_shift = false;   // shift key state

static volatile char rx_buffer[KBD_BUFFER_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;
static volatile bool flush = false;
static repeating_timer_t key_timer;

static struct
{
    uint8_t keycode;
    unsigned short normal;
    unsigned short shifted;
    unsigned short control;
    unsigned short alt;
} key_table[] =
    {
        /* keycode          normal         shifted       control      alt*/
        {PC_KEY_LEFT, 'h', 'H', CTL_LEFT, ALT_LEFT},
        {PC_KEY_RIGHT, 'l', 'L', CTL_RIGHT, ALT_RIGHT},
        {PC_KEY_UP, 'k', 'K', CTL_UP, ALT_UP},
        {PC_KEY_DOWN, 'j', 'J', CTL_DOWN, ALT_DOWN},
        {PC_KEY_HOME, KEY_HOME, KEY_SHOME, CTL_HOME, ALT_HOME},
        {PC_KEY_BREAK, KEY_BREAK, 0, 0, 0},
        {PC_KEY_BACKSPACE, KEY_BACKSPACE, 0, 0, 0},
        {PC_KEY_F1, KEY_F(1), 0, 0, 0},
        {PC_KEY_F2, KEY_F(2), 0, 0, 0},
        {PC_KEY_F3, KEY_F(3), 0, 0, 0},
        {PC_KEY_F4, KEY_F(4), 0, 0, 0},
        {PC_KEY_F5, KEY_F(5), 0, 0, 0},
        {PC_KEY_F6, KEY_F(6), 0, 0, 0},
        {PC_KEY_F7, KEY_F(7), 0, 0, 0},
        {PC_KEY_F8, KEY_F(8), 0, 0, 0},
        {PC_KEY_F9, KEY_F(9), 0, 0, 0},
        {PC_KEY_F10, KEY_F(10), 0, 0, 0},
        {PC_KEY_DEL, KEY_DC, 0, 0, 0},
        {PC_KEY_RETURN, KEY_ENTER, 0, 0, 0},
        {PC_KEY_ESC, 0x1b, 0, 0, 0}};

static char _lookup_key(int keycode, bool shifted, bool control, bool alt)
{
    for (size_t i = 0; i < sizeof(key_table) / sizeof(key_table[0]); i++)
    {
        if (key_table[i].keycode == keycode)
        {
            if (shifted)
                return key_table[i].shifted;
            if (control)
                return key_table[i].control;
            if (alt)
                return key_table[i].alt;
            return key_table[i].normal;
        }
    }
    return 0;
}

static bool on_keyboard_timer(repeating_timer_t *rt)
{
    uint16_t key = 0;
    uint8_t key_state = 0;
    uint8_t key_code = 0;

    if (flush)
    {
        flush = false;     // reset flush flag
        rx_head = rx_tail; // discard any buffered key events
    }

    if (!sb_available())
    {
        return true; // if SPI is not available, skip this timer tick
    }

    // Repeat this loop until we exhaust the FIFO on the "south bridge".
    do
    {
        key = sb_read_keyboard();
        key_state = (key >> 8) & 0xFF;
        key_code = key & 0xFF;

        if (key_state != 0)
        {
            if (key_state == PC_KEY_STATE_PRESSED)
            {
                if (key_code == PC_KEY_MOD_CTRL)
                {
                    key_control = true;
                }
                else if (key_code == PC_KEY_MOD_SHL || key_code == PC_KEY_MOD_SHR)
                {
                    key_shift = true;
                }
                else
                {
                    uint8_t ch = key_code;

                    // If a key is released, we return the key code
                    char new_ch = _lookup_key(key_code, key_shift, key_control, false);
                    if (new_ch)
                    {
                        ch = new_ch;
                    }
                    else if (ch >= 'a' && ch <= 'z') // Ctrl and Shift handling
                    {
                        if (key_control)
                        {
                            ch &= 0x1F; // convert to control character
                        }
                        if (key_shift)
                        {
                            ch &= ~0x20;
                        }
                    }

                    uint16_t next_head = (rx_head + 1) & (KBD_BUFFER_SIZE - 1);
                    rx_buffer[rx_head] = ch;
                    rx_head = next_head;
                }

                continue;
            }

            if (key_state == PC_KEY_STATE_RELEASED)
            {
                if (key_code == PC_KEY_MOD_CTRL)
                {
                    key_control = false;
                }
                else if (key_code == PC_KEY_MOD_SHL || key_code == PC_KEY_MOD_SHR)
                {
                    key_shift = false;
                }
            }
        }
    } while (key_state != 0);

    return true; // continue the timer
}

void PDC_set_keyboard_binary(bool on)
{
    PDC_LOG(("PDC_set_keyboard_binary() - called\n"));

    // poll every 100 ms for key events
    add_repeating_timer_ms(100, on_keyboard_timer, NULL, &key_timer);
}

bool PDC_check_key(void)
{
    return rx_head != rx_tail && !flush;
}

int PDC_get_key(void)
{
    while (!PDC_check_key())
    {
        tight_loop_contents();
    }

    char ch = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) & (KBD_BUFFER_SIZE - 1);
    return ch;
}

void PDC_flushinp(void)
{
    PDC_LOG(("PDC_flushinp() - called\n"));

    flush = true;
}

bool PDC_has_mouse(void)
{
    return FALSE;
}

int PDC_mouse_set(void)
{
    return OK;
}

int PDC_modifiers_set(void)
{
    return OK;
}
