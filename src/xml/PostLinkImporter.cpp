//
// Created by Róbert Selvek on 30/04/2017.
//

#include "PostLinkImporter.h"

namespace xml {
    PostLinkImporter::PostLinkImporter(std::string path): XMLAttributeImporter(path, "postlinks") {}

    models::PostLink PostLinkImporter::handle_element(const std::string &elemName,
                                                      const std::vector<const tinyxml2::XMLAttribute *> &attrs) {
        models::PostLink l {};
        for (auto attr : attrs) {
            std::string name {attr->Name()};
            auto err = tinyxml2::XML_SUCCESS;
            if (name == "Id") {
                err = attr->QueryInt64Value(&l.id);
            } else if (name == "PostId") {
                err = attr->QueryInt64Value(&l.source);
            }  else if (name == "RelatedPostId") {
                err = attr->QueryInt64Value(&l.target);
            } else if (name == "LinkTypeId") {
                err = attr->QueryInt64Value(&l.type);
            } else if (name == "CreationDate") {
                l.date = parse_time(std::string(attr->Value()));
            }
            if (err != tinyxml2::XML_SUCCESS) {
                throw Exception(err);
            }
        }
        return l;
    }
}