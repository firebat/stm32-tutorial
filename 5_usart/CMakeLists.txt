PROJECT(main)
cmake_minimum_required(VERSION 2.6)

SET(PERIPH_LIB $ENV{HOME}/libraries/STM32F10x_StdPeriph_Lib_V3.5.0)
SET(PERIPH_LIB_SRC ${PERIPH_LIB}/Libraries/STM32F10x_StdPeriph_Driver/src)

INCLUDE_DIRECTORIES(
  ../
  ${PERIPH_LIB}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
  ${PERIPH_LIB}/Libraries/CMSIS/CM3/CoreSupport
  ${PERIPH_LIB}/Libraries/STM32F10x_StdPeriph_Driver/inc
)

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_C_COMPILER "arm-none-eabi-gcc")
SET(CMAKE_LINKER "arm-none-eabi-ld")
SET(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
SET(LINK_SCRIPT "../stm32f10x.ld")
SET(FAMILY "STM32F10X_MD_VL")

SET(STARTUP
  ../startup_stm32f10x.c
  ${PERIPH_LIB}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
  ${PERIPH_LIB_SRC}/stm32f10x_rcc.c
  ${PERIPH_LIB_SRC}/stm32f10x_gpio.c
  ${PERIPH_LIB_SRC}/stm32f10x_usart.c
#  ${PERIPH_LIB_SRC}/misc.c
)

#SET(DEBUG_FLAGS "-O3")
SET(DEBUG_FLAGS "-O0 -g")

SET(MCU_FLAGS "-march=armv7-m -mcpu=cortex-m3 -mthumb")
SET(CMAKE_C_FLAGS "${MCU_FLAGS} -fno-common -fno-builtin -ffreestanding -Wall ${DEBUG_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib")
add_definitions(-D${FAMILY} -DUSE_STDPERIPH_DRIVER)
SET(CMAKE_EXE_LINKER_FLAGS "${DEBUG_FLAGS} -nostartfiles -T${LINK_SCRIPT}")
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


cmake_policy(SET CMP0015 OLD)
ADD_EXECUTABLE(${PROJECT_NAME}.elf ${PROJECT_NAME}.c ${STARTUP})

add_custom_command(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.bin COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
add_custom_target(generate_bin ALL DEPENDS ${PROJECT_NAME}.bin)

add_custom_command(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.hex COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
add_custom_target(generate_hex ALL DEPENDS ${PROJECT_NAME}.hex)

add_custom_target(burn ../stm32 burn ${PROJECT_NAME}.bin depends ${PROJECT_NAME}.bin)
