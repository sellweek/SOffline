//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_STATEMENT_H
#define SEMESTRALKA_SQLITE_STATEMENT_H

#include <sqlite3.h>
#include <cstdint>
#include <iterator>

#include "sqlite_client.h"

namespace sqlite {

    class Statement {
    public:
        Statement(Client &client, std::string statement);

        Statement(const Statement &) = delete;

        ~Statement();

        void bind(size_t idx, int64_t val);
        void bind(size_t idx, double val);
        void bind(size_t idx, std::string val);
        void bind_null(size_t idx);

        bool step();

        int columns();

        template <typename T>
        T get(size_t col);


    private:
        sqlite3_stmt *stmt;
        Client &client;

        void check_error(int code) {
            if (code) {
                sqlite3_finalize(stmt);
                throw Exception(sqlite3_errmsg(client.get_db()));
            }
        }

        void check_get_preconditions(size_t col) {
            if (col >= columns()) {
                throw ColumnOutOfBoundsException();
            }
        }
    };

    template <>
    inline int64_t Statement::get<int64_t>(size_t col) {
        check_get_preconditions(col);
        return sqlite3_column_int64(stmt, col);
    }

    template <>
    inline double Statement::get<double>(size_t col) {
        check_get_preconditions(col);
        return sqlite3_column_double(stmt, col);
    }

    template<>
    inline std::string Statement::get<std::string>(size_t col) {
        check_get_preconditions(col);
        // res will not be freed by me, because sqlite3 manages
        // its storage duration automagically
        const unsigned char *res = sqlite3_column_text(stmt, col);
        if (res == nullptr) {
            return std::string("");
        }
        return std::string((const char *) res);
    }

}
#endif //SEMESTRALKA_SQLITE_STATEMENT_H
