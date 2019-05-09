#ifndef Login_H
#define Login_H
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "tools.h"
class Database;
class Login {
   public:
    Login(Database* db, View* view);
    void handleLogin(Request);
    void login(User* user);
    bool isLoggedIn();
    User* getCurrentUser() { return currentUser; }

   private:
    Database* DB;
    View* Res;
    bool _isLoggedIn = false;
    User* currentUser;
};

#endif