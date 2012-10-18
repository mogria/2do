cmake_minimum_required(VERSION 2.8)

project(2do)

set (2do_VERSION_MAJOR 0)
set (2do_VERSION_MINOR 1)
set (2do_VERSION_PATCH 0)
set (2do_VERSION_APPENDIX "-alpha")

configure_file(
  "${PROJECT_SOURCE_DIR}/src/2do.h.in"
  "${PROJECT_BINARY_DIR}/src/2do.h"
)

include_directories(${PROJECT_BINARY_DIR})

add_executable(2do src/2do.c)
