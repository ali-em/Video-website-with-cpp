#ifndef APP_H
#define APP_H
#include "../database/database.h"
#include "../views/view.h"
#include "input_handler.h"

class App {
   public:
    void run(){};

   private:
    Database database;
    InputHandler req;
    View res;
    User* user;
};

#endif