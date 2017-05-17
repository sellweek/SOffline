//
// Created by Róbert Selvek on 15/05/2017.
//

#include <iostream>
#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <cli/ANSIPrinter.h>
#include <cli/views/DetailedUserView.h>
#include "UserCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::UserCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to read from", false, true, true, DEFAULT_DB_LOCATION},
            {"name", "Name of the user", false, true, false, ""},
    };
    return parameters;
}

std::string cli::UserCommand::summary() const {
    return "Show information about a user.";
}

std::string cli::UserCommand::description() const {
    return "Shows information about user with the given username. Users are matched using SQL LIKE operator.";
}

void cli::UserCommand::run(std::unordered_map<std::string, std::string> args) {
    try {
        sqlite::Client db(args["db"]);
        sqlite::Statement userIdStmt(db, "SELECT id FROM users WHERE display_name LIKE ?");
        userIdStmt.bind(1, args["name"]);
        std::vector<int64_t> userIds;
        while (userIdStmt.step()) {
            userIds.push_back(userIdStmt.get<int64_t>(0));
        }

        if (userIds.size() == 0) {
            printer->normal("No such user");
            printer->newline();
            return;
        }
        for (int64_t id : userIds) {
            DetailedUserView(db, id).print(*printer);
            printer->newline();
        }

    } catch (sqlite::Exception e) {
        log_sqlite_exception(e);
        return;
    }
}
