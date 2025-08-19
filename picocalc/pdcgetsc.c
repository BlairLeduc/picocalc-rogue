#include "pdcpicocalc.h"

uint16_t cols = 64;
uint16_t rows = 32;

int PDC_get_columns(void)
{
    return cols;
}

int PDC_get_cursor_mode(void)
{
    return lcd_cursor_enabled() ? 1 : 0;
}

int PDC_get_rows(void)
{
    return rows;
}