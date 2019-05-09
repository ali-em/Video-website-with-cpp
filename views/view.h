#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <map>
#include <string>
#include "../models/modelHeaders.h"

class View {
   public:
    std::map<std::string, std::string> get();
    void send(std::string);

   private:
};

#endif
