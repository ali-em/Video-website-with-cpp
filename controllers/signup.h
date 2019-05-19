#ifndef SIGN_UP_H
#define SIGN_UP_H
#include "../database/database.h"
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "tools.h"
class SignUp {
   public:
    SignUp(Database*, View*, Login*);
    void handleSignUp(Parameters&);
    void validateSignUp(Parameters&);

   private:
    Database* DB;
    View* Res;
    Login* login;
};

#endif