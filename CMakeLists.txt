cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(hanako)

# Generate compile_commands.json
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()

# Our Project

add_executable(${PROJECT_NAME}
    src/engine/e_math.c
    src/engine/e_scene.c
    src/engine/e_screen.c
    src/engine/e_asset.c
    src/engine/e_core.c

    src/scenes/g_scene_test.c
    src/scenes/g_scene_boot.c

    src/g_cursor.c
    src/g_scenes.c
    src/g_assets.c
    src/g_main.c
)

target_link_libraries(${PROJECT_NAME}
    raylib
)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()