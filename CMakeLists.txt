cmake_minimum_required(VERSION 3.2)
project("threadedluajit" CXX)

file(GLOB CXX_SOURCES "src/*.cxx")
add_executable(engine ${CXX_SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Modules)

find_package(LuaJIT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

add_custom_target(copy-scripts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/scripts ${CMAKE_BINARY_DIR}/scripts
)

add_custom_target(build-luajit
    COMMAND make -C ${CMAKE_SOURCE_DIR}/ext/LuaJIT/src -j24
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/ext/LuaJIT/src/libluajit.* ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/ext/LuaJIT/src/lua.hpp ${CMAKE_SOURCE_DIR}/src
)

add_library(libluajit.a STATIC IMPORTED)
set_property(TARGET libluajit.a PROPERTY IMPORTED_LOCATION libluajit.so)

add_dependencies(engine
    build-luajit
    copy-scripts
)

target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/ext/LuaJIT/src)
target_link_libraries(engine ${CMAKE_BINARY_DIR}/libluajit.a glfw vulkan)