#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "../models/modelHeaders.h"

class Database {
   public:
    User* findUserByUsername(std::string);

   private:
    std::vector<User*> users;
    std::vector<Film*> films;
    std::vector<Comment*> comments;
    std::vector<Purchase*> purchases;
    std::vector<Notification*> notifications;
};

#endif