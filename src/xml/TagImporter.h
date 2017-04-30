//
// Created by Róbert Selvek on 30/04/2017.
//

#ifndef SEMESTRALKA_TAGIMPORTER_H
#define SEMESTRALKA_TAGIMPORTER_H


#include "models.h"
#include "tinyxml2.h"
#include "xml/XMLAttributeImporter.h"

namespace xml {

    class TagImporter: public XMLAttributeImporter<models::Tag> {
    public:
        TagImporter(std::string path);

    protected:
        virtual models::Tag handle_element(const std::string &elemName, const std::vector<const tinyxml2::XMLAttribute*> &attrs) override;
    };

}


#endif //SEMESTRALKA_TAGIMPORTER_H
