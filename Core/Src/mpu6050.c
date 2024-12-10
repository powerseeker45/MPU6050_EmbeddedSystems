/*
 * mpu6050.c
 *
 *  Created on: Dec 10, 2024
 *      Author: shash
 */


#include "mpu6050.h"

void MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t data = 0x00; // Clear sleep mode bit (6th bit)
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDRESS, MPU6050_REG_PWR_MGMT_1, 1, &data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MPU6050_ReadAccelerometer(I2C_HandleTypeDef *hi2c, int16_t *accelX, int16_t *accelY, int16_t *accelZ) {
    uint8_t buffer[6];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, MPU6050_REG_ACCEL_XOUT_H, 1, buffer, 6, HAL_MAX_DELAY);
    if (status == HAL_OK) {
        *accelX = (int16_t)(buffer[0] << 8 | buffer[1]);
        *accelY = (int16_t)(buffer[2] << 8 | buffer[3]);
        *accelZ = (int16_t)(buffer[4] << 8 | buffer[5]);
    }
    return status;
}

HAL_StatusTypeDef MPU6050_ReadGyroscope(I2C_HandleTypeDef *hi2c, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ) {
    uint8_t buffer[6];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, MPU6050_REG_GYRO_XOUT_H, 1, buffer, 6, HAL_MAX_DELAY);
    if (status == HAL_OK) {
        *gyroX = (int16_t)(buffer[0] << 8 | buffer[1]);
        *gyroY = (int16_t)(buffer[2] << 8 | buffer[3]);
        *gyroZ = (int16_t)(buffer[4] << 8 | buffer[5]);
    }
    return status;
}

HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c, int16_t *temp) {
    uint8_t buffer[2];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, MPU6050_REG_TEMP_OUT_H, 1, buffer, 2, HAL_MAX_DELAY);
    if (status == HAL_OK) {
        *temp = (int16_t)(buffer[0] << 8 | buffer[1]);
    }
    return status;
}

HAL_StatusTypeDef MPU6050_ReadAllData(I2C_HandleTypeDef *hi2c, int16_t *accel, int16_t *gyro, int16_t *temp) {
    uint8_t buffer[14];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDRESS, MPU6050_REG_ACCEL_XOUT_H, 1, buffer, 14, HAL_MAX_DELAY);
    if (status == HAL_OK) {
        accel[0] = (int16_t)(buffer[0] << 8 | buffer[1]);
        accel[1] = (int16_t)(buffer[2] << 8 | buffer[3]);
        accel[2] = (int16_t)(buffer[4] << 8 | buffer[5]);
        *temp    = (int16_t)(buffer[6] << 8 | buffer[7]);
        gyro[0]  = (int16_t)(buffer[8] << 8 | buffer[9]);
        gyro[1]  = (int16_t)(buffer[10] << 8 | buffer[11]);
        gyro[2]  = (int16_t)(buffer[12] << 8 | buffer[13]);
    }
    return status;
}

HAL_StatusTypeDef MPU6050_GetScaledData(I2C_HandleTypeDef *hi2c, int16_t *accel, int16_t *gyro, int16_t *temp) {
    uint8_t i=0;
    HAL_StatusTypeDef status;
    status=MPU6050_ReadAllData(hi2c, accel, gyro, temp);
    if (status==HAL_OK) {
        // Accelerometer
    	for (i=0;i<3;i++)
    	{
    		accel[i]/=ACCEL_SCALE;
    		gyro[i]/=GYRO_SCALE;
    	}


        // Temperature
        *temp = *temp / 340.0 + 36.53;

    }
    return status;

}

