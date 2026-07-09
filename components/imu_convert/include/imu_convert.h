#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MPU6050 accelerometer full-scale ranges (AFS_SEL). */
typedef enum {
    IMU_ACCEL_FS_2G = 0,
    IMU_ACCEL_FS_4G,
    IMU_ACCEL_FS_8G,
    IMU_ACCEL_FS_16G,
} imu_accel_fs_t;

/* MPU6050 gyroscope full-scale ranges (FS_SEL). */
typedef enum {
    IMU_GYRO_FS_250DPS = 0,
    IMU_GYRO_FS_500DPS,
    IMU_GYRO_FS_1000DPS,
    IMU_GYRO_FS_2000DPS,
} imu_gyro_fs_t;

/* Convert a raw signed 16-bit accel count to g, per the configured full scale.
 * Sensitivities are the MPU6050 datasheet LSB/g values. */
float imu_accel_raw_to_g(int16_t raw, imu_accel_fs_t fs);

/* Convert a raw signed 16-bit gyro count to deg/s, per the configured full scale. */
float imu_gyro_raw_to_dps(int16_t raw, imu_gyro_fs_t fs);

/* Combine an MSB/LSB pair (MPU6050 registers are big-endian) into a signed 16-bit. */
int16_t imu_be16_to_i16(uint8_t msb, uint8_t lsb);

#ifdef __cplusplus
}
#endif
