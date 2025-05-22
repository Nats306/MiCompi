cmake_minimum_required(VERSION 3.15)
project(mi_proyecto)

set(CMAKE_CXX_STANDARD 17)

# Incluye 'include' y 'src' para los headers
include_directories(include)
include_directories(src)

# Incluye todos los .cpp dentro de src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crea el ejecutable
add_executable(mi_proyecto ${SOURCES})
