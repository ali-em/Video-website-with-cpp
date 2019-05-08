#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>

class User {
   public:
   private:
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::vector<User*> following;
    double money;
    // std::vector<Film*> purchasedFilms;
};

#endif