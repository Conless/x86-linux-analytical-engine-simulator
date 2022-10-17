project(x86_linux_analytical-engine-simulator)
set(CMAKE_BUILD_TYPE DEBUG)
set(SRC_LIST main.cpp)
add_executable(simulate ${SRC_LIST})