#include "pdcpicocalc.h"
#include <pico/stdlib.h>
#include <sys/types.h>
#include <pwd.h>

void PDC_beep(void)
{
    audio_play_sound_blocking(PITCH_A5, PITCH_A5, NOTE_EIGHTH);
}

const char *PDC_sysname(void)
{
    return "PicoCalc";
}

void PDC_napms(int ms)
{
    sleep_ms(ms);
}


int getuid()
{
    return 0;
}

struct passwd *getpwuid(uid_t uid)
{
    static struct passwd pw;
    pw.pw_name = "player";
    pw.pw_uid = 0;
    pw.pw_gid = 0;
    pw.pw_dir = "/Rogue";
    pw.pw_shell = "/bin/sh";
    return &pw;
}

void chmod(const char *path, mode_t mode)
{
    // No-op implementation
}