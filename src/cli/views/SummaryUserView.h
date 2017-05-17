//
// Created by Róbert Selvek on 15/05/2017.
//

#ifndef SEMESTRALKA_SUMMARYUSERVIEW_H
#define SEMESTRALKA_SUMMARYUSERVIEW_H


#include "UserView.h"

namespace cli {
    /**
    * Retrieves some metrics about user's activity and displays it together
    * with basic information about the user.
    */
    class SummaryUserView : public UserView {
    public:
        SummaryUserView(sqlite::Client &db, int64_t id);
        void print(TerminalPrinter &tp) override;
    private:
        int64_t questionCount;
        int64_t answerCount;
        int64_t acceptedCount;
    };
}

#endif //SEMESTRALKA_SUMMARYUSERVIEW_H
