# Host (Linux target) unit-test app for the pure imu_convert component.
# Runs Unity natively in CI — no ESP32 hardware or QEMU required.
cmake_minimum_required(VERSION 3.16)

# Make the pure component under test visible to this out-of-tree project.
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../components/imu_convert")

# Linux target: build only `main` and its transitive deps (imu_convert, unity).
# Without this the build pulls the full default component set, which includes
# esp_driver_* components unavailable on the Linux host (e.g. esp_hal_ana_cmpr).
set(COMPONENTS main)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(imu_convert_host_test)
