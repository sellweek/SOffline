//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_STATEMENT_H
#define SEMESTRALKA_SQLITE_STATEMENT_H

#include <sqlite3.h>
#include "sqlite_client.h"

namespace sqlite {

    class Statement {
        Statement(Client &client, std::string statement);

        Statement(const Statement &) = delete;

        ~Statement();

    private:
        sqlite3_stmt *stmt;
    };

}
#endif //SEMESTRALKA_SQLITE_STATEMENT_H
