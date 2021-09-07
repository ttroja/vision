project (unittest)

file(GLOB_RECURSE CPP_FILES src/*.cpp)
add_executable (${PROJECT_NAME} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} vision gtest opencv)

install(TARGETS ${PROJECT_NAME} DESTINATION test)
