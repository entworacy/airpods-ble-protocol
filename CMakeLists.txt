cmake_minimum_required(VERSION 3.26)
project(airpods-ble-protocol C)

set(CMAKE_C_STANDARD 11)

add_library(airpods-ble-protocol SHARED apple_ble_protocol.c)

set_target_properties(airpods-ble-protocol PROPERTIES
        PUBLIC_HEADER apple_ble_protocol.h
        OUTPUT_NAME "apple_ble_protocol"
)

install(TARGETS airpods-ble-protocol
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)