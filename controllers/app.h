#ifndef APP_H
#define APP_H
#include <cstdarg>
#include <map>
#include "../database/database.h"
#include "../views/view.h"
#include "input_handler.h"
class App {
   public:
    void run();

   private:
    void handleRequest(Request);
    void signUp(Request);
    void validateSignUp(Request req);
    bool isInMap(std::map<std::string, std::string> m, int counter, const char* v...);
    void printSuccess();
    Database DB;
    InputHandler Req;
    View Res;
    User* user;
    bool isLoggedIn = false;
};

#endif