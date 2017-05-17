//
// Created by Róbert Selvek on 16/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include <cli/views/CommentView.h>
#include <cli/views/SummaryPostView.h>
#include <cli/views/SummaryTagView.h>
#include <cli/views/SummaryUserView.h>
#include <cli/views/helpers.h>
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
        std::string model = args["model"];
        while (stmt.step()) {
            if (stmt.columns() > 1) {
                printer->normal("Too many selected elements.");
                printer->newline();
                return;
            }
            int64_t id = stmt.get<int64_t>(0);

            if (model == "comment") {
                CommentView(db, id).print(*printer);
            } else if (model == "post") {
                SummaryPostView(db, id).print(*printer);
            } else if (model == "tag") {
                SummaryTagView(db, id).print(*printer);
            } else if (model == "user") {
                SummaryUserView(db, id).print(*printer);
            } else {
                printer->normal("No such model");
                printer->newline();
                return;
            }
            printer->newline();
        }
    } catch (sqlite::Exception e) {
        log_sqlite_exception(e);
        return;
    } catch (DoesNotExistException e) {
        printer->normal("One of the IDs returned by the SQL query was not found. Did you use the correct model?");
        printer->newline();
        return;
    }
}
