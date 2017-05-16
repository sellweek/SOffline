//
// Created by Róbert Selvek on 02/05/2017.
//

#ifndef SEMESTRALKA_IMPORT_CPP
#define SEMESTRALKA_IMPORT_CPP

#include "import.h"
#include "sqlite/SqliteClient.h"
#include "sqlite/SqliteStatement.h"
#include "XMLAttributeImporter.h"

#include <future>
#include <fstream>
#include <sstream>
#include <iostream>

template <typename M>
std::vector<std::shared_ptr<models::Model>> make_model_vector(std::vector<std::unique_ptr<M>> in) {
    std::vector<std::shared_ptr<models::Model>> out;
    for (size_t i = 0; i < in.size(); i++) {
        std::shared_ptr<models::Model> ptr(std::move(in[i]));
        out.push_back(ptr);
    }
    return out;
}

std::vector<std::string> extract_tags(std::string source) {
    // Tags are enclosed in angle brackets like:
    // <C++><madness><STL><depression>
    // so we remove the first and last bracket and then split on ><
    std::vector<std::string> tokens;
    if (source.size() == 0) {
        return tokens;
    }
    source.erase(0, 1);
    source.erase(source.size() - 1, 1);
    auto pos = source.find("><");
    while (pos != source.npos) {
        tokens.push_back(source.substr(0, pos));
        source.erase(0, pos+2);
        pos = source.find("><");
    }
    // Push in the remaining piece of string
    tokens.push_back(source);
    return tokens;
}

namespace import {

    Importer::Importer(std::string sources, const std::string & destination_db): directory(sources), db(destination_db) {}

    Importer::XMLData Importer::import_xml() const {
        Importer::XMLData results;
        auto badges = std::async(std::launch::async, xml::XMLAttributeImporter<models::Badge>::construct_and_parse,
                                 directory + "/Badges.xml", "badges");
        auto comments = std::async(std::launch::async, xml::XMLAttributeImporter<models::Comment>::construct_and_parse,
                                   directory + "/Comments.xml", "comments");
        auto changes = std::async(std::launch::async, xml::XMLAttributeImporter<models::PostHistoryEntry>::construct_and_parse,
                                  directory + "/PostHistory.xml", "posthistory");
        auto links = std::async(std::launch::async, xml::XMLAttributeImporter<models::PostLink>::construct_and_parse,
                                directory + "/PostLinks.xml", "postlinks");
        auto posts = std::async(std::launch::async, xml::XMLAttributeImporter<models::Post>::construct_and_parse,
                                directory + "/Posts.xml", "posts");
        auto tags = std::async(std::launch::async, xml::XMLAttributeImporter<models::Tag>::construct_and_parse,
                               directory + "/Tags.xml", "tags");
        auto users = std::async(std::launch::async, xml::XMLAttributeImporter<models::User>::construct_and_parse,
                                directory + "/Users.xml", "users");
        auto votes = std::async(std::launch::async, xml::XMLAttributeImporter<models::Vote>::construct_and_parse,
                                directory + "/Votes.xml", "votes");
        results["badges"] = make_model_vector(badges.get());
        results["comments"] = make_model_vector(comments.get());
        results["post_history"] = make_model_vector(changes.get());
        results["post_links"] = make_model_vector(links.get());
        auto postVec = posts.get();
        auto tagVec = tags.get();
        results["post_tags"] = make_model_vector(make_post_tags(tagVec, postVec));
        results["posts"] = make_model_vector(std::move(postVec));
        results["tags"] = make_model_vector(std::move(tagVec));
        results["users"] = make_model_vector(users.get());
        results["votes"] = make_model_vector(votes.get());
        return results;
    }


    void Importer::save_to_sqlite(const Importer::XMLData &data) {
        // We won't need to turn these off, that happens automatically after each COMMIT
        sqlite::Statement deferForeign(db, "PRAGMA defer_foreign_keys=1;");
        deferForeign.step();
        sqlite::Statement(db, "BEGIN;").step();
        for (const auto &table : data) {
            insert_with_max_len(table.first, table.second);
            std::cout << table.first << " saved" << std::endl;
        }
        sqlite::Statement(db, "COMMIT;").step();
    }


    void Importer::insert_with_max_len(const std::string &table, const std::vector<std::shared_ptr<models::Model>> &data) {
        //int maxVars = db.max_variables();
        //size_t modelsPerStatement = maxVars / data[0]->sql_map().size();
        // Turns out there are many other limits that affect multiple-value inserts
        // and some of those are set rather curiously in Progtest environment.
        size_t modelsPerStatement = 25;
        size_t data_idx = 0;
        while (data_idx < data.size()) {
            size_t dst_idx = 0;
            std::vector<std::shared_ptr<models::Model>> dst;
            while (dst_idx < modelsPerStatement && data_idx < data.size()) {
                dst.push_back(data.at(data_idx));
                data_idx++;
                dst_idx++;
            }
            sqlite::Statement st(db, table, dst);
            st.step();
        }

    }

    void Importer::import_all() {
        auto xml = import_xml();
        prepare_db();
        save_to_sqlite(xml);
    }

    void Importer::prepare_db() {
        db.exec(schema.c_str());
    }

