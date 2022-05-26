# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS  ./components)
            

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp-cloud-connector)

target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "cert/actuator_private.pem.key" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "cert/actuator_public.pem.key" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "cert/actuator_certificate.pem.crt" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "cert/amazon_root.pem" TEXT)