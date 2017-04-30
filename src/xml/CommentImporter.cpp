//
// Created by Róbert Selvek on 30/04/2017.
//

#include "CommentImporter.h"

namespace xml {
    CommentImporter::CommentImporter(std::string path): XMLAttributeImporter(path, "comments") {}

    models::Comment CommentImporter::handle_element(const std::string &elemName,
                                                    const std::vector<const tinyxml2::XMLAttribute *> &attrs) {
        models::Comment c {};
        for (auto attr : attrs) {
            std::string name {attr->Name()};
            auto err = tinyxml2::XML_SUCCESS;
            if (name == "Id") {
                err = attr->QueryInt64Value(&c.id);
            } else if (name == "PostId") {
                err = attr->QueryInt64Value(&c.post);
            } else if (name == "Score") {
                err = attr->QueryInt64Value(&c.score);
            } else if (name == "Text") {
                c.text = std::string(attr->Value());
            } else if (name == "CreationDate") {
                c.date = parse_time(std::string(attr->Value()));
            } else if (name == "UserId") {
                err = attr->QueryInt64Value(&c.user);
            }
            if (err != tinyxml2::XML_SUCCESS) {
                throw Exception(err);
            }
        }
        return c;
    }
}
