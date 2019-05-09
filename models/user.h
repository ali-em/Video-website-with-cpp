#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include "film.h"
#include "notification.h"
class Film;
class User {
   public:
   private:
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::vector<User*> following;
    double money;
    std::vector<Notification*> notifications;
    std::vector<Film*> purchasedFilms;
};

#endif