cmake_minimum_required(VERSION 3.2)
project("threadedluajit")

file(GLOB CXX_SOURCES "src/*.cxx")

add_executable(engine ${CXX_SOURCES})