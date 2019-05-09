#ifndef Login_H
#define Login_H
#include "../database/database.h"
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "tools.h"
class Login {
   public:
    Login(Database*, View*);
    void handleLogin(Request);
    void login(User* user);
    bool isLoggedIn() { return _isLoggedIn; }

   private:
    Database* DB;
    View* Res;
    bool _isLoggedIn = false;
    User* currentUser;
};

#endif