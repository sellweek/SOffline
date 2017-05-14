//
// Created by Róbert Selvek on 14/05/2017.
//

#include "SummaryPostView.h"
#include "PostView.h"

cli::SummaryPostView::SummaryPostView(sqlite::Client &db, int64_t id): PostView(db, id) {}

void cli::SummaryPostView::print(cli::TerminalPrinter &tp) {
    PostView::print(tp);
    tp.normal(" ");
    tp.underline(post.title);
}
