#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include "../models/types.h"
#define SPACE ' '
class InputHandler {
   public:
    Request get();

   private:
    std::vector<std::string> split(std::string);
    std::string trim(std::string);
};

#endif