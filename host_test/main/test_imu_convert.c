#include <stdlib.h>

#include "unity.h"

#include "imu_convert.h"

void setUp(void) {}
void tearDown(void) {}

TEST_CASE("accel raw->g at +/-2g uses 16384 LSB/g", "[imu_convert]")
{
    TEST_ASSERT_FLOAT_WITHIN(1e-4f, 1.0f, imu_accel_raw_to_g(16384, IMU_ACCEL_FS_2G));
    TEST_ASSERT_FLOAT_WITHIN(1e-4f, -1.0f, imu_accel_raw_to_g(-16384, IMU_ACCEL_FS_2G));
    TEST_ASSERT_FLOAT_WITHIN(1e-4f, 0.0f, imu_accel_raw_to_g(0, IMU_ACCEL_FS_2G));
}

TEST_CASE("accel full-scale doubling halves sensitivity", "[imu_convert]")
{
    /* Same raw count reads twice as large in g when the range doubles. */
    TEST_ASSERT_FLOAT_WITHIN(1e-4f, 2.0f, imu_accel_raw_to_g(16384, IMU_ACCEL_FS_4G));
    TEST_ASSERT_FLOAT_WITHIN(1e-4f, 8.0f, imu_accel_raw_to_g(16384, IMU_ACCEL_FS_16G));
}

TEST_CASE("gyro raw->dps at +/-250dps uses 131 LSB/dps", "[imu_convert]")
{
    TEST_ASSERT_FLOAT_WITHIN(1e-2f, 1.0f, imu_gyro_raw_to_dps(131, IMU_GYRO_FS_250DPS));
    TEST_ASSERT_FLOAT_WITHIN(1e-2f, -1.0f, imu_gyro_raw_to_dps(-131, IMU_GYRO_FS_250DPS));
}

TEST_CASE("be16 combines bytes as signed big-endian", "[imu_convert]")
{
    TEST_ASSERT_EQUAL_INT16(0x0102, imu_be16_to_i16(0x01, 0x02));
    TEST_ASSERT_EQUAL_INT16(-1, imu_be16_to_i16(0xFF, 0xFF));
    TEST_ASSERT_EQUAL_INT16(-32768, imu_be16_to_i16(0x80, 0x00));
}

/* ESP-IDF Linux-target entry point: run every registered TEST_CASE and
 * terminate the process with a definitive exit code. Without the explicit
 * exit(), returning from app_main leaves the linux-target process alive and
 * the CI step hangs until the job timeout. */
void app_main(void)
{
    UNITY_BEGIN();
    unity_run_all_tests();
    int failures = UNITY_END();
    exit(failures == 0 ? 0 : 1);
}
