#include "imu_convert.h"

/* MPU6050 datasheet accel sensitivity (LSB per g) per full-scale setting. */
static float accel_lsb_per_g(imu_accel_fs_t fs)
{
    switch (fs) {
    case IMU_ACCEL_FS_2G:  return 16384.0f;
    case IMU_ACCEL_FS_4G:  return 8192.0f;
    case IMU_ACCEL_FS_8G:  return 4096.0f;
    case IMU_ACCEL_FS_16G: return 2048.0f;
    }
    return 16384.0f;
}

/* MPU6050 datasheet gyro sensitivity (LSB per deg/s) per full-scale setting. */
static float gyro_lsb_per_dps(imu_gyro_fs_t fs)
{
    switch (fs) {
    case IMU_GYRO_FS_250DPS:  return 131.0f;
    case IMU_GYRO_FS_500DPS:  return 65.5f;
    case IMU_GYRO_FS_1000DPS: return 32.8f;
    case IMU_GYRO_FS_2000DPS: return 16.4f;
    }
    return 131.0f;
}

float imu_accel_raw_to_g(int16_t raw, imu_accel_fs_t fs)
{
    return (float)raw / accel_lsb_per_g(fs);
}

float imu_gyro_raw_to_dps(int16_t raw, imu_gyro_fs_t fs)
{
    return (float)raw / gyro_lsb_per_dps(fs);
}

int16_t imu_be16_to_i16(uint8_t msb, uint8_t lsb)
{
    return (int16_t)(((uint16_t)msb << 8) | (uint16_t)lsb);
}
