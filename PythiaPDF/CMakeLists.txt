cmake_minimum_required(VERSION 3.16)

project(PythiaPDF VERSION 1.0.0
                  DESCRIPTION "Explore the pythia8 parton distribution functions"
                  LANGUAGES CXX)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

#include BOOST
find_package(Boost 1.69 COMPONENTS program_options REQUIRED)

find_package(ROOT 6.22 CONFIG REQUIRED COMPONENTS Hist)

#include PYTHIA
find_package(Pythia8 REQUIRED)

add_subdirectory(pythiapdf_base)

add_subdirectory(cli)

#enable_testing()
#add_subdirectory(test)

