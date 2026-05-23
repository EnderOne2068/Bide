cmake_minimum_required(VERSION 3.16)
project(Bide VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN -DNOMINMAX)
    set(PLATFORM_SOURCES
        src/platform/platform_windows.cpp
    )
    set(PLATFORM_LIBS ws2_32 user32 gdi32 shell32)
elseif(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    set(PLATFORM_SOURCES
        src/platform/platform_linux.cpp
    )
    set(PLATFORM_LIBS ${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

add_executable(bide
    src/main.cpp
    src/editor/editor.cpp
    src/editor/highlighter.cpp
    src/compiler/compiler.cpp
    src/compiler/cintsys.cpp
    src/ui/window.cpp
    src/ui/renderer.cpp
    src/platform/platform.cpp
    ${PLATFORM_SOURCES}
)

target_include_directories(bide PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(bide PRIVATE ${PLATFORM_LIBS})

if(MSVC)
    target_compile_options(bide PRIVATE /W4 /permissive-)
else()
    target_compile_options(bide PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS bide RUNTIME DESTINATION bin)
