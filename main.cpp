#include <iostream>
#include <cstdint>
#include <chrono>
#include <string>
#include <fstream>
#include <xml/BadgeImporter.h>
#include <xml/CommentImporter.h>
#include <xml/HistoryImporter.h>
#include <xml/PostLinkImporter.h>

#include "src/sqlite/sqlite_client.h"
#include "src/sqlite/sqlite_statement.h"

#include "xml/PostImporter.h"
#include "models.h"

int main() {
    xml::PostImporter pi("/Users/selvek/Downloads/worldbuilding.stackexchange.com/Posts.xml");
    auto posts = pi.parse();
    std::cout << "Got " << posts.size() << " posts." << std::endl;
    xml::BadgeImporter bi("/Users/selvek/Downloads/worldbuilding.stackexchange.com/Badges.xml");
    auto badges = bi.parse();
    std::cout << "Got " << badges.size() << " badges." << std::endl;
    xml::CommentImporter ci("/Users/selvek/Downloads/worldbuilding.stackexchange.com/Comments.xml");
    auto comments = ci.parse();
    std::cout << "Got " << comments.size() << " comments." << std::endl;
    xml::HistoryImporter hi("/Users/selvek/Downloads/worldbuilding.stackexchange.com/PostHistory.xml");
    auto edits = hi.parse();
    std::cout << "Got " << edits.size() << " histories." << std::endl;
    xml::PostLinkImporter li("/Users/selvek/Downloads/worldbuilding.stackexchange.com/PostLinks.xml");
    auto links = li.parse();
    std::cout << "Got " << links.size() << " links." << std::endl;
    std::cout << "Done" << std::endl;
    /*
    std::cout << "Starting" << std::endl;
    sqlite::Client cl {"/Users/selvek/Dev/fit/PA2/semestralka/db.sqlite"};
    std::cout << "Database open" << std::endl;
    sqlite::Statement insert {cl, "INSERT INTO test(name) VALUES (?);"};
    auto value = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    std::cout << "Will insert " << value << std::endl;
    insert.bind(1, value);
    std::cout << "Statement created" << std::endl;
    bool result {insert.step()};
    std::cout << "Insert succeeded: " << !result << std::endl;
    sqlite::Statement select {cl, "SELECT id, name FROM test;"};
    while (select.step()) {
        std::cout << select.get<int64_t>(0) << ": " << select.get<std::string>(1) << std::endl;
    }
     */
    return 0;
}