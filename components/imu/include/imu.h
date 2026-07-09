#pragma once

#include <stdint.h>

#include "esp_err.h"
#include "imu_convert.h"

#ifdef __cplusplus
extern "C" {
#endif

/* One inertial sample: timestamped, in physical units. */
typedef struct {
    int64_t  t_us;         /* monotonic timestamp (esp_timer) */
    float    accel_g[3];   /* x, y, z in g */
    float    gyro_dps[3];  /* x, y, z in deg/s */
    uint32_t seq;          /* monotonically increasing sample id */
} imu_sample_t;

/* Opaque device handle — callers never see the internals (S1 "opaque module"). */
typedef struct imu_dev_s imu_dev_t;

typedef struct {
    int            i2c_port;   /* I2C controller index */
    int            sda_gpio;
    int            scl_gpio;
    uint8_t        addr;       /* MPU6050 default 0x68 (0x69 if AD0 high) */
    imu_accel_fs_t accel_fs;
    imu_gyro_fs_t  gyro_fs;
} imu_config_t;

/* Allocate + configure the device. On success writes a handle to *out. */
esp_err_t imu_init(const imu_config_t *cfg, imu_dev_t **out);

/* Begin/stop sampling. */
esp_err_t imu_start(imu_dev_t *dev);
esp_err_t imu_stop(imu_dev_t *dev);

/* Read the most recent sample. ESP_ERR_INVALID_STATE if not started. */
esp_err_t imu_get_sample(imu_dev_t *dev, imu_sample_t *out);

/* Release the device. */
void imu_deinit(imu_dev_t *dev);

#ifdef __cplusplus
}
#endif
