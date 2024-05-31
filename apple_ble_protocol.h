#ifndef AIRPODS_BLE_PROTOCOL_APPLE_BLE_PROTOCOL_H
#define AIRPODS_BLE_PROTOCOL_APPLE_BLE_PROTOCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int batteryStatus;
    int isCharging;
    int inEar;
} Pod;

typedef struct {
    Pod leftPod;
    Pod rightPod;
    Pod casePod;
    Pod singlePod;
    char model[20];
    long timestamp;
} PodsStatus;

/**
 * Converts a hexadecimal character to its integer value.
 *
 * @param c A hexadecimal character.
 * @return The integer value of the hexadecimal character.
 */
int hexCharToInt(char c);

/**
 * Determines if the status string is flipped.
 *
 * @param str The status string.
 * @return 1 if the string is flipped, 0 otherwise.
 */
int isFlipped(char* str);

/**
 * Decodes the given BLE status string into a PodsStatus structure.
 *
 * @param status A string containing the BLE status information.
 * @return A PodsStatus structure containing the decoded information.
 */
PodsStatus decodePodsStatus(char* status);

#endif //AIRPODS_BLE_PROTOCOL_APPLE_BLE_PROTOCOL_H
