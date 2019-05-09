#ifndef SIGN_UP_H
#define SIGN_UP_H
#include "../database/database.h"
#include "../views/view.h"
class SignUp {
   public:
    SignUp(Database*, View*);
    void signUp(Request);
    void validateSignUp(Request req);

   private:
    Database* DB;
    View* Res;
};

#endif