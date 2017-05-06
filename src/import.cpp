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
#include <iostream>
/*
template <typename T>
std::vector<std::vector<const models::Model&>> split_to_max_lengths(std::vector<T> src, int max_len) {
    size_t src_idx = 0;
    std::vector<std::vector<const models::Model&>> result;
    while (src_idx < src.size()) {
        size_t dst_idx = 0;
        std::vector<const models::Model&> dst;
        while (dst_idx < max_len && src_idx < src.size()) {
            dst.push_back(src.at(src_idx));
            src_idx++;
            dst_idx++;
        }
        result.push_back(dst);
    }
    return result;
}
 */

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
        save_to_sqlite(xml);
    }
}

#endif