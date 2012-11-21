cmake_minimum_required(VERSION 2.8)

project(2do)

set(2do_VERSION_MAJOR 0)
set(2do_VERSION_MINOR 1)
set(2do_VERSION_PATCH 0)
set(2do_VERSION_APPENDIX "-alpha")
set(CMAKE_C_FLAGS "-g -Wall")

# Create uninstall target template file, if it doesn't exist...
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in)
  set(__uninstall_filename ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake.in)

  # BEGIN actual write to file...
  file(WRITE ${__uninstall_filename} "
if (NOT EXISTS \"\@CMAKE_CURRENT_BINARY_DIR\@/install_manifest.txt\")
  message(FATAL_ERROR \"Cannot find install manifest: \\\"\@CMAKE_CURRENT_BINARY_DIR\@/install_manifest.txt\\\"\")
endif(NOT EXISTS \"\@CMAKE_CURRENT_BINARY_DIR\@/install_manifest.txt\")

file(READ \"\@CMAKE_CURRENT_BINARY_DIR\@/install_manifest.txt\" files)
string(REGEX REPLACE \"\\n\" \";\" files \"\${files}\")

foreach (file \${files})
  message(STATUS \"Uninstalling \\\"\$ENV{DESTDIR}\${file}\\\"\")
  if (EXISTS \"\$ENV{DESTDIR}\${file}\")
    execute_process(
      COMMAND \@CMAKE_COMMAND\@ -E remove \"\$ENV{DESTDIR}\${file}\"
      OUTPUT_VARIABLE rm_out
      RESULT_VARIABLE rm_retval
    )
    if(NOT \${rm_retval} EQUAL 0)
      message(FATAL_ERROR \"Problem when removing \\\"\$ENV{DESTDIR}\${file}\\\"\")
    endif (NOT \${rm_retval} EQUAL 0)
  else (EXISTS \"\$ENV{DESTDIR}\${file}\")
    message(STATUS \"File \\\"\$ENV{DESTDIR}\${file}\\\" does not exist.\")
  endif (EXISTS \"\$ENV{DESTDIR}\${file}\")
endforeach(file)
") # END of appending to file...
endif()

FILE(GLOB_RECURSE 2DO_SOURCE_FILES "src/*.c")

configure_file(
  "${PROJECT_SOURCE_DIR}/src/info.h.in"
  "${PROJECT_BINARY_DIR}/src/info.h"
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY
)

include_directories(${PROJECT_BINARY_DIR})

add_executable(2do ${2DO_SOURCE_FILES})

# add install and uninstall command to Makefile
install(TARGETS 2do DESTINATION /usr/bin)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
