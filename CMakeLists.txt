cmake_minimum_required(VERSION 3.13)
project(test-seq-lock)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp src/workers.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-interference-size)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DTEST_SL_RELAXED) # -DTEST_SL_RELAXED OR -DTEST_SL_2HB OR -DTEST_SL_3HB



