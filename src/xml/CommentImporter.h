//
// Created by Róbert Selvek on 30/04/2017.
//

#ifndef SEMESTRALKA_COMMENTIMPORTER_H
#define SEMESTRALKA_COMMENTIMPORTER_H

#include <string>
#include <vector>

#include "tinyxml2.h"
#include "xml/XMLAttributeImporter.h"
#include "models.h"

namespace xml {
    class CommentImporter : public XMLAttributeImporter<models::Comment> {
    public:
        CommentImporter(std::string path);

    protected:
        virtual models::Comment handle_element(const std::string &elemName,
                                               const std::vector<const tinyxml2::XMLAttribute *> &attrs) override;
    };
}
#endif //SEMESTRALKA_COMMENTIMPORTER_H
