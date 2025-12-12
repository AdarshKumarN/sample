cmake_minimum_required(VERSION 3.10)
project(MathUtilsTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/src)

# -------------------
# Source library (for coverage)
# -------------------
add_library(math_utils STATIC 
                    src/math_utils.cpp)
                    #include new file path here to get the coverage report)

# [FIX 1] Apply coverage flags to the library so .gcda files are generated for it
target_compile_options(math_utils PRIVATE --coverage -O0 -g)
target_link_libraries(math_utils PRIVATE --coverage)

# -------------------
# Test executable
# -------------------
add_executable(runTests test/testing.cpp)
target_link_libraries(runTests PRIVATE math_utils gtest gtest_main pthread)
target_compile_options(runTests PRIVATE --coverage -O0 -g)
target_link_libraries(runTests PRIVATE --coverage)

# -------------------
# Coverage target
# -------------------
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

if(LCOV_PATH AND GENHTML_PATH)
    add_custom_target(coverage
        # 1. Reset counters (Optional but good practice)
        COMMAND ${LCOV_PATH} --directory . --zerocounters

        # 2. Run tests
        COMMAND ./runTests

        # 3. Capture coverage
        # [FIX 2] Changed directory to '.' to find both math_utils and runTests objects
        # [FIX 3] Changed 'mismatched' to 'mismatch' to match the tool's requirement
        COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info --ignore-errors mismatch

        # 4. Filter out system headers and test files (so you only see library coverage)
        #    (I added filtering for '/test/*' so your report focuses on source code)
        COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/test/*' --output-file coverage.info

        # 5. Generate HTML report
        COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report --ignore-errors mismatch

        COMMAND ${CMAKE_COMMAND} -E echo "Coverage report: ${CMAKE_BINARY_DIR}/coverage_report/index.html"

        DEPENDS runTests
        COMMENT "Generating code coverage report..."
    )
endif()