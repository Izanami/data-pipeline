cmake_minimum_required (VERSION 2.6)
project (DataPipeline)

# Path extra package
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Packages
find_package(Doxygen)
find_package(Glib)
find_package(cmocka)

# Options
option(DEVEL "Enable devel mode" OFF)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# Set flags
if(DEVEL)
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer")
    else()
        message( FATAL_ERROR "In devel mode, you must use clang." )
    endif()
endif()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall --pedantic -pedantic-errors --std=c11 -Werror -Wno-padded")

# Glib
if(NOT GLib_FOUND)
    message(FATAL_ERROR "Require GLib-2.0")
endif()

include_directories(${GLib_INCLUDE_DIRS})

# Build shared libraries.
add_library(datapipeline SHARED src/pipeline.c src/job.c)
target_link_libraries(datapipeline ${GLib_LIBRARY})

###
# TEST
###
enable_testing()
add_executable(test-pipeline src/pipeline_test.c)
add_executable(test-job src/job_test.c)
target_link_libraries(test-pipeline datapipeline ${CMOCKA_LIBRARY})
target_link_libraries(test-job datapipeline ${CMOCKA_LIBRARY})
add_test(test test-pipeline test-job)

###
# DOCUMENTATION
###
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_result "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()
