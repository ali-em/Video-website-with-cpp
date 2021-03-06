#ifndef USER_H
#define USER_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../controllers/tools.h"
#include "film.h"
#include "notification.h"
class Film;

struct UserInfo {
    int userId;
    std::string username;
    std::string email;
};

class User {
   public:
    std::string getUsername();
    std::string getPassword();
    UserInfo getInfo();
    User(std::map<std::string, std::string>);
    User(std::string email, std::string username, std::string password, std::string age);
    void setId(int id);
    bool isPublisher();
    void chargeMoney(int amount);
    double getMoney();
    void addToPurchased(Film*);
    bool isPurchased(Film*);
    std::vector<Film*> getPurchased();
    void addNotif(Notification* notif);
    int getId();
    WordsList getUnReadNotifications();
    WordsList getReadNotifications();

   protected:
    int id;
    std::string username;
    std::string password;
    std::string email;
    int age;
    double money = 0;
    std::vector<Notification*> notifications;
    std::vector<Film*> purchasedFilms;
    bool publisher = false;
};

#endif