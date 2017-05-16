//
// Created by Róbert Selvek on 16/05/2017.
//

#include <iostream>
#include <sstream>
#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <cli/ANSIPrinter.h>
#include <cli/views/SummaryTagView.h>
#include "TagsCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::TagsCommand::supported_params() const {
    std::vector<ParameterProps> parameters{
            {"db", "SQLite database to read from",
                    false, true, true, DEFAULT_DB_LOCATION},
            {"order", "(id, name, questions) Field by which tags are ordered",
                    false, true, true, "id"},
            {"direction", "(asc, desc) Direction in which to order tags",
                    false, true, true, "asc"},
            {"limit", "Maximum number of returned tags",
                    false, true, true, "20"},
            {"offset", "Number of tags to skip in the beginning",
                    false, true, true, "0"}
    };
    return parameters;
}

std::string cli::TagsCommand::summary() const {
    return "Print tags ordered by a criterium";
}

std::string cli::TagsCommand::description() const {
    return "Prints a number of tags and their brief descriptions, ordered by a specified column.";
}

void cli::TagsCommand::run(std::unordered_map<std::string, std::string> args) {
    int64_t limit, offset;
    try {
        limit = std::stoll(args["limit"]);
        offset = std::stoll(args["offset"]);
    } catch (std::invalid_argument e) {
        std::cout << "A parameter expecting a number received a textual value." << std::endl;
        return;
    }
    if (args["direction"] != "asc" && args["direction"] != "desc") {
        std::cout << "Incorrect direction parameter." << std::endl;
        return;
    }
    std::string order = args["order"];
    std::stringstream statementBody;
    if (order == "id" || order == "name") {
        statementBody << "SELECT id FROM tags";
    } else if (order == "questions") {
        statementBody
                << "SELECT id, (SELECT COUNT(*) FROM post_tags WHERE tag = tags.id) AS questions FROM tags";
    } else {
        std::cout << "Incorrect order parameter." << std::endl;
        return;
    }
    statementBody << " ORDER BY " << order << " " << args["direction"] << " LIMIT ? OFFSET ?";
    try {
        sqlite::Client db(args["db"]);
        sqlite::Statement select(db, statementBody.str());
        select.bind(1, limit);
        select.bind(2, offset);
        std::unique_ptr<TerminalPrinter> p = getPrinter();
        while (select.step()) {
            SummaryTagView v(db, select.get<int64_t>(0));
            v.print(*p);
            p->newline();
        }
    } catch (sqlite::Exception e) {
        std::cout << "An error occurred when communicating with the database: " << e.what() << std::endl;
        return;
    }
}
