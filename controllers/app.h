#ifndef APP_H
#define APP_H
#include <cstdarg>
#include <map>
#include "../database/database.h"
#include "../views/view.h"
#include "film_manager.h"
#include "follower_handler.h"
#include "input_handler.h"
#include "login.h"
#include "money_handler.h"
#include "signup.h"
#include "tools.h"
class App {
   public:
    void run();

   private:
    void handleRequest(Request);

    Database DB;
    InputHandler Req;
    View Res;
    SignUp* signUp;
    Login* login;
    FilmManager* fm;
    FollowerHandler* fh;
    MoneyHandler* mh;
};

#endif