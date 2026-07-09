#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "imu.h"

static const char *TAG = "app";

void app_main(void)
{
    imu_config_t cfg = {
        .i2c_port = 0,
        .sda_gpio = 8,
        .scl_gpio = 9,
        .addr     = 0x68,
        .accel_fs = IMU_ACCEL_FS_4G,
        .gyro_fs  = IMU_GYRO_FS_500DPS,
    };

    imu_dev_t *imu = NULL;
    ESP_ERROR_CHECK(imu_init(&cfg, &imu));
    ESP_ERROR_CHECK(imu_start(imu));

    ESP_LOGI(TAG, "esp32-imu-bridge skeleton up; emitting synthetic samples");

    /* Skeleton loop at 1 Hz. The 1 kHz core-0 acquisition task + SPSC ring
     * buffer + WebSocket streaming land in S4-S5. */
    while (true) {
        imu_sample_t s;
        if (imu_get_sample(imu, &s) == ESP_OK) {
            ESP_LOGI(TAG, "seq=%lu t=%lld us az=%.3f g",
                     (unsigned long)s.seq, (long long)s.t_us, s.accel_g[2]);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
