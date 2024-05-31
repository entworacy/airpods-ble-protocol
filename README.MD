# airpods-ble-protocol

This project provides a C implementation to decode the status of various Apple AirPods devices based on their BLE (Bluetooth Low Energy) status strings. The implementation decodes a BLE status string into a structured format, providing information such as battery status, charging status, and in-ear detection for left and right pods, as well as the case and single pod.

## Overview

The `decodePodsStatus` function decodes a BLE status string into a structured format. This function is helpful for parsing status information from AirPods and similar devices.

## File Structure

- `apple_ble_protocol.c`: Contains the implementation of the `decodePodsStatus` function and related helper functions.

## Functions

### `PodsStatus decodePodsStatus(char* status)`

This function decodes the given BLE status string into a `PodsStatus` structure.

- **Parameters:**
    - `status`: A string containing the BLE status information.

- **Returns:**
    - A `PodsStatus` structure containing the decoded information.

### `int hexCharToInt(char c)`

Converts a hexadecimal character to its integer value.

- **Parameters:**
    - `c`: A hexadecimal character.

- **Returns:**
    - The integer value of the hexadecimal character.

### `int isFlipped(char* str)`

Determines if the status string is flipped.

- **Parameters:**
    - `str`: The status string.

- **Returns:**
    - `1` if the string is flipped, `0` otherwise.

## Structs

### `Pod`

Represents the status of a single pod.

- **Fields:**
    - `int batteryStatus`: Battery level of the pod.
    - `int isCharging`: Charging status of the pod.
    - `int inEar`: In-ear detection status of the pod.

### `PodsStatus`

Represents the overall status of the AirPods or Beats device.

- **Fields:**
    - `Pod leftPod`: Status of the left pod.
    - `Pod rightPod`: Status of the right pod.
    - `Pod casePod`: Status of the case.
    - `Pod singlePod`: Status of a single pod.
    - `char model[20]`: Model of the device.
    - `long timestamp`: Timestamp of the status.

## Example Usage

```c
#include <stdio.h>
#include "apple_ble_protocol.h"

int main() {
    char status[] = "0220123456789ABCDEF";
    PodsStatus podsStatus = decodePodsStatus(status);
    
    printf("Model: %s\n", podsStatus.model);
    printf("Timestamp: %ld\n", podsStatus.timestamp);
    printf("Left Pod - Battery: %d, Charging: %d, In Ear: %d\n", 
            podsStatus.leftPod.batteryStatus, podsStatus.leftPod.isCharging, podsStatus.leftPod.inEar);
    printf("Right Pod - Battery: %d, Charging: %d, In Ear: %d\n", 
            podsStatus.rightPod.batteryStatus, podsStatus.rightPod.isCharging, podsStatus.rightPod.inEar);
    printf("Case - Battery: %d, Charging: %d\n", 
            podsStatus.casePod.batteryStatus, podsStatus.casePod.isCharging);
    printf("Single Pod - Battery: %d, Charging: %d\n", 
            podsStatus.singlePod.batteryStatus, podsStatus.singlePod.isCharging);

    return 0;
}
```

## Acknowledgments

This project was inspired by and references the [OpenPods](https://github.com/adolfintel/OpenPods) project by adolfintel.

## License

This project is licensed under the GPL License. See the LICENSE file for details.