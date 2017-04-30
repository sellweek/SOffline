//
// Created by Róbert Selvek on 30/04/2017.
//

#include "HistoryImporter.h"

namespace xml {
    HistoryImporter::HistoryImporter(std::string path): XMLAttributeImporter(path, "posthistory") {}

    models::PostHistoryEntry HistoryImporter::handle_element(const std::string &elemName,
                                                             const std::vector<const tinyxml2::XMLAttribute *> &attrs) {
        models::PostHistoryEntry h {};
        for (auto attr : attrs) {
            std::string name {attr->Name()};
            auto err = tinyxml2::XML_SUCCESS;
            if (name == "Id") {
                err = attr->QueryInt64Value(&h.id);
            } else if (name == "UserId") {
                err = attr->QueryInt64Value(&h.user);
            }  else if (name == "PostId") {
                err = attr->QueryInt64Value(&h.post);
            } else if (name == "PostHistoryTypeId") {
                err = attr->QueryInt64Value(&h.type);
            } else if (name == "CreationDate") {
                h.date = parse_time(std::string(attr->Value()));
            } else if (name == "RevisionGUID") {
                h.guid = attr->Value();
            } else if (name == "Comment") {
                h.comment = attr->Value();
            } else if (name == "Text") {
                h.text = attr->Value();
            }
            if (err != tinyxml2::XML_SUCCESS) {
                throw Exception(err);
            }
        }
        return h;
    }
}