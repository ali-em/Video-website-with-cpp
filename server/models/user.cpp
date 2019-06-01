#include "user.h"
using namespace std;

string User::getUsername() {
    return username;
}
int User::getId() {
    return id;
}

string User::getPassword() {
    return password;
}
User::User(map<string, string> params) {
    username = params["username"];
    password = to_string(Tools::hashCRC32(params["password"]));
    email = params["email"];
    age = stoi(params["age"]);
}
User::User(string _email, string _username, string _password, string _age) : email(_email), username(_username), age(stoi(_age)) {
    password = to_string(Tools::hashCRC32(_password));
}
void User::setId(int _id) {
    id = _id;
}
bool User::isPublisher() { return publisher; }

UserInfo User::getInfo() {
    return UserInfo{id, username, email};
}
void User::chargeMoney(int amount) {
    money += amount;
}
double User::getMoney() {
    return money;
}
void User::addToPurchased(Film* film) {
    purchasedFilms.push_back(film);
    money -= film->getPrice();
}
bool User::isPurchased(Film* film) {
    for (auto pf : purchasedFilms) {
        if (pf == film)
            return true;
    }
    return false;
}
vector<Film*> User::getPurchased() {
    return purchasedFilms;
}
void User::addNotif(Notification* notif) {
    notifications.push_back(notif);
}

WordsList User::getUnReadNotifications() {
    vector<string> result;
    for (auto n : notifications) {
        if (!n->isRead()) {
            result.push_back(n->getContent());
            n->read();
        }
    }
    return result;
}
WordsList User::getReadNotifications() {
    vector<string> result;
    for (auto n : notifications)
        if (n->isRead())
            result.push_back(n->getContent());
    return result;
}
