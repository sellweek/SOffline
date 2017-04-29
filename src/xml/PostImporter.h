//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_POSTIMPORTER_H
#define SEMESTRALKA_POSTIMPORTER_H

#include <string>
#include <vector>

#include "tinyxml2.h"
#include "xml/XMLAttributeImporter.h"
#include "models.h"


namespace xml {
    class PostImporter : public XMLAttributeImporter<models::Post> {
    public:
        PostImporter(std::string path);

    protected:
        virtual models::Post handle_element(const std::string &elemName, const std::vector<const tinyxml2::XMLAttribute*> &attrs) override;
    };
}
#endif //SEMESTRALKA_POSTIMPORTER_H
