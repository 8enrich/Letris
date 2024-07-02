cmake_minimum_required(VERSION 3.5)
project(letris)
#set(CMAKE_C_STANDARD 99)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.0"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)
# Adding nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY "https://github.com/nlohmann/json.git"
    GIT_TAG "v3.11.3"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(nlohmann_json)
# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} letris.rc)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_LIST_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
