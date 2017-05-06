//
// Created by Róbert Selvek on 07/04/2017.
//

#include "sqlite_client.h"

namespace sqlite {

    Client::Client(const std::string &path) {
        int error = sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_READWRITE, nullptr);
        if (error) {
            Exception exc(sqlite3_errmsg(db));
            sqlite3_close(db);
            throw exc;
        }
    }

    Client::~Client() {
        sqlite3_close_v2(db);
    }

    int Client::max_variables() {
        return sqlite3_limit(db, SQLITE_LIMIT_VARIABLE_NUMBER, -1);
    }

}