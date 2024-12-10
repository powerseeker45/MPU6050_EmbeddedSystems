/*
 * mpu6050.h
 *
 *  Created on: Dec 10, 2024
 *      Author: shash
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32h7xx_hal.h"

// MPU6050 I2C Address
#define MPU6050_ADDRESS 0x68 << 1 // Left shift for HAL compatibility

// MPU6050 Registers
#define MPU6050_REG_PWR_MGMT_1   0x6B
#define MPU6050_REG_ACCEL_XOUT_H 0x3B
#define MPU6050_REG_GYRO_XOUT_H  0x43
#define MPU6050_REG_TEMP_OUT_H   0x41
#define MPU6050_REG_WHO_AM_I     0x75

// MPU6050 Initialization
void MPU6050_Init(I2C_HandleTypeDef *hi2c);

// MPU6050 Data Retrieval
HAL_StatusTypeDef MPU6050_ReadAccelerometer(I2C_HandleTypeDef *hi2c, int16_t *accelX, int16_t *accelY, int16_t *accelZ);
HAL_StatusTypeDef MPU6050_ReadGyroscope(I2C_HandleTypeDef *hi2c, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ);
HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c, int16_t *temp);
HAL_StatusTypeDef MPU6050_ReadAllData(I2C_HandleTypeDef *hi2c, int16_t *accel, int16_t *gyro, int16_t *temp);



#endif /* INC_MPU6050_H_ */
