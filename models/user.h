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
    std::string getPassword();
    User(std::map<std::string, std::string>);
    User(std::string email, std::string username, std::string password, std::string age);
    void setId(int id);
    bool isPublisher();

   protected:
    int id;
    std::string username;
    std::string password;
    std::string email;
    int age;
    double money;
    std::vector<Notification*> notifications;
    std::vector<Film*> purchasedFilms;
    bool publisher = false;
};

#endif