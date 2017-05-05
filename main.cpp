#include <iostream>
#include <cstdint>
#include <chrono>
#include <string>
#include <fstream>

#include "src/sqlite/sqlite_client.h"
#include "src/sqlite/sqlite_statement.h"

#include "xml/import.h"
#include "models.h"

int main() {
    auto results = xml::import_all("/Users/selvek/Downloads/worldbuilding.stackexchange.com");
    std::cout << "Done, got " << results.users.size() << " users." << std::endl;
    std::cout << "Starting" << std::endl;
    sqlite::Client cl {"/Users/selvek/Dev/fit/PA2/semestralka/db.sqlite"};
    std::cout << "Database open" << std::endl;
    std::vector <models::Model*> ptr_vec;
    sqlite::Statement userStmt(cl, "users", results.users);
    userStmt.step();
    std::cout << "Users saved" << std::endl;
    sqlite::Statement badgeStmt(cl, "badges", results.badges);
    badgeStmt.step();
    std::cout << "Badges saved" << std::endl;
    sqlite::Statement postStmt(cl, "posts", results.posts);
    postStmt.step();
    std::cout << "Posts saved" << std::endl;
    sqlite::Statement commentStmt(cl, "comments", results.comments);
    commentStmt.step();
    std::cout << "Comments saved" << std::endl;
    sqlite::Statement historyStmt(cl, "post_history", results.changes);
    historyStmt.step();
    std::cout << "History saved" << std::endl;
    sqlite::Statement linkStmt(cl, "post_links", results.links);
    linkStmt.step();
    std::cout << "Links saved" << std::endl;
    sqlite::Statement tagStmt(cl, "tags", results.tags);
    tagStmt.step();
    std::cout << "Tags saved" << std::endl;
    sqlite::Statement voteStmt(cl, "votes", results.votes);
    voteStmt.step();
    std::cout << "Votes saved" << std::endl;
    return 0;
}