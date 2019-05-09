#ifndef APP_H
#define APP_H
#include <map>
#include "../database/database.h"
#include "../views/view.h"
#include "input_handler.h"
class App {
   public:
    void run();

   private:
    Database database;
    InputHandler Req;
    View Res;
    User* user;
    bool isLoggedIn = false;
};

#endif