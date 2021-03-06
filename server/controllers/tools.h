#ifndef TOOLS_H
#define TOOLS_H

#include <boost/crc.hpp>
#include <cstdarg>
#include <map>
#include <regex>
#include <string>
#include "../models/request_type.h"
#include "../server.hpp"
class Tools {
   public:
    static bool isEmail(std::string email);
    static bool isNumber(std::string content);
    static bool validateType(std::string, std::string);
    static bool checkParam(Parameters m, int counter, const char* keys...);
    static bool isInMap(Parameters m, std::string key);
    static int hashCRC32(const std::string& my_string);
    static RequestType getRequestType(std::string str);
    static Parameters makeMapFromRequest(Request*);
};

#endif