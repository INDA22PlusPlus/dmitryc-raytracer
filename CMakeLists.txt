cmake_minimum_required(VERSION 3.23)
project(dmitryc_raytracer)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(dmitryc_raytracer main.cpp vec.h ray.h camera.h scene.h ray-testing-scene.h first-sphere-scene.h shaded-sphere-scene.h)

#add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
#add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
#
#find_package(ImageMagick REQUIRED COMPONENTS MagickCore MagickWand Magick++)
#include_directories(${ImageMagick_INCLUDE_DIRS})
##execute_process(COMMAND Magick++-config --ldflags
##        OUTPUT_VARIABLE ImageMagick_LINK_FLAGS
##        OUTPUT_STRIP_TRAILING_WHITESPACE
##        )
#target_link_libraries(dmitryc_raytracer ${ImageMagick_LIBRARIES})



## Find where Magick++-config lives
#find_program(MAGICK_CONFIG "Magick++-config")
## Ask about CXX and lib flags/locations
#execute_process(COMMAND "${MAGICK_CONFIG}" "--cxxflags" OUTPUT_VARIABLE MAGICK_CXX_FLAGS)
#execute_process(COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS)
## Remove trailing whitespace (CMAKE warns about this)
#string(STRIP "${MAGICK_CXX_FLAGS}" MAGICK_CXX_FLAGS)
#string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)
## Append all flags to CMAKE_CXX_FLAGS
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${MAGICK_CXX_FLAGS} ${MAGICK_LD_FLAGS}")
#
#set(SOURCE_FILES main.cpp)
#
#add_executable(dmitryc_raytracer main.cpp)
