#ifndef VIEW_H
#define VIEW_H

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include "../models/modelHeaders.h"
#define DIVIDER " | "
class View {
   public:
    std::map<std::string, std::string> get();
    void send(std::string);
    void sendError(std::exception&);
    void printFilms(std::vector<Film*>&);

   private:
};

#endif
