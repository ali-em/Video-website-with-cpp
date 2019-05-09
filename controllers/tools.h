#ifndef TOOLS_H
#define TOOLS_H

#include <cstdarg>
#include <map>
#include <string>
class Tools {
   public:
    static bool isInMap(std::map<std::string, std::string> m, int counter, const char* v...);
};

#endif