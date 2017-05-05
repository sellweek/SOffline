#ifndef SEMESTRALKA_IMPORT_H
#define SEMESTRALKA_IMPORT_H

#include <vector>

#include "models.h"

namespace xml {
    struct ImportResults {
        std::vector<models::Badge> badges;
        std::vector<models::Comment> comments;
        std::vector<models::PostHistoryEntry> changes;
        std::vector<models::PostLink> links;
        std::vector<models::Post> posts;
        std::vector<models::Tag> tags;
        std::vector<models::User> users;
        std::vector<models::Vote> votes;
    };

    ImportResults import_all(std::string sourceDirectory);
}

#endif