cmake_minimum_required(VERSION 3.7)
project(semestralka)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/sqlite/sqlite_client.cpp src/sqlite/sqlite_client.h src/sqlite/sqlite_statement.cpp src/sqlite/sqlite_statement.h)

find_package(PkgConfig)
pkg_check_modules(sqlite3 REQUIRED)

add_executable(semestralka ${SOURCE_FILES})

target_link_libraries(semestralka sqlite3)