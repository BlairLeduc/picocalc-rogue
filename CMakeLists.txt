# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pimoroni_pico_plus2_w_rp2350 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picocalc-rogue C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(picocalc-rogue
    modules/PDCurses/pdcurses/addch.c
    modules/PDCurses/pdcurses/addchstr.c
    modules/PDCurses/pdcurses/addstr.c
    modules/PDCurses/pdcurses/attr.c
    modules/PDCurses/pdcurses/beep.c
    modules/PDCurses/pdcurses/bkgd.c
    modules/PDCurses/pdcurses/border.c
    modules/PDCurses/pdcurses/clear.c
    modules/PDCurses/pdcurses/color.c
    modules/PDCurses/pdcurses/debug.c
    modules/PDCurses/pdcurses/delch.c
    modules/PDCurses/pdcurses/deleteln.c
    modules/PDCurses/pdcurses/getch.c
    modules/PDCurses/pdcurses/getstr.c
    modules/PDCurses/pdcurses/getyx.c
    modules/PDCurses/pdcurses/inch.c
    modules/PDCurses/pdcurses/inchstr.c
    modules/PDCurses/pdcurses/initscr.c
    modules/PDCurses/pdcurses/inopts.c
    modules/PDCurses/pdcurses/insch.c
    modules/PDCurses/pdcurses/insstr.c
    modules/PDCurses/pdcurses/instr.c
    modules/PDCurses/pdcurses/kernel.c
    modules/PDCurses/pdcurses/keyname.c
    modules/PDCurses/pdcurses/mouse.c
    modules/PDCurses/pdcurses/move.c
    modules/PDCurses/pdcurses/outopts.c
    modules/PDCurses/pdcurses/overlay.c
    modules/PDCurses/pdcurses/pad.c
    modules/PDCurses/pdcurses/panel.c
    modules/PDCurses/pdcurses/printw.c
    modules/PDCurses/pdcurses/refresh.c
    modules/PDCurses/pdcurses/scanw.c
    modules/PDCurses/pdcurses/scr_dump.c
    modules/PDCurses/pdcurses/scroll.c
    modules/PDCurses/pdcurses/slk.c
    modules/PDCurses/pdcurses/termattr.c
    modules/PDCurses/pdcurses/touch.c
    modules/PDCurses/pdcurses/util.c
    modules/PDCurses/pdcurses/window.c
    modules/picocalc-text-starter/drivers/audio.c
    modules/picocalc-text-starter/drivers/clib.c
    modules/picocalc-text-starter/drivers/fat32.c
    modules/picocalc-text-starter/drivers/font-5x10.c
    modules/picocalc-text-starter/drivers/font-8x10.c
    modules/picocalc-text-starter/drivers/lcd.c
    modules/picocalc-text-starter/drivers/sdcard.c
    modules/picocalc-text-starter/drivers/southbridge.c
    modules/rogue/armor.c
    modules/rogue/chase.c
    modules/rogue/command.c
    modules/rogue/daemon.c
    modules/rogue/daemons.c
    rogue/extern.c
    modules/rogue/fight.c
    modules/rogue/init.c
    rogue/io.c
    modules/rogue/list.c
    modules/rogue/mach_dep.c
    rogue/main.c
    modules/rogue/mdport.c
    modules/rogue/misc.c
    modules/rogue/monsters.c
    modules/rogue/move.c
    modules/rogue/new_level.c
    modules/rogue/options.c
    modules/rogue/pack.c
    modules/rogue/passages.c
    modules/rogue/potions.c
    modules/rogue/rings.c
    modules/rogue/rip.c
    modules/rogue/rooms.c
    modules/rogue/save.c
    modules/rogue/scrolls.c
    modules/rogue/state.c
    modules/rogue/sticks.c
    modules/rogue/things.c
    modules/rogue/vers.c
    modules/rogue/weapons.c
    modules/rogue/wizard.c
    modules/rogue/xcrypt.c
    picocalc/pdcclip.c
    picocalc/pdcdisp.c
    picocalc/pdcgetsc.c
    picocalc/pdckbd.c
    picocalc/pdcscrn.c
    picocalc/pdcsetsc.c
    picocalc/pdcutil.c
    )

pico_set_program_name(picocalc-rogue "picocalc-rogue")
pico_set_program_version(picocalc-rogue "0.1")

# Generate PIO header
pico_generate_pio_header(picocalc-rogue ${CMAKE_CURRENT_LIST_DIR}/modules/picocalc-text-starter/drivers/audio.pio)

target_compile_definitions(picocalc-rogue PUBLIC
    HAVE_CONFIG_H=1
    )

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(picocalc-rogue 0)
pico_enable_stdio_usb(picocalc-rogue 0)

# Add the standard library to the build
target_link_libraries(picocalc-rogue
    pico_stdlib
    pico_printf
    pico_rand
    pico_bootrom
    hardware_gpio
    hardware_i2c
    hardware_spi
    hardware_pio
    hardware_clocks)

# Add the standard include files to the build
target_include_directories(picocalc-rogue PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/rogue
    ${CMAKE_CURRENT_LIST_DIR}/modules/PDCurses
    ${CMAKE_CURRENT_LIST_DIR}/modules/picocalc-text-starter
    ${CMAKE_CURRENT_LIST_DIR}/modules/rogue
    ${CMAKE_CURRENT_LIST_DIR}/picocalc
)

pico_add_extra_outputs(picocalc-rogue)

