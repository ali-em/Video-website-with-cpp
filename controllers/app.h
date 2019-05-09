#ifndef APP_H
#define APP_H
#include "../database/database.h"
#include "../views/view.h"
#include "input_handler.h"

class App {
   public:
   private:
    Database database;
    InputHandler req;
    View res;
    User* user;
};

#endif