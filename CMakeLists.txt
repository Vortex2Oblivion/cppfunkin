cmake_minimum_required(VERSION 3.10.0)
project(cppfunkin VERSION 0.1.0 LANGUAGES C CXX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(cppfunkin ${SOURCES})

add_subdirectory(external/raylib-5.5)
target_link_libraries(cppfunkin raylib)
add_subdirectory(external/raylib-cpp-5.5.0)
target_link_libraries(cppfunkin raylib_cpp)
add_subdirectory(external/json-3.12.0)
target_link_libraries(cppfunkin nlohmann_json)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
