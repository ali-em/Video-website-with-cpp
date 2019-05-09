#ifndef APP_H
#define APP_H
#include <cstdarg>
#include <map>
#include "../database/database.h"
#include "../views/view.h"
#include "input_handler.h"
#include "signup.h"
class App {
   public:
    void run();

   private:
    void handleRequest(Request);

    bool isInMap(std::map<std::string, std::string> m, int counter, const char* v...);
    void handleLogin(Request);
    void login(User* user);
    Database DB;
    InputHandler Req;
    View Res;
    SignUp* signUp;
    User* currentUser;
    bool isLoggedIn = false;
};

#endif