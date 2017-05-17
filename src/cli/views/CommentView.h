//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_COMMENTVIEW_H
#define SEMESTRALKA_COMMENTVIEW_H

#include <sqlite/SqliteClient.h>
#include <cli/TerminalPrinter.h>
#include <models.h>
#include <cli/View.h>

namespace cli {
    /**
    * Retrieves and displays a single comment.
    */
    class CommentView : public View {
    public:
        CommentView(sqlite::Client &db, int64_t id);
        void print(cli::TerminalPrinter &tp);
    private:
        models::Comment comment;
        std::string userName;
    };
}



#endif //SEMESTRALKA_COMMENTVIEW_H
