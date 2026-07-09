# Host (Linux target) unit-test app for the pure imu_convert component.
# Runs Unity natively in CI — no ESP32 hardware or QEMU required.
cmake_minimum_required(VERSION 3.16)

# Make the pure component under test visible to this out-of-tree project.
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../components/imu_convert")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(imu_convert_host_test)
