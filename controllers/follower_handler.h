#ifndef FOLLOWER_H_H
#define FOLLOWER_H_H
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "tools.h"
class Database;

class FollowerHandler {
   public:
    FollowerHandler(Database*, View*, Login*);
    void follow(User*, Parameters&);
    void validateFollow(User* user, Parameters&);
    void getFollower();

   private:
    Database* DB;
    View* Res;
    Login* login;
};

#endif