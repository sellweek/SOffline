//
// Created by Róbert Selvek on 02/05/2017.
//

#ifndef SEMESTRALKA_IMPORT_CPP
#define SEMESTRALKA_IMPORT_CPP

#include "import.h"
#include "sqlite/sqlite_client.h"
#include "sqlite/sqlite_statement.h"
#include "XMLAttributeImporter.h"

#include <future>
#include <fstream>

template <typename M>
std::vector<std::shared_ptr<models::Model>> make_model_vector(std::vector<std::unique_ptr<M>> in) {
    std::vector<std::shared_ptr<models::Model>> out;
    for (int i = 0; i < in.size(); i++) {
        std::shared_ptr<models::Model> ptr(std::move(in[i]));
        out.push_back(ptr);
    }
    return out;
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
        results["posts"] = make_model_vector(posts.get());
        results["tags"] = make_model_vector(tags.get());
        results["users"] = make_model_vector(users.get());
        results["votes"] = make_model_vector(votes.get());
        return results;
    }


    void Importer::save_to_sqlite(const Importer::XMLData &data) {
        sqlite::Statement deferForeign(db, "PRAGMA defer_foreign_keys=1;");
        // We won't need to turn these off, that happens automatically after each COMMIT
        deferForeign.step();
        sqlite::Statement(db, "BEGIN;").step();
        for (const auto &table : data) {
            insert_with_max_len(table.first, table.second);
            std::cout << table.first << " saved" << std::endl;
        }
        sqlite::Statement(db, "COMMIT;").step();
    }


    void Importer::insert_with_max_len(const std::string &table, const std::vector<std::shared_ptr<models::Model>> &data) {
        int maxVars = db.max_variables();
        size_t modelsPerStatement = maxVars / data[0]->sql_map().size();
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
        sqlite::Statement schemaPrepareStatement(db, schema);
        schemaPrepareStatement.step();
    }
}

const std::string import::Importer::schema = R"SCHEMA_END_MARK(
-- Adminer 4.2.4 SQLite 3 dump
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
  "body" text NOT NULL,
  "owner" integer NULL,
  "last_editor" integer NULL,
  "last_edit" integer NOT NULL,
  "last_activity" integer NOT NULL,
  "closed_at" integer NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("parent") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("owner") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("last_editor") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);


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

COMMIT;
)SCHEMA_END_MARK";

#endif