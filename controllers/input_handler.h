#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include "../models/modelHeaders.h"
#define SPACE ' '
class InputHandler {
   public:
    Request get();

   private:
    std::vector<std::string> split(std::string);
    std::string trim(std::string);
    Request parseToRequest(std::vector<std::string>);
    RequestType getReqType(std::vector<std::string>);
    bool hasWord(std::vector<std::string>, std::string);
    RequestType getRequestType(std::string str);
};

#endif