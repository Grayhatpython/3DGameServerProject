cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME OpenglProject)
set(CMAKE_CXX_STANDARD 17)

# 실행 파일은 빌드 디렉토리 안에 bin 폴더에 출력.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)