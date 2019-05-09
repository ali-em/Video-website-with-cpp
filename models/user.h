#ifndef USER_H
#define USER_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "film.h"
#include "notification.h"
class Film;
class User {
   public:
    std::string getUsername();
    User(std::map<std::string, std::string>);
    User(std::string email, std::string username, std::string password, std::string age);
    void setId(int id);

   protected:
    int id;
    std::string username;
    std::string password;
    std::string email;
    int age;
    std::vector<User*> following;
    double money;
    std::vector<Notification*> notifications;
    std::vector<Film*> purchasedFilms;
    bool isPublisher = false;
};

#endif