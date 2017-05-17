//
// Created by Róbert Selvek on 15/05/2017.
//

#ifndef SEMESTRALKA_USERVIEW_H
#define SEMESTRALKA_USERVIEW_H


#include <models.h>
#include <sqlite/SqliteClient.h>
#include <cli/TerminalPrinter.h>
#include <cli/View.h>

namespace cli {
    /**
    * Retrieves and displays basic information about a user.
    */
    class UserView : public View {
    public:
        UserView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp) = 0;
    protected:
        models::User user;
        void print_reputation(TerminalPrinter &tp);
    };
}


#endif //SEMESTRALKA_USERVIEW_H
