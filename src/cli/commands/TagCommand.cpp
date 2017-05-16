//
// Created by Róbert Selvek on 16/05/2017.
//

#include <iostream>
#include <sqlite/SqliteStatement.h>
#include <cli/views/DetailedTagView.h>
#include <cli/ANSIPrinter.h>
#include "TagCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::TagCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to read from", false, true, true, DEFAULT_DB_LOCATION},
            {"name", "Name of the tag", false, true, false, ""},
    };
    return parameters;
}

std::string cli::TagCommand::summary() const {
    return "Show detailed tag view.";
}

std::string cli::TagCommand::description() const {
    return "Shows tag metadata, wiki article and questions tagged with the tag.";
}

void cli::TagCommand::run(std::unordered_map<std::string, std::string> args) {
    try {
        sqlite::Client db(args["db"]);
        sqlite::Statement idStmt(db, "SELECT id FROM tags WHERE name LIKE ?");
        idStmt.bind(1, args["name"]);
        bool tagFound = false;
        ANSIPrinter tp(std::cout);
        while (idStmt.step()) {
            tagFound = true;
            DetailedTagView(db, idStmt.get<int64_t>(0)).print(tp);
            tp.newline();
        }
        if (!tagFound) {
            std::cout << "No tag with given name found" << std::endl;
        }
    } catch (sqlite::Exception e) {
        std::cout << "An error occurred when communicating with the database: " << e.what() << std::endl;
        return;
    }
}
