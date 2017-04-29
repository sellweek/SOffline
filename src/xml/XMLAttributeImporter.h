//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H
#define SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H

#include "tinyxml2.h"
#include "xml/util.h"
#include <iostream>
#include <string>
#include <vector>

namespace xml {

    template <typename M>
    class XMLAttributeImporter : public tinyxml2::XMLVisitor {
    public:
        XMLAttributeImporter(std::string path, std::string rootElemName);

        virtual bool VisitEnter(const tinyxml2::XMLElement &elem, const tinyxml2::XMLAttribute *attr) override;

        virtual M handle_element(const std::string &elemName, const std::vector<const tinyxml2::XMLAttribute*> &attrs) = 0;

        virtual std::vector<M> parse();

    protected:
        std::string rootElemName, path;
        bool rootHandled;
        std::vector<M> results;
        tinyxml2::XMLDocument doc;
    };

    template <typename M>
    bool XMLAttributeImporter<M>::VisitEnter(const tinyxml2::XMLElement &elem, const tinyxml2::XMLAttribute *attr) {
        if (!rootHandled && std::string(elem.Name()) != rootElemName) {
            std::cout << elem.Name() << std::endl;
            throw IncorrectFileException();
        }
        rootHandled = true;
        if (rootHandled) {
            std::vector<const tinyxml2::XMLAttribute *> attrs;
            while (attr != nullptr) {
                attrs.push_back(attr);
                attr = attr->Next();
            }
            results.push_back(handle_element(std::string(elem.Name()), attrs));
        }
        return true;
    }

    template <typename M>
    XMLAttributeImporter<M>::XMLAttributeImporter(std::string path, std::string rootElemName) : rootElemName(rootElemName),
                                                                                                rootHandled(false),
                                                                                                doc(), path(path) {}

    template <typename M>
    std::vector<M> XMLAttributeImporter<M>::parse() {
        tinyxml2::XMLError result = doc.LoadFile(path.c_str());
        if (result != tinyxml2::XML_SUCCESS) {
            throw Exception(result);
        }
        doc.Accept(this);
        return results;
    }
}
#endif //SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H
