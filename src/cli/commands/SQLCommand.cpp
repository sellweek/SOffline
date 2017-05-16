//
// Created by Róbert Selvek on 16/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include <cli/views/CommentView.h>
#include <cli/views/SummaryPostView.h>
#include <cli/views/SummaryTagView.h>
#include <cli/views/SummaryUserView.h>
#include "SQLCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::SQLCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to read from", false, true, true, DEFAULT_DB_LOCATION},
            {"sql", "SQL query returning IDs of objects to show", false, true, false, ""},
            {"model", "(comment, post, tag, user) Model which has its IDs returned", false, true, false, ""},
    };
    return parameters;
}

std::string cli::SQLCommand::summary() const {
    return "Execute an SQL query against the database and show its results.";
}

std::string cli::SQLCommand::description() const {
    return "Executes an SQL query against the database and shows its results. The query should return IDs of objects "
            "specified in the model argument.";
}

void cli::SQLCommand::run(std::unordered_map<std::string, std::string> args) {
    try {
        sqlite::Client db(args["db"]);
        sqlite::Statement stmt(db, args["sql"]);
        std::unique_ptr<TerminalPrinter> p = getPrinter();
        std::string model = args["model"];
        while (stmt.step()) {
            if (stmt.columns() > 1) {
                p->normal("Too many selected elements.");
                p->newline();
                return;
            }
            int64_t id = stmt.get<int64_t>(0);

            if (model == "comment") {
                CommentView(db, id).print(*p);
            } else if (model == "post") {
                SummaryPostView(db, id).print(*p);
            } else if (model == "tag") {
                SummaryTagView(db, id).print(*p);
            } else if (model == "user") {
                SummaryUserView(db, id).print(*p);
            } else {
                p->normal("No such model");
                p->newline();
                return;
            }
            p->newline();
        }
    } catch (sqlite::Exception e) {
        auto p = getPrinter();
        p->normal("An error occurred when communicating with the database: ");
        p->normal(e.what());
        p->newline();
        return;
    }
}
