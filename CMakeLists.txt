cmake_minimum_required(VERSION 3.10.0)
project(cppfunkin VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(MAIN src/main.cpp)
file(GLOB FUNKIN "src/funkin/*.cpp")
file(GLOB ENGINE "src/engine/*.cpp")

set(OS)

if(APPLE)
    set(OS ${OS}
        src/engine/macos.mm
    )
endif()

add_executable(${PROJECT_NAME} ${MAIN} ${FUNKIN} ${ENGINE} ${OS})


add_subdirectory(external/raylib)
target_link_libraries(${PROJECT_NAME} raylib)

add_subdirectory(external/raylib-cpp)
target_link_libraries(${PROJECT_NAME} raylib_cpp)

add_subdirectory(external/json)
target_link_libraries(${PROJECT_NAME} nlohmann_json)

add_subdirectory(external/pugixml)
target_link_libraries(${PROJECT_NAME} pugixml)

if (UNIX AND NOT APPLE)
include_directories(external/gamemode/lib)
endif ()

add_dependencies(${PROJECT_NAME} copy_assets)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
    add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/Release/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/Debug/assets

    COMMENT "COPYING ASSETS"
)

else()
    add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "COPYING ASSETS"
)
endif(MSVC)
