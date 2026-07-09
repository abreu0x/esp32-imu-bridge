idf_component_register(
    SRCS "imu.c"
    INCLUDE_DIRS "include"
    REQUIRES imu_convert esp_timer
)