    std::vector<std::unique_ptr<models::PostTag>>
    Importer::make_post_tags(const std::vector<std::unique_ptr<models::Tag>> &tags,
                             const std::vector<std::unique_ptr<models::Post>> &posts) const {
        std::vector<std::unique_ptr<models::PostTag>> postTags;
        std::unordered_map<std::string, int64_t> tagMap;
        for (const auto &tag : tags) {
            tagMap[tag->name] = tag->id;
        }
        for (const auto &post : posts) {
            auto tagNames = extract_tags(post->tagString);
            for (const auto &name : tagNames) {
                auto tagIdIt = tagMap.find(name);
                if (tagIdIt != tagMap.end()) {
                    auto postTag = new models::PostTag();
                    postTag->post = post->id;
                    postTag->tag = tagIdIt->second;
                    postTags.push_back(std::unique_ptr<models::PostTag>(postTag));
                }
            }
        }
        return postTags;
    }
}

/// The database schema. Embedded in the executable to make it as portable as possible.
const std::string import::Importer::schema = R"SCHEMA_END_MARK(
BEGIN;

DROP TABLE IF EXISTS "badges";
CREATE TABLE "badges" (
  "id" integer NOT NULL,
  "user" integer NOT NULL,
  "name" text NOT NULL,
  "date" integer NOT NULL,
  "class" integer NOT NULL,
  "tag_based" integer NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "comments";
CREATE TABLE "comments" (
  "id" integer NOT NULL,
  "post" integer NOT NULL,
  "score" integer NOT NULL,
  "text" text NOT NULL,
  "creation_date" integer NOT NULL,
  "user" integer NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "post_history";
CREATE TABLE "post_history" (
  "id" integer NOT NULL,
  "type" integer NOT NULL,
  "post" integer NOT NULL,
  "guid" text NOT NULL,
  "creation_date" integer NOT NULL,
  "user" integer NOT NULL,
  "comment" text NULL,
  "text" text NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE NO ACTION ON UPDATE NO ACTION,
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE INDEX "post_history_post_type" ON "post_history" ("post", "type");


DROP TABLE IF EXISTS "post_links";
CREATE TABLE "post_links" (
  "id" integer NOT NULL,
  "created" integer NOT NULL,
  "source" integer NOT NULL,
  "target" integer NOT NULL,
  "type" integer NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("target") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("source") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "post_tags";
CREATE TABLE "post_tags" (
  "post" integer NOT NULL,
  "tag" integer NOT NULL,
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE,
  FOREIGN KEY ("tag") REFERENCES "tags" ("id") ON DELETE CASCADE
);

CREATE INDEX "post_tags_tag" ON "post_tags" ("tag");

CREATE INDEX "post_tags_post" ON "post_tags" ("post");


DROP TABLE IF EXISTS "posts";
CREATE TABLE "posts" (
  "id" integer NOT NULL,
  "title" text NULL,
  "post_type" integer NOT NULL,
  "accepted_answer" integer NULL,
  "parent" integer NULL,
  "creation_date" integer NOT NULL,
  "score" integer NOT NULL,
  "views" integer NULL,
  "owner" integer NULL,
  "last_editor" integer NULL,
  "last_edit" integer NOT NULL,
  "last_activity" integer NOT NULL,
  "closed_at" integer NULL,
  "body" text NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("parent") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("owner") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("last_editor") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);

CREATE INDEX "posts_accepted_answer" ON "posts" ("accepted_answer");

CREATE INDEX "post_owner_type" ON "posts" ("owner", "post_type");

CREATE INDEX "post_body" ON "posts" ("body");

CREATE INDEX "post_parent" ON "posts" ("parent");


DROP VIEW IF EXISTS "posts_markdown";
CREATE TABLE "posts_markdown" ("id" integer, "title" text, "post_type" integer, "accepted_answer" integer, "parent" integer, "creation_date" integer, "score" integer, "views" integer, "owner" integer, "last_editor" integer, "last_edit" integer, "last_activity" integer, "closed_at" integer, "body" text);


DROP TABLE IF EXISTS "tags";
CREATE TABLE "tags" (
  "id" integer NOT NULL,
  "name" text NOT NULL,
  "excerpt" integer NULL,
  "wiki" integer NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("wiki") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("excerpt") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "users";
CREATE TABLE "users" (
  "id" integer NOT NULL,
  "reputation" integer NOT NULL,
  "created_at" integer NOT NULL,
  "display_name" text NOT NULL,
  "last_access" integer NULL,
  "website" text NULL,
  "location" text NULL,
  "about" text NULL,
  "upvotes" integer NOT NULL,
  "downvotes" integer NOT NULL,
  "account_id" integer NOT NULL,
  PRIMARY KEY ("id")
);

CREATE INDEX "users_created_at" ON "users" ("created_at");

CREATE INDEX "users_upvotes" ON "users" ("upvotes");

CREATE INDEX "users_downvotes" ON "users" ("downvotes");

CREATE INDEX "users_reputation" ON "users" ("reputation");

CREATE INDEX "users_display_name" ON "users" ("display_name");


DROP TABLE IF EXISTS "votes";
CREATE TABLE "votes" (
  "id" integer NOT NULL,
  "post" integer NOT NULL,
  "type" integer NOT NULL,
  "user" integer NULL,
  "creation_date" integer NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "posts_markdown";
CREATE VIEW posts_markdown AS
    SELECT posts.id, posts.title, posts.post_type, posts.accepted_answer, posts.parent,
           posts.creation_date, posts.score, posts.views, posts.owner, posts.last_editor,
           posts.last_edit, posts.last_activity, posts.closed_at, post_history.text AS body
    FROM posts
        LEFT JOIN post_history ON posts.id = post_history.post
        WHERE
            (post_history.type = 2 OR post_history.type = 5)
            AND post_history.id = (
                SELECT MAX(post_history.id) FROM post_history
                    WHERE post_history.post = posts.id
                          AND (post_history.type = 2 OR post_history.type = 5));

COMMIT;
)SCHEMA_END_MARK";

#endif