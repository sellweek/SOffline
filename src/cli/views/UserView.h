//
// Created by Róbert Selvek on 15/05/2017.
//

#ifndef SEMESTRALKA_USERVIEW_H
#define SEMESTRALKA_USERVIEW_H


#include <models.h>
#include <sqlite/SqliteClient.h>
#include <cli/TerminalPrinter.h>

namespace cli {
    class UserView {
    public:
        UserView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp) = 0;
    protected:
        models::User user;
        void print_reputation(TerminalPrinter &tp);
    };
}


#endif //SEMESTRALKA_USERVIEW_H
