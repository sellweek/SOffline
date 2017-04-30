cmake_minimum_required(VERSION 3.7)
project(semestralka)

add_custom_target(doc doxygen Doxyfile)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/sqlite/sqlite_client.cpp src/sqlite/sqlite_client.h src/sqlite/sqlite_statement.cpp src/sqlite/sqlite_statement.h src/models.h src/xml/XMLAttributeImporter.h src/xml/util.h src/xml/PostImporter.cpp src/xml/PostImporter.h src/xml/BadgeImporter.cpp src/xml/BadgeImporter.h src/xml/CommentImporter.cpp src/xml/CommentImporter.h src/xml/HistoryImporter.cpp src/xml/HistoryImporter.h src/models.cpp src/xml/PostLinkImporter.cpp src/xml/PostLinkImporter.h src/xml/TagImporter.cpp src/xml/TagImporter.h)

find_package(PkgConfig)
pkg_check_modules(sqlite3 REQUIRED)

set(TINYXML2_FILES include/tinyxml2.h include/tinyxml2.cpp)
add_library(TinyXML2 STATIC ${TINYXML2_FILES})

include_directories(${semestralka_SOURCE_DIR}/include)
include_directories(${semestralka_SOURCE_DIR}/src)

add_executable(semestralka ${SOURCE_FILES})

target_link_libraries(semestralka sqlite3 TinyXML2)