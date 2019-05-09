#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "../models/modelHeaders.h"

class Database {
   public:
    User* findUserByUsername(std::string);
    void addUser(User*);

   private:
    int userId = 1, filmId = 1, commentId = 1, purchaseId = 1, notificationId = 1;
    std::vector<User*> users;
    std::vector<Film*> films;
    std::vector<Comment*> comments;
    std::vector<Purchase*> purchases;
    std::vector<Notification*> notifications;
};

#endif