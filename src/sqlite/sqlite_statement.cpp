//
// Created by Róbert Selvek on 07/04/2017.
//

#include "sqlite_statement.h"

namespace sqlite {

    Statement::Statement(Client &client, std::string statement) {
        int error = sqlite3_prepare_v2(client.get_db(), statement.c_str(), (int) statement.size(), &stmt, nullptr);
        if (error) {
            Exception exc(sqlite3_errmsg(client.get_db()));
        }
    }

    Statement::~Statement() {
        sqlite3_finalize(stmt);
    }

}