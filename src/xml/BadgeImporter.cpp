//
// Created by Róbert Selvek on 29/04/2017.
//

#include "BadgeImporter.h"

namespace xml {
    BadgeImporter::BadgeImporter(std::string path): XMLAttributeImporter(path, "badges") {}

    models::Badge BadgeImporter::handle_element(const std::string &elemName,
                                                const std::vector<const tinyxml2::XMLAttribute *> &attrs) {
        models::Badge b {};
        for (auto attr : attrs) {
            std::string name {attr->Name()};
            auto err = tinyxml2::XML_SUCCESS;
            if (name == "Id") {
                err = attr->QueryInt64Value(&b.id);
            } else if (name == "UserId") {
                err = attr->QueryInt64Value(&b.user);
            } else if (name == "Name") {
                b.name = std::string(attr->Value());
            } else if (name == "Date") {
                b.date = parse_time(std::string(attr->Value()));
            } else if (name == "Class") {
                err = attr->QueryInt64Value(&b.badge_class);
            } else if (name == "TagBased") {
                std::string(attr->Value()) == "True" ? b.tag_based = true : b.tag_based = false;
            }
            if (err != tinyxml2::XML_SUCCESS) {
                throw Exception(err);
            }
        }
        return b;
    }
}