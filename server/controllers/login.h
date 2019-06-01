#ifndef Login_H
#define Login_H
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "tools.h"
class Database;
class Login {
   public:
    Login(Database* db);
    void handleLogin(Parameters&);
    void login(User* user);
    bool isLoggedIn();
    User* getCurrentUser();
    void logout();

   private:
    Database* DB;
    bool _isLoggedIn = false;
    User* currentUser;
};

#endif