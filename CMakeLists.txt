cmake_minimum_required(VERSION 3.16) 
project(MathUtilsTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# --------------------------------------------------------
# Automatically fetch Google Test
# --------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# This prevents Google Test from overwriting your compiler settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# -------------------
# Source library
# -------------------
add_library(math_utils STATIC src/math_utils.cpp)

target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


if(ENABLE_TESTS)
    find_package(Threads REQUIRED)

    add_executable(MathUtilsTest
        test/testing.cpp
    )

    target_link_libraries(MathUtilsTest
        PRIVATE
            math_utils
            gtest_main
            Threads::Threads
    )

    enable_testing()
    add_test(NAME MathUtilsTest COMMAND MathUtilsTest)
endif()

# --------------------------------------------------------
# Code coverage (GCC / Clang only, optional)
# --------------------------------------------------------
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    
    # Add coverage flags to all targets
    target_compile_options(math_utils PRIVATE -O0 -g --coverage)
    if(TARGET MathUtilsTest)
        target_compile_options(MathUtilsTest PRIVATE -O0 -g --coverage)
        target_link_libraries(MathUtilsTest PRIVATE --coverage)
    endif()

    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)

    if(NOT LCOV_PATH OR NOT GENHTML_PATH)
        message(WARNING "Coverage tools not found; coverage target will do nothing")
        add_custom_target(coverage
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage skipped (tools missing)"
        )
    else()
        add_custom_target(coverage
            COMMAND ${LCOV_PATH} --directory . --zerocounters
            COMMAND $<TARGET_FILE:MathUtilsTest>           # run the tests to generate .gcda files
            COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info --ignore-errors mismatch,inconsistent
            COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/test/*' '*/_deps/*' --output-file coverage.info
            COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report --ignore-errors mismatch
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated at: ${CMAKE_BINARY_DIR}/coverage_report/index.html"
            DEPENDS MathUtilsTest
            COMMENT "Generating code coverage report"
        )
    endif()
endif()