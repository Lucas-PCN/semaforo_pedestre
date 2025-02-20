# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicialize o pico_sdk
include(pico_sdk_import.cmake)

project(semaforo_pedestre C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Adiciona o executável
add_executable(semaforo_pedestre semaforo_pedestre.c inc/ssd1306_i2c.c)

# Nome e versão do programa
pico_set_program_name(semaforo_pedestre "semaforo_pedestre")
pico_set_program_version(semaforo_pedestre "1.0")

# Habilita saída via USB
pico_enable_stdio_usb(semaforo_pedestre 1)
pico_enable_stdio_uart(semaforo_pedestre 0)

# Inclui bibliotecas padrão e do OLED
target_link_libraries(semaforo_pedestre
    pico_stdlib
    hardware_i2c
)

# Inclui arquivos de cabeçalho
target_include_directories(semaforo_pedestre PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Gera arquivos extras para o Pico
pico_add_extra_outputs(semaforo_pedestre)


