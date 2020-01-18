set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(ROOT "${CMAKE_SOURCE_DIR}")

#######################################
# paths
#######################################
# GCC path
set(GCC_PATH "${ROOT}/Tools/gcc-arm-none-eabi-8-2019-q3-update/bin")

######################################
# building variables
######################################

# optimization
if (CMAKE_BUILD_TYPE EQUAL "MinSizeRel")
    set(OPT "-Os")
elseif (CMAKE_BUILD_TYPE EQUAL "Release")
    set(OPT "-O3")
else ()
    set(OPT "-Og")
endif ()

#######################################
# binaries
#######################################
set(PREFIX "arm-none-eabi-")

set(CMAKE_CXX_COMPILER "${GCC_PATH}/${PREFIX}g++")
set(CMAKE_C_COMPILER "${GCC_PATH}/${PREFIX}gcc")
set(CMAKE_ASM_COMPILER "${GCC_PATH}/${PREFIX}gcc")
set(CMAKE_OBJCOPY "${GCC_PATH}/${PREFIX}objcopy")

#######################################
# CFLAGS
#######################################
# cpu
set(CPU "-mcpu=cortex-m4")

# fpu
set(FPU "-mfpu=fpv4-sp-d16")

# float-abi
set(FLOAT-ABI "-mfloat-abi=hard")

# mcu
set(MCU "${CPU} -mthumb ${FPU} ${FLOAT-ABI}")

#######################################
# LDFLAGS
#######################################
# libraries
set(LIBS "-lc -lm -lnosys")
set(LIBDIR "")

# link script
set(LINKER_SCRIPT "${ROOT}/Drivers/CMSIS_5/Device/ST/STM32L4xx/Source/GCC/STM32L475VGTx_FLASH.ld")

#######################################
# GCC flags
#######################################
# compilers
set(COMMON_FLAGS "${MCU} -specs=nosys.specs ${LIBDIR} ${LIBS} ${OPT} -Wall -fdata-sections -ffunction-sections")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -x assembler-with-cpp")

# linkers
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -T ${LINKER_SCRIPT}")