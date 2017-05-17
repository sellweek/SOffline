//
// Created by Róbert Selvek on 14/05/2017.
//

#include <iostream>

#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <cli/ANSIPrinter.h>
#include <cli/views/DetailedPostView.h>
#include "ThreadCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::ThreadCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to read from", false, true, true, DEFAULT_DB_LOCATION},
            {"id", "ID of a post from the thread", false, true, false, ""},
    };
    return parameters;
}

std::string cli::ThreadCommand::summary() const {
    return "Show a whole question-answer thread.";
}

std::string cli::ThreadCommand::description() const {
    return "Shows a thread, like you'd get in the web interface. The id parameter doesn't need to be "
            "the question's ID, it only needs to belong to either the question or one of the answers.";
}

void cli::ThreadCommand::run(std::unordered_map<std::string, std::string> args) {
    int64_t postId;
    try {
        postId = std::stoll(args["id"]);
    } catch (std::invalid_argument e) {
        std::cout << "Post ID must be an integer" << std::endl;
        return;
    }
    try {
        sqlite::Client db(args["db"]);
        auto parent = get_post_parent(db, postId);
        auto answers = get_answers(db, parent);
        try {
            DetailedPostView parentView(db, parent);
            printer->reverse("QUESTION:");
            printer->newline();
            parentView.print(*printer);
            if (parentView.post.acceptedAnswer != 0) {
                printer->newline();
                printer->reverse("ACCEPTED ANSWER:");
                printer->newline();
                DetailedPostView(db, parentView.post.acceptedAnswer).print(*printer);
            }
            if (answers.size() != 0) {
                printer->newline();
                printer->reverse("ANSWERS:");
                printer->newline();
                for (int64_t answerId : answers) {
                    if (answerId != parentView.post.acceptedAnswer) {
                        DetailedPostView(db, answerId).print(*printer);
                    }
                }
            } else {
                printer->newline();
                printer->bold("Oops, it seems this post has no answers. :(");
                printer->newline();
            }
        } catch (DoesNotExistException e) {
            printer->normal("This post doesn't exist.");
            printer->newline();
        }

    } catch (sqlite::Exception e) {
        log_sqlite_exception(e);
        return;
    }
}

int64_t cli::ThreadCommand::get_post_parent(sqlite::Client &db, int64_t postId) {
    sqlite::Statement parent(db, "SELECT parent FROM posts WHERE id = ?");
    parent.bind(1, postId);
    parent.step();
    int64_t parentId = parent.get<int64_t>(0);
    if (parentId == 0) {
        return postId;
    }
    return parentId;
}

std::vector<int64_t> cli::ThreadCommand::get_answers(sqlite::Client &db, int64_t postId) {
    sqlite::Statement select(db, "SELECT id FROM posts WHERE parent = ? AND post_type = 2 ORDER BY score DESC");
    select.bind(1, postId);
    std::vector<int64_t> results;
    while (select.step()) {
        results.push_back(select.get<int64_t>(0));
    }
    return results;
}
