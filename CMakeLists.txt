cmake_minimum_required(VERSION 3.10.0)
project(cppfunkin VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")
add_executable(cppfunkin ${SOURCES})

add_subdirectory(external/raylib)
target_link_libraries(cppfunkin raylib)

add_subdirectory(external/raylib-cpp)
target_link_libraries(cppfunkin raylib_cpp)

add_subdirectory(external/json)
target_link_libraries(cppfunkin nlohmann_json)

add_subdirectory(external/pugixml)
target_link_libraries(cppfunkin pugixml)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_dependencies(${PROJECT_NAME} copy_assets)
if(MSVC)
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/assets
    COMMENT "COPYING ASSETS"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "COPYING ASSETS"
)
endif(MSVC)