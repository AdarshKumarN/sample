# Sample Project
Tiny C++ project to demo auto doc generation with Doxygen + GitHub Actions.
Testing

To build Locally use below commands

#To generate the build system
cmake -B build

#For Complete Build
cmake --build build

#For Build to generate report for Coverage
cmake --build build --target coverage 

#use directly to disable the coverage reports
cmake -S . -B build DENABLE_TESTS=ON -DENABLE_COVERAGE=ON

#For cleaning the build directory
cmake --build build --clean-first

