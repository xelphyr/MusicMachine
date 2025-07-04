cmake_minimum_required(VERSION 3.22)
project(3DASCII VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows" AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -lwinpthread")

endif()

# === Project Source Files ===
set(SRC_FILES
    src/main.cpp
)

# === Executable Target ===
add_executable(MusicMachine ${SRC_FILES})

# === Include Directories ===
target_include_directories(MusicMachine PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# === SDL ===
set(SDL3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl/include")

set(SDL3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl/lib/x64/SDL3.lib")

target_include_directories(MusicMachine PRIVATE
    ${SDL3_INCLUDE_DIR}
)

target_link_libraries(MusicMachine PRIVATE
    ${SDL3_LIBRARY}
)

# === SDL_Image ===
set(SDL3_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl_image/include")
set(SDL3_IMAGE_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl_image/lib/x64/SDL3_image.lib")

target_include_directories(MusicMachine PRIVATE
    ${SDL3_IMAGE_INCLUDE_DIR}
)

target_link_libraries(MusicMachine PRIVATE
    ${SDL3_IMAGE_LIBRARY}
)

# === ImGui ===
file(GLOB IMGUI_SRC
    lib/imgui/*.cpp
    lib/imgui/backends/imgui_impl_sdl3.cpp
    lib/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    lib/imgui
    lib/imgui/backends
    ${SDL3_INCLUDE_DIR}
    ${SDL3_IMAGE_INCLUDE_DIR}
)

# ===Link Dependencies===
target_link_libraries(MusicMachine PRIVATE
    imgui
    ${SDL3_LIBRARY}
    ${SDL3_IMAGE_LIBRARY}
    opengl32
    winmm
    gdi32
    user32
    shell32
    ole32
    imm32
    version
)

add_custom_command(TARGET MusicMachine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/sdl/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:MusicMachine>
)