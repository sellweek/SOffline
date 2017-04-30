//
// Created by Róbert Selvek on 30/04/2017.
//

#ifndef SEMESTRALKA_POSTLINKIMPORTER_H
#define SEMESTRALKA_POSTLINKIMPORTER_H

#include "models.h"
#include "tinyxml2.h"
#include "xml/XMLAttributeImporter.h"

namespace xml {

    class PostLinkImporter: public XMLAttributeImporter<models::PostLink> {
    public:
        PostLinkImporter(std::string path);

    protected:
        virtual models::PostLink handle_element(const std::string &elemName, const std::vector<const tinyxml2::XMLAttribute*> &attrs) override;
    };

}

#endif //SEMESTRALKA_POSTLINKIMPORTER_H
