//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_MODELS_H
#define SEMESTRALKA_MODELS_H

#include <cstdint>
#include <string>
#include <chrono>

struct Badge {
    int64_t id;
    int64_t user;
    std::string name;
    std::chrono::system_clock::time_point date;
    int64_t badge_class;
    bool tag_based;
};

struct Comment {
    int64_t id;
    int64_t post;
    int64_t score;
    std::string text;
    std::chrono::system_clock::time_point date;
    int64_t user;
};

struct PostHistoryEntry {
    int64_t id;
    int64_t post;
    int64_t type;
    int64_t user;
    std::chrono::system_clock::time_point date;
    std::string guid;
    std::string comment;
    std::string text;
};

struct PostLink {
    int64_t id;
    int64_t source;
    int64_t target;
    int64_t type;
    std::chrono::system_clock::time_point date;
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
    std::chrono::system_clock::time_point last_edit;
    std::chrono::system_clock::time_point last_activity;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point closed_at;
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
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point last_access;
};

struct Vote {
    int64_t id;
    int64_t post;
    int64_t type;
    int64_t user;
};
#endif //SEMESTRALKA_MODELS_H
