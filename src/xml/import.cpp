//
// Created by Róbert Selvek on 02/05/2017.
//

#ifndef SEMESTRALKA_IMPORT_CPP
#define SEMESTRALKA_IMPORT_CPP

#import "xml/import.h"
#include "XMLAttributeImporter.h"

#import <future>
#import <iostream>

namespace xml {

    ImportResults import_all(std::string sourceDirectory) {
        ImportResults results;
        auto badges = std::async(std::launch::async, xml::XMLAttributeImporter<models::Badge>::construct_and_parse,
                                 sourceDirectory + "/Badges.xml", "badges");
        auto comments = std::async(std::launch::async, xml::XMLAttributeImporter<models::Comment>::construct_and_parse,
                                   sourceDirectory + "/Comments.xml", "comments");
        auto changes = std::async(std::launch::async, xml::XMLAttributeImporter<models::PostHistoryEntry>::construct_and_parse,
                                  sourceDirectory + "/PostHistory.xml", "posthistory");
        auto links = std::async(std::launch::async, xml::XMLAttributeImporter<models::PostLink>::construct_and_parse,
                                sourceDirectory + "/PostLinks.xml", "postlinks");
        auto posts = std::async(std::launch::async, xml::XMLAttributeImporter<models::Post>::construct_and_parse,
                                sourceDirectory + "/Posts.xml", "posts");
        auto tags = std::async(std::launch::async, xml::XMLAttributeImporter<models::Tag>::construct_and_parse,
                               sourceDirectory + "/Tags.xml", "tags");
        auto users = std::async(std::launch::async, xml::XMLAttributeImporter<models::User>::construct_and_parse,
                                sourceDirectory + "/Users.xml", "users");
        auto votes = std::async(std::launch::async, xml::XMLAttributeImporter<models::Vote>::construct_and_parse,
                                sourceDirectory + "/Votes.xml", "votes");
        results.badges = badges.get();

        results.comments = comments.get();
        results.changes = changes.get();
        results.links = links.get();
        results.posts = posts.get();
        results.tags = tags.get();
        results.users = users.get();
        results.votes = votes.get();
        return results;
    }
}

#endif