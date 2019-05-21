#ifndef TOOLS_H
#define TOOLS_H

#include <cstdarg>
#include <map>
#include <regex>
#include <string>
#include "../models/request_type.h"
class Tools {
   public:
    static bool isEmail(std::string email);
    static bool isNumber(std::string content);
    static bool validateType(std::string, std::string);
    static bool checkParam(Parameters m, int counter, const char* keys...);
    static bool isInMap(Parameters m, std::string key);
};

#endif