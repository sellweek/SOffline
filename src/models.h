//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_MODELS_H
#define SEMESTRALKA_MODELS_H

#include <cstdint>
#include <string>
#include <ctime>
#include <iomanip>
#include <ostream>

namespace models {

    struct Badge {
        int64_t id;
        int64_t user;
        std::string name;
        std::tm date;
        int64_t badge_class;
        bool tag_based;
    };

    std::ostream &operator <<(std::ostream &os, const models::Badge &b);

    struct Comment {
        int64_t id;
        int64_t post;
        int64_t score;
        std::string text;
        std::tm date;
        int64_t user;
    };



    struct PostHistoryEntry {
        int64_t id;
        int64_t post;
        int64_t type;
        int64_t user;
        std::tm date;
        std::string guid;
        std::string comment;
        std::string text;
    };

    std::ostream &operator<<(std::ostream &os, const models::PostHistoryEntry &h);

    struct PostLink {
        int64_t id;
        int64_t source;
        int64_t target;
        int64_t type;
        std::tm date;
    };

    struct Post {
        int64_t id;
        int64_t type;
        int64_t parent;

        int64_t accepted_answer;

        int64_t score;
        int64_t views;

        std::string title;
        std::string body;

        int64_t owner;
        int64_t last_editor;
        std::tm last_edit;
        std::tm last_activity;
        std::tm created_at;
        std::tm closed_at;
    };

    struct Tag {
        int64_t id;
        int64_t wiki;
        int64_t excerpt;
        std::string name;
    };

    struct User {
        int64_t id;
        int64_t reputation;
        int64_t upvotes;
        int64_t downvotes;
        int64_t account_id;
        std::string display_name;
        std::string website;
        std::string location;
        std::string about;
        std::tm created_at;
        std::tm last_access;
    };

    struct Vote {
        int64_t id;
        int64_t post;
        int64_t type;
        int64_t user;
    };

}
#endif //SEMESTRALKA_MODELS_H