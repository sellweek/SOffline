//
// Created by Róbert Selvek on 16/05/2017.
//

#ifndef SEMESTRALKA_SUMMARYTAGVIEW_H
#define SEMESTRALKA_SUMMARYTAGVIEW_H

#include "TagView.h"

namespace cli {
    /**
    * Retrieves basic metrics about a tag and displays them together with its information.
    */
    class SummaryTagView : public TagView {
    public:
        SummaryTagView(sqlite::Client &db, int64_t id);
        void print(TerminalPrinter &tp) override;
    private:
        std::string description;
    };
}



#endif //SEMESTRALKA_SUMMARYTAGVIEW_H
