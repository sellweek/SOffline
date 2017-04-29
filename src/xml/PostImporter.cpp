//
// Created by Róbert Selvek on 29/04/2017.
//

#include "PostImporter.h"
#include "xml/util.h"

namespace xml {
    PostImporter::PostImporter(std::string path): XMLAttributeImporter(path, "posts") {}

    models::Post PostImporter::handle_element(const std::string &elemName,
                                              const std::vector<const tinyxml2::XMLAttribute *> &attrs) {
        models::Post p {};
        for (auto attr : attrs) {
            std::string name {attr->Name()};
            auto err = tinyxml2::XML_SUCCESS;
            if (name == "Id") {
                err = attr->QueryInt64Value(&p.id);
            } else if (name == "PostTypeId") {
                err = attr->QueryInt64Value(&p.type);
            } else if (name == "ParentId") {
                err = attr->QueryInt64Value(&p.parent);
            } else if (name == "AcceptedAnswerId") {
                err = attr->QueryInt64Value(&p.accepted_answer);
            } else if (name == "Score") {
                err = attr->QueryInt64Value(&p.score);
            } else if (name == "ViewCount") {
                err = attr->QueryInt64Value(&p.views);
            } else if (name == "Title") {
                p.title = std::string(attr->Value());
            } else if (name == "Body") {
                p.body = std::string(attr->Value());
            } else if (name == "OwnerUserId") {
                err = attr->QueryInt64Value(&p.owner);
            } else if (name == "LastEditorUserId") {
                err = attr->QueryInt64Value(&p.last_editor);
            } else if (name == "LastEditDate") {
                p.last_edit = parse_time(std::string(attr->Value()));
            } else if (name == "LastActivityDate") {
                p.last_activity = parse_time(std::string(attr->Value()));
            }else if (name == "CreationDate") {
                p.created_at = parse_time(std::string(attr->Value()));
            }else if (name == "ClosedDate") {
                p.closed_at = parse_time(std::string(attr->Value()));
            }
            if (err != tinyxml2::XML_SUCCESS) {
                throw Exception(err);
            }
        }
        return p;
    }
}