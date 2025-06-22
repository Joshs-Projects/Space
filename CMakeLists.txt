cmake_minimum_required(VERSION 3.28)
cmake_policy(VERSION 3.28)

project(Space LANGUAGES VERSION 0.0.1 C CXX)

# Optional: Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Optional: override flags (CLion should use Debug/Release profiles)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Conditionally define ENABLE_LOGGING in debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(ENABLE_LOGGING)
endif()

# ---- Dependencies: Raylib ----
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if(NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# ---- Source Files ----
set(SOURCE_FILES
        main.cpp
        Title.cpp Title.h
        Gameplay.cpp Gameplay.h
        structures.cpp structures.h
        Player.cpp Player.h
        Collidable.cpp Collidable.h
        Cuboid.cpp Cuboid.h
        Developer_Tools/Developer_Tools.cpp
        Developer_Tools/Developer_Tools.h
        Developer_Tools/Logger.cpp
        Developer_Tools/Logger.h
        Developer_Tools/LoggerMacros.h
)

# ---- Create executable ----
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# ---- Link raylib (modern keyword-style) ----
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# ---- Link OpenMP if found ----
find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
    set(ENV{OMP_NUM_THREADS} 8)
    message(STATUS "OpenMP linked successfully.")
else()
    message(WARNING "OpenMP not found!")
endif()

# ---- Platform-specific Configurations ----

# Web build (Emscripten)
if(PLATFORM STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# macOS framework linking
if(APPLE)
    target_link_libraries(${PROJECT_NAME}
            "-framework IOKit"
            "-framework Cocoa"
            "-framework OpenGL"
    )
endif()
