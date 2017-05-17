//
// Created by Róbert Selvek on 16/05/2017.
//

#ifndef SEMESTRALKA_DETAILEDTAGVIEW_H
#define SEMESTRALKA_DETAILEDTAGVIEW_H

#include "TagView.h"
#include "SummaryPostView.h"

namespace cli {
    /**
    * Retrieves posts associated with a tag and displays their summaries along with tag information.
    */
    class DetailedTagView : public TagView {
    public:
        DetailedTagView(sqlite::Client &db, int64_t id);
        void print(TerminalPrinter &tp) override;

    private:
        std::string description;
        std::vector<SummaryPostView> questions;
    };
}



#endif //SEMESTRALKA_DETAILEDTAGVIEW_H
