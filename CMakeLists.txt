cmake_minimum_required(VERSION 3.7)
project(semestralka)

add_custom_target(doc doxygen Doxyfile)

set(CMAKE_CXX_STANDARD 11)

#set(CXX g++-7)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pedantic -Wall" )

set(SOURCE_FILES main.cpp src/sqlite/SqliteClient.cpp src/sqlite/SqliteClient.h src/sqlite/SqliteStatement.h src/models.h src/import/XMLAttributeImporter.h src/import/xml_util.h src/models.cpp src/import/import.cpp src/cli/Commander.cpp src/cli/Commander.h src/cli/Command.cpp src/cli/Command.h src/cli/ParameterProps.h src/cli/commands/ImportCommand.cpp src/cli/commands/ImportCommand.h src/cli/views/PostView.cpp src/cli/views/PostView.h src/cli/TerminalPrinter.cpp src/cli/TerminalPrinter.h src/cli/NoOpPrinter.cpp src/cli/NoOpPrinter.h src/cli/ANSIPrinter.cpp src/cli/ANSIPrinter.h src/cli/views/helpers.cpp src/cli/views/helpers.h src/cli/commands/ShowPostCommand.cpp src/cli/commands/ShowPostCommand.h src/cli/commands/ThreadCommand.cpp src/cli/commands/ThreadCommand.h src/cli/views/CommentView.cpp src/cli/views/CommentView.h src/cli/views/DetailedPostView.cpp src/cli/views/DetailedPostView.h src/cli/views/SummaryPostView.cpp src/cli/views/SummaryPostView.h src/cli/commands/RecentCommand.cpp src/cli/commands/RecentCommand.h src/cli/commands/SearchCommand.cpp src/cli/commands/SearchCommand.h src/cli/views/UserView.cpp src/cli/views/UserView.h src/cli/views/DetailedUserView.cpp src/cli/views/DetailedUserView.h src/cli/commands/UserCommand.cpp src/cli/commands/UserCommand.h src/cli/views/SummaryUserView.cpp src/cli/views/SummaryUserView.h src/cli/commands/UsersCommand.cpp src/cli/commands/UsersCommand.h src/cli/views/TagView.cpp src/cli/views/TagView.h src/cli/commands/TagsCommand.cpp src/cli/commands/TagsCommand.h)

find_package(PkgConfig)
pkg_check_modules(sqlite3 REQUIRED)

set(TINYXML2_FILES include/tinyxml2.h include/tinyxml2.cpp)
add_library(TinyXML2 STATIC ${TINYXML2_FILES})

include_directories(${semestralka_SOURCE_DIR}/include)
include_directories(${semestralka_SOURCE_DIR}/src)

add_executable(semestralka ${SOURCE_FILES})

target_link_libraries(semestralka sqlite3 TinyXML2)