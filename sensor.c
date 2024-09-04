#include "sensor.h"
#include <stdio.h>
#include "stm32f4xx_hal.h" // Include the HAL for STM32

#define TRIG_PIN GPIO_PIN_0
#define ECHO_PIN GPIO_PIN_1
#define SENSOR_PORT GPIOA

void Sensor_Init(void) {
    // Initialize GPIO pins for the ultrasonic sensor (TRIG and ECHO)
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure TRIG pin
    GPIO_InitStruct.Pin = TRIG_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);

    // Configure ECHO pin
    GPIO_InitStruct.Pin = ECHO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);
}

int Sensor_Read(void) {
    // Send a 10us pulse to the TRIG pin
    HAL_GPIO_WritePin(SENSOR_PORT, TRIG_PIN, GPIO_PIN_SET);
    HAL_Delay(1);  // Delay 1 ms for the signal to stabilize
    HAL_GPIO_WritePin(SENSOR_PORT, TRIG_PIN, GPIO_PIN_RESET);

    // Measure the ECHO pulse width to determine distance
    uint32_t start_time = HAL_GetTick();  // Start timing
    while (HAL_GPIO_ReadPin(SENSOR_PORT, ECHO_PIN) == GPIO_PIN_RESET);  // Wait for ECHO to go HIGH

    uint32_t echo_start = HAL_GetTick();  // Record when the pulse starts
    while (HAL_GPIO_ReadPin(SENSOR_PORT, ECHO_PIN) == GPIO_PIN_SET);    // Wait for ECHO to go LOW

    uint32_t echo_end = HAL_GetTick();  // Record when the pulse ends

    uint32_t echo_duration = echo_end - echo_start;
    int distance = echo_duration * 0.034 / 2;  // Convert time to distance

    // If distance is less than a threshold (e.g., 30cm), parking spot is occupied
    if (distance < 30) {
        printf("Parking spot occupied\n");
        return 1;  // Occupied
    } else {
        printf("Parking spot free\n");
        return 0;  // Free
    }
}
