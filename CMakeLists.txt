cmake_minimum_required(VERSION 3.28)
project(Space)

# cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
# project(example)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
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
endif()

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(ENV{OMP_NUM_THREADS} 8)
    message(NOTICE "OpenMP Found")
endif()
message(NOTICE "Was OpenMP Found?")

# Our Project

add_executable(${PROJECT_NAME} main.cpp
        Title.cpp
        Title.h
        Gameplay.cpp
        Gameplay.h
        structures.cpp
        structures.h
        Player.cpp
        Player.h
        Collidable.cpp
        Collidable.h
        Cuboid.cpp
        Cuboid.h
        Developer_Tools/Developer_Tools.cpp
        Developer_Tools/Developer_Tools.h
        Developer_Tools/Logging.cpp
        Developer_Tools/Logging.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# set(CMAKE_CXX_STANDARD 26)

# add_executable(Space main.cpp)
