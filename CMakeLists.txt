cmake_minimum_required(VERSION 3.14)
project(MotionPerfect C ASM)

######################################
# source
######################################
# C sources
file(GLOB_RECURSE C_SOURCES "Middlewares/Third_Party/FreeRTOS/Source/*.c"
        "Drivers/STM32L4xx_HAL_Driver/Src/*.c"
        "Core/Src/*.c")

# ASM sources
set(ASM_SOURCES "startup_stm32l475xx.s")

#######################################
# CFLAGS
#######################################
## Macros for gcc
# C defines
add_definitions(-DUSE_HAL_DRIVER -DSTM32L475xx)

# C includes
include_directories(Core/Inc)
include_directories(Drivers/STM32L4xx_HAL_Driver/Inc)
include_directories(Drivers/STM32L4xx_HAL_Driver/Inc/Legacy)
include_directories(Middlewares/Third_Party/FreeRTOS/Source/include)
include_directories(Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2)
include_directories(Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F)
include_directories(Drivers/CMSIS/Device/ST/STM32L4xx/Include)
include_directories(Drivers/CMSIS/Include)

add_executable(${PROJECT_NAME}.elf ${C_SOURCES} ${ASM_SOURCES})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

# add_custom_command(TARGET ${PROJECT_NAME}.elf PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}
#        COMMENT "Creating build directory")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")