//
// Created by Róbert Selvek on 14/05/2017.
//

#include <iostream>
#include <sqlite/SqliteStatement.h>
#include <cli/ANSIPrinter.h>
#include <cli/views/SummaryPostView.h>
#include "SearchCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::SearchCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to create or overwrite", false, true, true, DEFAULT_DB_LOCATION},
            {"limit", "Number of posts to show", false, true, true, "22"},
            {"text", "Text to search for, using SQL LIKE syntax", false, true, false, ""},
            {"include-body", "Include post bodies in search", true, false, false, ""},
            {"include-answers", "Include answers in search", true, false, false, ""},
    };
    return parameters;
}

std::string cli::SearchCommand::summary() const {
    return "Search for questions and answers";
}

std::string cli::SearchCommand::description() const {
    return "Searches for questions and (possibly) answers containing the given text.sqlqqq";
}

void cli::SearchCommand::run(std::unordered_map<std::string, std::string> args) {
    int64_t limit;
    try {
        limit = std::stoll(args["limit"]);
    } catch (std::invalid_argument e) {
        std::cout << "Limit must be an integer" << std::endl;
        return;
    }
    size_t placeholders = 1;
    std::string whereTextSource("(posts.title LIKE ? ");
    if (args.find("include-body") != args.end()) {
        whereTextSource += "OR posts.body LIKE ?";
        placeholders++;
    }
        whereTextSource += ")";
    std::string wherePostType("(posts.post_type = 1 ");
    if (args.find("include-answers") != args.end()) {
        wherePostType += "OR posts.post_type = 2";
    }
    wherePostType += ")";
    try {
        sqlite::Client db(args["db"]);
        std::string statementBody = "SELECT id FROM POSTS WHERE "  + whereTextSource + " AND " + wherePostType + "ORDER BY score LIMIT ?";
        sqlite::Statement select(db, statementBody);
        for (int i = 1; i <= placeholders; i++) {
            select.bind(i, args["text"]);
        }
        select.bind(placeholders+1, limit);
        ANSIPrinter p(std::cout);
        while (select.step()) {
            auto id = select.get<int64_t>(0);
            SummaryPostView(db, id).print(p);
            p.newline();
        }
    } catch (sqlite::Exception e) {
        std::cout << "An error occurred when communicating with the database: " << e.what() << std::endl;
        return;
    }
}
