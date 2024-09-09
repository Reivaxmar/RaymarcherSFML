cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(headers /usr/include)

find_package(SFML 2.5 COMPONENTS graphics QUIET)
if(NOT SFML_FOUND)
    message(">>> Installing SFML because it wasn't found")
    # Install SFML
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Create a custom target to copy the assets
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to the build directory"
)

# Make sure the 'copy_assets' target is run before building the main executable
add_dependencies(${PROJECT_NAME} copy_assets)
