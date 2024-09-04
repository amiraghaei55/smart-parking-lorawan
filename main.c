#include "lorawan.h"
#include "sensor.h"
#include <stdio.h>

int main(void) {
    // Initialize LoRaWAN and sensor
    LoRaWAN_Init();
    Sensor_Init();

    int parking_status = 0;  // 0 = free, 1 = occupied

    while (1) {
        // Read the sensor data
        parking_status = Sensor_Read();

        // Send the parking status over LoRaWAN
        LoRaWAN_Send(parking_status);

        // Delay before next read (adjust as per your requirements)
        HAL_Delay(5000);  // 5 seconds
    }

    return 0;
}
