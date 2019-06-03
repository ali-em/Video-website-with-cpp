#ifndef APP_H
#define APP_H
#include <cstdarg>
#include <map>
#include "../database/database.h"
#include "../my_server.hpp"
#include "../views/view.h"
#include "comment_handler.h"
#include "film_manager.h"
#include "follower_handler.h"
#include "handlers.h"
#include "input_handler.h"
#include "login.h"
#include "middleware.h"
#include "money_handler.h"
#include "recommendation_system.h"
#include "signup.h"
#include "tools.h"
class App {
   public:
    void run();
    Response* handleRequest(Request_struct&);
    Parameters handleTemplates(Request_struct&);
   private:
    void preSetup();
    Database DB;
    InputHandler Req;
    SignUp* signUp;
    Login* login;
    FilmManager* fm;
    FollowerHandler* fh;
    MoneyHandler* mh;
    CommentHandler* ch;
    RecommendationSystem* rs;
};

#endif