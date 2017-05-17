//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_DETAILEDPOSTVIEW_H
#define SEMESTRALKA_DETAILEDPOSTVIEW_H

#include "PostView.h"

namespace cli {
    /**
    * Retrieves and displays detailed information about a post, as well as its title and text.
    */
    class DetailedPostView : public PostView {
    public:
        DetailedPostView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp) override;
        std::vector<CommentView> comments;
        std::vector<std::string> tags;
    };
}



#endif //SEMESTRALKA_DETAILEDPOSTVIEW_H
