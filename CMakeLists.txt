cmake_minimum_required(VERSION 3.20)

project(jswd
        VERSION 1.0.0
        LANGUAGES C CXX
        )

if (UNIX AND CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
endif ()

# ===============================================================================================
# Library
# ===============================================================================================

option(BUILD_TESTS "build test code" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(BUILD_TESTS ON)
endif ()

file(
        GLOB_RECURSE
        SOURCES
        src/*.cpp
        src/*.c
        src/*.h
        ${PROJECT_BINARY_DIR}/gen/*.c
        ${PROJECT_BINARY_DIR}/gen/*.cpp
)

file(
        GLOB_RECURSE
        HEADERS
        include/*.h
)

# ===============================================================================================
# jsex
# ===============================================================================================
set(JSEX_PATH $ENV{JSEX_PATH})

include(FetchContent)

if (JSEX_PATH)

    option(USE_CHAKRA_CORE "use chackra core" OFF)

    add_subdirectory(${JSEX_PATH} ${PROJECT_BINARY_DIR}/jsex)

    get_target_property(JSEX_INCLUDES jsex INTERFACE_INCLUDE_DIRECTORIES)

    include_directories(
            ${JSEX_PATH}/include
            ${JSEX_INCLUDES}
    )

else ()

    if(DEFINED ENV{GITHUB_TOKEN})
      set(GIT_REPO https://tinysec:$ENV{GITHUB_TOKEN}@github.com/tinysec/jsex)
    else()
      set(GIT_REPO https://github.com/tinysec/jsex)
    endif()

    FetchContent_Declare(jsex
            GIT_REPOSITORY ${GIT_REPO}
            GIT_TAG autotag-20230625-040717
            )

    FetchContent_MakeAvailable(jsex)
endif ()


# ===============================================================================================
# version
# ===============================================================================================

execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
        COMMAND git rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/src/git_version.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/gen/git_version.h"
)


# ===============================================================================================
# executable
# ===============================================================================================

add_library(
        ${PROJECT_NAME}
        SHARED
        ${SOURCES}
        ${HEADERS}
        src/version.rc
)

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
        BUILD_LIBRARY=1
        _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
        USE_EDGEMODE_JSRT
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        C_STANDARD 11
        )

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "js"
)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/inc
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        jsex
        DbgEng
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/exports.def"
)


# ===============================================================================================
# script
# ===============================================================================================
include(cmake/Binary2Header.cmake)



bin2h(
        SOURCE_FILE "src/script/jswd.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/jswd.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_JSWD"
)

bin2h(
        SOURCE_FILE "src/script/dbgeng.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/dbgeng.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_DBGENG"
)


bin2h(
        SOURCE_FILE "src/script/jswd/module.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/module.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_MODULE"
)

bin2h(
        SOURCE_FILE "src/script/jswd/physical.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/physical.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_PHYSICAL"
)

bin2h(
        SOURCE_FILE "src/script/jswd/processor.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/processor.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_PROCESSOR"
)


bin2h(
        SOURCE_FILE "src/script/jswd/reader.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/reader.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_READER"
)

bin2h(
        SOURCE_FILE "src/script/jswd/register.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/register.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_REGISTER"
)

bin2h(
        SOURCE_FILE "src/script/jswd/segment.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/segment.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_SEGMENT"
)


bin2h(
        SOURCE_FILE "src/script/jswd/symbol.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/symbol.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_SYMBOL"
)


bin2h(
        SOURCE_FILE "src/script/jswd/virtual.js"
        HEADER_FILE "${PROJECT_BINARY_DIR}/gen/script/virtual.js.h"
        VARIABLE_NAME "JSWD_BUILTIN_SCRIPT_VIRTUAL"
)


# ===============================================================================================
# test
# ===============================================================================================

if (BUILD_TESTS)

    include(CTest)

    add_executable(
            test_${PROJECT_NAME}
            ${SOURCES}
            ${HEADERS}
            tests/test.cpp
    )

    # set lang requrired
    set_target_properties(test_${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            C_STANDARD 11
            )

    set_target_properties(
            test_${PROJECT_NAME} PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )


    target_link_libraries(
            test_${PROJECT_NAME}
            PUBLIC
            jsex
            DbgEng
    )

    target_compile_definitions(
            test_${PROJECT_NAME}
            PRIVATE
            BUILD_TESTS=1
            _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
            USE_EDGEMODE_JSRT
    )

    target_include_directories(
            test_${PROJECT_NAME}
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/src/inc
            ${CMAKE_CURRENT_BINARY_DIR}
    )

endif (BUILD_TESTS)
