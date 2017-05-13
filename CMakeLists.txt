cmake_minimum_required(VERSION 3.7)
project(semestralka)

add_custom_target(doc doxygen Doxyfile)

set(CMAKE_CXX_STANDARD 11)

#set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address" )

set(SOURCE_FILES main.cpp src/sqlite/sqlite_client.cpp src/sqlite/sqlite_client.h src/sqlite/sqlite_statement.h src/models.h src/import/XMLAttributeImporter.h src/import/xml_util.h src/models.cpp src/import/import.cpp src/cli/Commander.cpp src/cli/Commander.h src/cli/Command.cpp src/cli/Command.h src/cli/ParameterProps.h src/cli/commands/TestCommand.cpp src/cli/commands/TestCommand.h src/cli/commands/ImportCommand.cpp src/cli/commands/ImportCommand.h)

find_package(PkgConfig)
pkg_check_modules(sqlite3 REQUIRED)

set(TINYXML2_FILES include/tinyxml2.h include/tinyxml2.cpp)
add_library(TinyXML2 STATIC ${TINYXML2_FILES})

include_directories(${semestralka_SOURCE_DIR}/include)
include_directories(${semestralka_SOURCE_DIR}/src)

add_executable(semestralka ${SOURCE_FILES})

target_link_libraries(semestralka sqlite3 TinyXML2)