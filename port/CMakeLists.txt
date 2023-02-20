# ioLibrary_Driver
add_library(IOLIBRARY_FILES STATIC)

target_sources(IOLIBRARY_FILES PUBLIC
        ${PORT_DIR}/ioLibrary_Driver/src/w5x00_spi.c
        ${PORT_DIR}/ioLibrary_Driver/src/w5x00_gpio_irq.c
        )

target_include_directories(IOLIBRARY_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${PORT_DIR}/ioLibrary_Driver/inc
        ${PORT_DIR}
        )

target_link_libraries(IOLIBRARY_FILES PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        hardware_clocks
        )

# timer
add_library(TIMER_FILES STATIC)

target_sources(TIMER_FILES PUBLIC
        ${PORT_DIR}/timer/timer.c
        )

target_include_directories(TIMER_FILES PUBLIC
        ${PORT_DIR}/timer
        )

target_link_libraries(TIMER_FILES PRIVATE
        pico_stdlib      
        )

# aws-iot-device-sdk-embedded-C
add_library(AWS_SDK_PORT_FILES STATIC)

target_sources(AWS_SDK_PORT_FILES PUBLIC
        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/src/dns_interface.c
#        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/src/http_transport_interface.c
        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/src/mqtt_transport_interface.c
        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/src/ssl_transport_interface.c
        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/src/timer_interface.c
        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/src/util.c
        )

target_include_directories(AWS_SDK_PORT_FILES PUBLIC
        ${PORT_DIR}/aws-iot-device-sdk-embedded-C/inc
        ${AWS_SDK_DIR}/libraries/3rdparty/mbedtls/include
        )

target_link_libraries(AWS_SDK_PORT_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        DHCP_FILES
        DNS_FILES
        AWS_SDK_FILES
        mbedcrypto
        mbedx509s
        mbedtls
        )
add_library(tinycbor
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborpretty.c"
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborpretty_stdio.c"
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborencoder.c"
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.c"
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborerrorstrings.c"
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborparser.c"
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src/cborparser_dup_string.c"
)

#set_target_properties(tinycbor PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#    POSITION_INDEPENDENT_CODE ON
#)

# Use C99 for tinycbor as it is incompatible with C90
if(CMAKE_C_STANDARD LESS 99)
    set_target_properties(tinycbor PROPERTIES C_STANDARD 99)
endif()

target_include_directories(tinycbor PUBLIC
    "${AWS_SDK_DIR}/libraries/3rdparty/tinycbor/src"
)
