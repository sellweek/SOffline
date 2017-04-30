//
// Created by Róbert Selvek on 30/04/2017.
//

#include <ostream>

#include "models.h"

namespace models {
    std::ostream &operator<<(std::ostream &os, const models::Badge &b) {
        os << "Badge " << b.id
           << " is " << b.name
           << " for user " << b.user
           << " awarded on " << std::put_time(&b.date, "%c")
           << " has class ID " << b.badge_class << " (" << b.tag_based << ")";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const models::PostHistoryEntry &h) {
        os << "HistoryEntry " << h.id
           << " by user " << h.user
           << " was made on " << std::put_time(&h.date, "%c")
           << " has type " << h.type
           << " with a comment of " << h.comment
           << " and its body is " << std::endl << h.text;
        return os;
    }
}