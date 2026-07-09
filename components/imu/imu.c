#include "imu.h"

#include <stdlib.h>
#include <string.h>

#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "imu";

struct imu_dev_s {
    imu_config_t cfg;
    bool         running;
    uint32_t     seq;
};

esp_err_t imu_init(const imu_config_t *cfg, imu_dev_t **out)
{
    if (cfg == NULL || out == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    imu_dev_t *dev = calloc(1, sizeof(*dev));
    if (dev == NULL) {
        return ESP_ERR_NO_MEM;
    }
    dev->cfg = *cfg;

    /* TODO(S4): configure the I2C master, probe WHO_AM_I (reg 0x75) == 0x68,
     * clear sleep bit in PWR_MGMT_1 (reg 0x6B), set AFS_SEL/FS_SEL from cfg. */
    ESP_LOGI(TAG, "init (stub): i2c%d sda=%d scl=%d addr=0x%02x",
             cfg->i2c_port, cfg->sda_gpio, cfg->scl_gpio, cfg->addr);

    *out = dev;
    return ESP_OK;
}

esp_err_t imu_start(imu_dev_t *dev)
{
    if (dev == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    dev->running = true;
    return ESP_OK;
}

esp_err_t imu_stop(imu_dev_t *dev)
{
    if (dev == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    dev->running = false;
    return ESP_OK;
}

esp_err_t imu_get_sample(imu_dev_t *dev, imu_sample_t *out)
{
    if (dev == NULL || out == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!dev->running) {
        return ESP_ERR_INVALID_STATE;
    }

    /* TODO(S4): burst-read ACCEL_XOUT_H..GYRO_ZOUT_L (14 bytes) over I2C and
     * convert with imu_be16_to_i16 + imu_accel_raw_to_g / imu_gyro_raw_to_dps.
     * Skeleton emits a synthetic stationary sample (1 g on +Z, no rotation)
     * so the downstream streaming path is wireable before hardware arrives. */
    memset(out, 0, sizeof(*out));
    out->t_us       = esp_timer_get_time();
    out->accel_g[2] = 1.0f;
    out->seq        = dev->seq++;
    return ESP_OK;
}

void imu_deinit(imu_dev_t *dev)
{
    free(dev);
}
