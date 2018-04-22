cmake_minimum_required(VERSION 3.1)

project(pyaboria)

set(lib_dir "lib")
set(include_dirs "")
set(libraries "")

set(CMAKE_MODULE_PATH "${lib_dir}/Aboria/cmake"
                        ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1 )

# OpenMP
find_package(OpenMP REQUIRED)
add_definitions(-DHAVE_OPENMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

# Eigen
find_package(Eigen3 REQUIRED)
add_definitions(-DHAVE_EIGEN)
list(APPEND include_dirs ${EIGEN3_INCLUDE_DIR})

# Boost
find_package(Boost 1.50.0 COMPONENTS python serialization REQUIRED)
list(APPEND libraries ${Boost_LIBRARIES})
list(APPEND include_dirs ${Boost_INCLUDE_DIRS})

# VTK 
find_package(VTK REQUIRED)
add_definitions(-DHAVE_VTK)
list(APPEND libraries ${VTK_LIBRARIES})
list(APPEND include_dirs ${VTK_INCLUDE_DIRS})

# Aboria
list(APPEND include_dirs ${lib_dir}/Aboria/src)
list(APPEND include_dirs ${lib_dir}/Aboria/third-party)

include_directories(${include_dirs})

set(source_dir src/pyaboria)

set(source_files 
    )

set(header_files 
    ${source_dir}/pyaboria.h
    )

add_library(pyaboria SHARED ${source_files} ${header_files} "${source_dir}/python.cpp")
target_link_libraries(pyaboria ${libraries})

