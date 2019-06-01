#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include "../models/modelHeaders.h"
#define SPACE ' '
class InputHandler {
   public:
    Request_struct get();

   private:
    WordsList split(std::string);
    std::string trim(std::string);
    Request_struct parseToRequest(WordsList);
    RequestType getReqType(WordsList);
    bool hasWord(WordsList, std::string);
    RequestType getRequestType(std::string str);
    WordsList getReqPart(WordsList splitted);
    Parameters getReqParams(WordsList, RequestType);
    void validateRequest(WordsList, RequestType);
};
#endif