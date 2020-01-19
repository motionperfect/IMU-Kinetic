cmake_minimum_required(VERSION 3.14)
project(MotionPerfect C ASM)
set(TARGET_NAME "${PROJECT_NAME}.elf")

include(stm32l4xx.gcc.cmake)

######################################
# source
######################################
# C sources
file(GLOB_RECURSE C_SOURCES "Middlewares/Third_Party/FreeRTOS/*.c"
        "Middlewares/Third_Party/Printf/*.c"
        "Drivers/CMSIS_5/CMSIS/RTOS2/FreeRTOS/Source/*.c"
        "Drivers/CMSIS_5/Device/ST/STM32L4xx/Source/*.c"
        "Drivers/STM32L4xx_HAL_Driver/Src/*.c"
        "Drivers/BSP/Src/*.c"
        "Core/Src/*.c")

#######################################
# CFLAGS
#######################################
## Macros for gcc
# C defines
add_definitions(-DUSE_HAL_DRIVER -DSTM32L475xx)

# C includes
include_directories(Core/Inc)

include_directories(Drivers/BSP/Inc)
include_directories(Drivers/STM32L4xx_HAL_Driver/Inc)
include_directories(Drivers/STM32L4xx_HAL_Driver/Inc/Legacy)
include_directories(Drivers/CMSIS_5/Device/ST/STM32L4xx/Include)
include_directories(Drivers/CMSIS_5/CMSIS/Core/Include)
include_directories(Drivers/CMSIS_5/CMSIS/RTOS2/FreeRTOS/Include)
include_directories(Drivers/CMSIS_5/CMSIS/RTOS2/Include)
include_directories(Drivers/CMSIS_5/CMSIS/DSP/Include)

include_directories(Middlewares/Third_Party/FreeRTOS/Source/include)
include_directories(Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F)
include_directories(Middlewares/Third_Party/Printf)

#######################################
# executables
#######################################
add_executable(${TARGET_NAME} "${C_SOURCES}")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${TARGET_NAME}> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${TARGET_NAME}> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")