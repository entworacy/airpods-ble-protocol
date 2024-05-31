#include "apple_ble_protocol.h"

/**
 * Converts a hexadecimal character to its integer value.
 *
 * @param c A hexadecimal character.
 * @return The integer value of the hexadecimal character.
 */
int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    }
    return -1;
}

/**
 * Determines if the status string is flipped.
 *
 * The flipping of the status string affects the interpretation of certain bits in the string.
 *
 * @param str The status string.
 * @return 1 if the string is flipped, 0 otherwise.
 */
int isFlipped(char* str) {
    return (hexCharToInt(str[10]) & 0x02) == 0;
}

/**
 * Decodes the given BLE status string into a PodsStatus structure.
 *
 * This function parses the status string to extract information such as battery levels,
 * charging status, and in-ear detection for left and right pods, as well as the case and single pod.
 * It also identifies the model of the device based on the string.
 *
 * @param status A string containing the BLE status information.
 * @return A PodsStatus structure containing the decoded information.
 */
PodsStatus decodePodsStatus(char* status) {
    PodsStatus podsStatus;
    podsStatus.timestamp = time(NULL); // Set the current timestamp

    // Handle the case where the status is NULL (disconnected state)
    if (status == NULL) {
        strcpy(podsStatus.model, "DISCONNECTED");
        return podsStatus;
    }

    int flip = isFlipped(status); // Determine if the status string is flipped

    // Extract battery status for left, right, case, and single pod
    int leftStatus = hexCharToInt(status[flip ? 12 : 13]);
    int rightStatus = hexCharToInt(status[flip ? 13 : 12]);
    int caseStatus = hexCharToInt(status[15]);
    int singleStatus = hexCharToInt(status[13]);

    // Extract charging status
    int chargeStatus = hexCharToInt(status[14]);
    int chargeL = (chargeStatus & (flip ? 0b00000010 : 0b00000001)) != 0;
    int chargeR = (chargeStatus & (flip ? 0b00000001 : 0b00000010)) != 0;
    int chargeCase = (chargeStatus & 0b00000100) != 0;
    int chargeSingle = (chargeStatus & 0b00000001) != 0;

    // Extract in-ear detection status
    int inEarStatus = hexCharToInt(status[11]);
    int inEarL = (inEarStatus & (flip ? 0b00001000 : 0b00000010)) != 0;
    int inEarR = (inEarStatus & (flip ? 0b00000010 : 0b00001000)) != 0;

    // Populate the PodsStatus structure with the extracted values
    podsStatus.leftPod.batteryStatus = leftStatus;
    podsStatus.leftPod.isCharging = chargeL;
    podsStatus.leftPod.inEar = inEarL;

    podsStatus.rightPod.batteryStatus = rightStatus;
    podsStatus.rightPod.isCharging = chargeR;
    podsStatus.rightPod.inEar = inEarR;

    podsStatus.casePod.batteryStatus = caseStatus;
    podsStatus.casePod.isCharging = chargeCase;
    podsStatus.casePod.inEar = 0;

    podsStatus.singlePod.batteryStatus = singleStatus;
    podsStatus.singlePod.isCharging = chargeSingle;
    podsStatus.singlePod.inEar = 0;

    // Identify the model based on the status string
    char idSingle = status[7];
    char idFull[5];
    strncpy(idFull, status + 6, 4);
    idFull[4] = '\0';

    if (strcmp(idFull, "0220") == 0) {
        strcpy(podsStatus.model, "AirPods1");
    } else if (strcmp(idFull, "0F20") == 0) {
        strcpy(podsStatus.model, "AirPods2");
    } else if (strcmp(idFull, "1320") == 0) {
        strcpy(podsStatus.model, "AirPods3");
    } else if (strcmp(idFull, "0E20") == 0) {
        strcpy(podsStatus.model, "AirPodsPro");
    } else if (strcmp(idFull, "1420") == 0 || strcmp(idFull, "2420") == 0) {
        strcpy(podsStatus.model, "AirPodsPro2");
    } else if (idSingle == 'A') {
        strcpy(podsStatus.model, "AirPodsMax");
    } else {
        strcpy(podsStatus.model, "RegularPods");
    }

    return podsStatus;
}
