#include "pdcpicocalc.h"

int PDC_getclipboard(char **contents, long *length)
{
    PDC_LOG(("PDC_getclipboard() - called\n"));

    return PDC_CLIP_EMPTY;
}

int PDC_setclipboard(const char *contents, long length)
{
    PDC_LOG(("PDC_setclipboard() - called\n"));

    return PDC_CLIP_SUCCESS;
}

int PDC_freeclipboard(char *contents)
{
    PDC_LOG(("PDC_freeclipboard() - called\n"));

    return PDC_CLIP_SUCCESS;
}

int PDC_clearclipboard(void)
{
    PDC_LOG(("PDC_clearclipboard() - called\n"));

    return PDC_CLIP_SUCCESS;
}