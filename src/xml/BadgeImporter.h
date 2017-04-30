//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_BADGEIMPORTER_H
#define SEMESTRALKA_BADGEIMPORTER_H

#include "models.h"
#include "tinyxml2.h"
#include "xml/XMLAttributeImporter.h"

namespace xml {

    class BadgeImporter: public XMLAttributeImporter<models::Badge> {
    public:
        BadgeImporter(std::string path);

    protected:
        virtual models::Badge handle_element(const std::string &elemName, const std::vector<const tinyxml2::XMLAttribute*> &attrs) override;
    };

}

#endif //SEMESTRALKA_BADGEIMPORTER_H
