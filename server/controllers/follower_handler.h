#ifndef FOLLOWER_H_H
#define FOLLOWER_H_H
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "notification_handler.h"
#include "tools.h"
class Database;

class FollowerHandler {
   public:
    FollowerHandler(Database*, Login*);
    void follow(User*, Parameters&);
    void validateFollow(User* user, Parameters&);
    void getFollower();

   private:
    Database* DB;
    Login* login;
};

#endif