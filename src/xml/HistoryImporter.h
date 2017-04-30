//
// Created by Róbert Selvek on 30/04/2017.
//

#ifndef SEMESTRALKA_HISTORYIMPORTER_H
#define SEMESTRALKA_HISTORYIMPORTER_H

#include "models.h"
#include "tinyxml2.h"
#include "xml/XMLAttributeImporter.h"

namespace xml {

    class HistoryImporter: public XMLAttributeImporter<models::PostHistoryEntry> {
    public:
        HistoryImporter(std::string path);

    protected:
        virtual models::PostHistoryEntry handle_element(const std::string &elemName, const std::vector<const tinyxml2::XMLAttribute*> &attrs) override;
    };

}

#endif //SEMESTRALKA_HISTORYIMPORTER_H
