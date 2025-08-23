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
file(GLOB PDCURSES_SOURCES CONFIGURE_DEPENDS
    modules/PDCurses/pdcurses/*.c
)

set(STARTER_KIT_SOURCES
    modules/picocalc-text-starter/drivers/audio.c
    modules/picocalc-text-starter/drivers/clib.c
    modules/picocalc-text-starter/drivers/fat32.c
    modules/picocalc-text-starter/drivers/font-5x10.c
    modules/picocalc-text-starter/drivers/font-8x10.c
    modules/picocalc-text-starter/drivers/lcd.c
    modules/picocalc-text-starter/drivers/sdcard.c
    modules/picocalc-text-starter/drivers/southbridge.c
)

file(GLOB PICOCALC_SOURCES CONFIGURE_DEPENDS
    picocalc/*.c
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/rogue/.patched
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_CURRENT_LIST_DIR}/rogue
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_LIST_DIR}/modules/rogue
            ${CMAKE_CURRENT_LIST_DIR}/rogue
    COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/scripts/apply_patches.sh
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_LIST_DIR}/rogue/.patched
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/patches/rogue.patch
            ${CMAKE_CURRENT_LIST_DIR}/scripts/apply_patches.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Copying and patching rogue sources"
    VERBATIM
)

add_custom_target(patch_rogue ALL
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/rogue/.patched
)

file(GLOB ROGUE_SOURCES CONFIGURE_DEPENDS
    rogue/*.c
)

add_executable(picocalc-rogue
    ${PDCURSES_SOURCES}
    ${STARTER_KIT_SOURCES}
    ${PICOCALC_SOURCES}
    ${ROGUE_SOURCES}
    main.c
    )

add_dependencies(picocalc-rogue patch_rogue)

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
    ${CMAKE_CURRENT_LIST_DIR}/picocalc
)

pico_add_extra_outputs(picocalc-rogue)
