//
// Created by Róbert Selvek on 15/05/2017.
//

#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <cli/ANSIPrinter.h>
#include <iostream>
#include <cli/views/SummaryUserView.h>
#include "UsersCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::UsersCommand::supported_params() const {
    std::vector<ParameterProps> parameters{
            {"db", "SQLite database to read from",
                    false, true, true, DEFAULT_DB_LOCATION},
            {"order", "(id, created, questions, answers, reputation, upvotes, downvotes) Field by which users are ordered",
                    false, true, true, "id"},
            {"direction", "(asc, desc) Direction in which to order users",
                    false, true, true, "asc"},
            {"limit", "Maximum number of returned users",
                    false, true, true, "20"},
            {"offset", "Number of users to skip in the beginning",
                    false, true, true, "0"}
    };
    return parameters;
}

std::string cli::UsersCommand::summary() const {
    return "Print users in order.";
}

std::string cli::UsersCommand::description() const {
    return "Prints a number of users ordered by the given criteria.";
}

void cli::UsersCommand::run(std::unordered_map<std::string, std::string> args) {
    std::string direction = args["direction"];
    if (direction != "asc" && direction != "desc") {
        std::cout << "Incorrect direction parameter." << std::endl;
        return;
    }
    int64_t limit;
    int64_t offset;
    try {
        limit = std::stoll(args["limit"]);
        offset = std::stoll(args["offset"]);
    } catch (std::invalid_argument e) {
        std::cout << "A parameter expecting a number received a textual value." << std::endl;
        return;
    }
    std::string order = args["order"];
    std::stringstream statementBody;
    if (order == "created") {
        order = "created_at";
    }
    if (order == "id" || order == "reputation" || order == "upvotes" || order == "downvotes" || order == "created_at") {
        statementBody << "SELECT id FROM users";
    } else if (order == "questions") {
        statementBody << "SELECT id, (SELECT COUNT(*) FROM posts WHERE post_type = 1 AND owner = users.id) AS questions FROM users";
    } else if (order == "answers") {
        statementBody << "SELECT id, (SELECT COUNT(*) FROM posts WHERE post_type = 2 AND owner = users.id) AS answers FROM users";
    } else {
        std::cout << "Incorrect order parameter." << std::endl;
        return;
    }

    statementBody << " ORDER BY " << order << " " << direction << " LIMIT ? OFFSET ?";
    try {
        sqlite::Client db(args["db"]);
        sqlite::Statement select(db, statementBody.str());
        select.bind(1, limit);
        select.bind(2, offset);
        std::unique_ptr<TerminalPrinter> p = getPrinter();
        while (select.step()) {
            SummaryUserView v(db, select.get<int64_t>(0));
            v.print(*p);
            p->newline();
        }
    } catch (sqlite::Exception e) {
        std::cout << "An error occurred when communicating with the database: " << e.what() << std::endl;
        return;
    }
}
