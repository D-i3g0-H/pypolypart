cmake_minimum_required(VERSION 3.15)
project(pypolypart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)
find_package(CGAL REQUIRED)

pybind11_add_module(_core src/bindings.cpp)

target_link_libraries(_core PRIVATE CGAL::CGAL)

target_compile_definitions(_core PRIVATE VERSION_INFO="${PROJECT_VERSION}")

install(TARGETS _core DESTINATION pypolypart)