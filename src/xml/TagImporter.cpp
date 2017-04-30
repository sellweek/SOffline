//
// Created by Róbert Selvek on 30/04/2017.
//

#include "TagImporter.h"

namespace xml {
    TagImporter::TagImporter(std::string path): XMLAttributeImporter(path, "tags") {}

    models::Tag TagImporter::handle_element(const std::string &elemName,
                                            const std::vector<const tinyxml2::XMLAttribute *> &attrs) {
        models::Tag t {};
        for (auto attr : attrs) {
            std::string name {attr->Name()};
            auto err = tinyxml2::XML_SUCCESS;
            if (name == "Id") {
                err = attr->QueryInt64Value(&t.id);
            } else if (name == "WikiPostId") {
                err = attr->QueryInt64Value(&t.wiki);
            } else if (name == "ExcerptPostId") {
                err = attr->QueryInt64Value(&t.excerpt);
            } else if (name == "TagName") {
                t.name = std::string(attr->Value());
            }
            if (err != tinyxml2::XML_SUCCESS) {
                throw Exception(err);
            }
        }
        return t;
    }
}