cmake_minimum_required(VERSION 3.15)

project(raygame VERSION 0.0 LANGUAGES C CXX)

add_subdirectory(raylib)

set (CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

if (EMSCRIPTEN)
  target_link_options(${PROJECT_NAME} PRIVATE
    "-sUSE_GLFW=3"
    "-sASSERTIONS=1"
    "-sWASM=1"
    "-sGL_ENABLE_GET_PROC_ADDRESS=1"
    "--shell-file=${PROJECT_SOURCE_DIR}/raylib/src/minshell.html"
    "--preload-file=${PROJECT_SOURCE_DIR}/res@/res"
    )
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "")

target_include_directories(${PROJECT_NAME} PRIVATE raylib/src)

target_link_libraries(${PROJECT_NAME} raylib)
