cmake_minimum_required(VERSION 3.14) # Bumped version slightly for FetchContent
project(MathUtilsTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/src)

# --------------------------------------------------------
# [NEW] Automatically fetch Google Test (Fixes CI Error)
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
target_compile_options(math_utils PRIVATE --coverage -O0 -g)
target_link_libraries(math_utils PRIVATE --coverage)

# -------------------
# Test executable
# -------------------
add_executable(runTests test/testing.cpp)

# [UPDATED] Link against the fetched gtest_main (which includes gtest)
target_link_libraries(runTests PRIVATE math_utils gtest_main pthread)

target_compile_options(runTests PRIVATE --coverage -O0 -g)
target_link_libraries(runTests PRIVATE --coverage)

# -------------------
# Coverage target
# -------------------
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

if(LCOV_PATH AND GENHTML_PATH)
    add_custom_target(coverage
        COMMAND ${LCOV_PATH} --directory . --zerocounters
        COMMAND ./runTests
        COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info --ignore-errors mismatch
        COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/test/*' '*/_deps/*' --output-file coverage.info
        COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report --ignore-errors mismatch
        COMMAND ${CMAKE_COMMAND} -E echo "Coverage report: ${CMAKE_BINARY_DIR}/coverage_report/index.html"
        DEPENDS runTests
        COMMENT "Generating code coverage report..."
    )
endif()