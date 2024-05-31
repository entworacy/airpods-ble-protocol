cmake_minimum_required(VERSION 3.26)
project(airpods-ble-protocol C)

set(CMAKE_C_STANDARD 11)

add_library(airpods-ble-protocol SHARED apple_ble_protocol.c)
