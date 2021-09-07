cmake_minimum_required(VERSION 3.6)
project (vision) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_RPATH "$ORIGIN")
SET(CMAKE_BUILD_TYPE "Release")

add_compile_options(-static-libstdc++)
add_compile_options(-fvisibility=hidden)

add_compile_options(-DENABLE_ASSERTION)

include_directories(include)

file(GLOB_RECURSE CPP_FILES src/*.cpp)
add_library (${PROJECT_NAME} STATIC ${CPP_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(thirdparty/googletest)
add_subdirectory(thirdparty/opencv)
add_subdirectory(test/unittest)