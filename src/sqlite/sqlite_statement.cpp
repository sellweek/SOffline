//
// Created by Róbert Selvek on 07/04/2017.
//

#include <cstring>

#include "sqlite_statement.h"

namespace sqlite {
    void free_c_str(void *str) {
        delete [] (char *) str;
    }

    Statement::Statement(Client &client, std::string statement) : client(client) {
        int error = sqlite3_prepare_v2(client.get_db(), statement.c_str(), (int) statement.size(), &stmt, nullptr);
        if (error) {
            sqlite3_finalize(stmt);
            check_error(error);
        }
    }

    Statement::~Statement() {
        sqlite3_finalize(stmt);
    }

    void Statement::bind(size_t idx, int64_t val) {
        check_error(sqlite3_bind_int64(stmt, idx, val));
    }

    void Statement::bind(size_t idx, double val) {
        check_error(sqlite3_bind_double(stmt, idx, val));
    }

    void Statement::bind(size_t idx, std::string val) {
        size_t len = val.size();
        char *copy = new char[len];
        strncpy(copy, val.c_str(), len);
        check_error(sqlite3_bind_text(stmt, idx, copy, len, &free_c_str));
    }

    void Statement::bind_null(size_t idx) {
        check_error(sqlite3_bind_null(stmt, idx));
    }

    bool Statement::step() {
        int result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            return true;
        } else if (result == SQLITE_DONE) {
            return false;
        }
        check_error(result);
        return false;
    }

    int Statement::columns() {
        return sqlite3_column_count(stmt);
    }


}