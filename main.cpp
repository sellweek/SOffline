#include <iostream>
#include <cstdint>

#include "src/sqlite/sqlite_client.h"
#include "src/sqlite/sqlite_statement.h"

int main() {
    std::cout << "Starting" << std::endl;
    sqlite::Client cl {"/Users/selvek/Dev/fit/PA2/semestralka/db.sqlite"};
    std::cout << "Database open" << std::endl;
    sqlite::Statement insert {cl, "INSERT INTO test(name) VALUES ('Robert');"};
    std::cout << "Statement created" << std::endl;
    bool result {insert.step()};
    std::cout << "Insert succeeded: " << !result << std::endl;
    sqlite::Statement select {cl, "SELECT id, name FROM test;"};
    while (select.step()) {
        std::cout << select.get<int64_t>(0) << ": " << select.get<std::string>(1) << std::endl;
    }
    return 0;
}