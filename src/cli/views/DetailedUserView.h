//
// Created by Róbert Selvek on 15/05/2017.
//

#ifndef SEMESTRALKA_DETAILEDUSERVIEW_H
#define SEMESTRALKA_DETAILEDUSERVIEW_H

#include "UserView.h"
#include "SummaryPostView.h"

namespace cli {
    /**
    * Displays information about a user together with their posts.
    */
    class DetailedUserView : public UserView {
    public:
        DetailedUserView(sqlite::Client &db, int64_t id);
        void print(TerminalPrinter &tp) override;
    private:
        std::vector<SummaryPostView> asked_questions;
        std::vector<SummaryPostView> answered_questions;
    };
}



#endif //SEMESTRALKA_DETAILEDUSERVIEW_H
