//
// Created by Róbert Selvek on 12/05/2017.
//

#ifndef SEMESTRALKA_PARAMETERPROPS_H
#define SEMESTRALKA_PARAMETERPROPS_H

namespace cli {

    struct ParameterProps {
        std::string name;
        std::string description;
        bool optional;
        bool hasParameter;
        bool hasDefault;
        std::string defaultValue;
    };

}

#endif //SEMESTRALKA_PARAMETERPROPS_H
