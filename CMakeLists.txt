cmake_minimum_required(VERSION 3.10.0)
project(cppfunkin VERSION 0.1.0 LANGUAGES C CXX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(cppfunkin ${SOURCES})

add_subdirectory(external/raylib)
target_link_libraries(cppfunkin raylib)
add_subdirectory(external/raylib-cpp)
target_link_libraries(cppfunkin raylib_cpp)
add_subdirectory(external/json)
target_link_libraries(cppfunkin nlohmann_json)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)