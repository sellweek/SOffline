//
// Created by Róbert Selvek on 14/05/2017.
//

#include "ShowPostCommand.h"
#include <sqlite/SqliteStatement.h>
#include <iostream>
#include <cli/views/PostView.h>
#include <cli/ANSIPrinter.h>
#include <cli/views/helpers.h>

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::ShowPostCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to read from", false, true, true, DEFAULT_DB_LOCATION},
            {"id", "ID of the post to show", false, true, false, ""},
    };
    return parameters;
}

std::string cli::ShowPostCommand::summary() const {
    return "Show the post with the given ID";
}

std::string cli::ShowPostCommand::description() const {
    return "Displays information and body of a post with the requested ID";
}

void cli::ShowPostCommand::run(std::unordered_map<std::string, std::string> args) {
    int64_t postId;
    try {
        postId = std::stoll(args["id"]);
    } catch (std::invalid_argument e) {
        std::cout << "Post ID must be an integer" << std::endl;
        return;
    }
    try {
        sqlite::Client db(args["db"]);
        try {
            PostView post(db, postId);
            ANSIPrinter p(std::cout);
            post.print(p);
        } catch (DoesNotExistException e) {
            std::cout << "This post doesn't exist." << std::endl;
        }

    } catch (sqlite::Exception e) {
        std::cout << "An error occurred when communicating with the database: " << e.what() << std::endl;
        return;
    }
}
