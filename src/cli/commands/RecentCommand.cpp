//
// Created by Róbert Selvek on 14/05/2017.
//

#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <iostream>
#include <cli/views/SummaryPostView.h>
#include <cli/ANSIPrinter.h>
#include "RecentCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::RecentCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to create or overwrite", false, true, true, DEFAULT_DB_LOCATION},
            {"limit", "Number of posts to show", false, true, true, "22"},
    };
    return parameters;
}

std::string cli::RecentCommand::summary() const {
    return "Print the most recently asked questions";
}

std::string cli::RecentCommand::description() const {
    return "Print the most recently asked questions.";
}

void cli::RecentCommand::run(std::unordered_map<std::string, std::string> args) {
    int64_t limit;
    try {
        limit = std::stoll(args["limit"]);
    } catch (std::invalid_argument e) {
        std::cout << "Limit must be an integer" << std::endl;
        return;
    }
    try {
        sqlite::Client db(args["db"]);
        sqlite::Statement select(db, "SELECT id FROM posts WHERE post_type=1 ORDER BY creation_date DESC LIMIT ?");
        select.bind(1, limit);
        std::unique_ptr<TerminalPrinter> p = getPrinter();
        while (select.step()) {
            auto id = select.get<int64_t>(0);
            SummaryPostView(db, id).print(*p);
            p->newline();
        }
    } catch (sqlite::Exception e) {
        std::cout << "An error occurred when communicating with the database: " << e.what() << std::endl;
        return;
    }
}
