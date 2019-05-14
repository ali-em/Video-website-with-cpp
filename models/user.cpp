#include "user.h"
using namespace std;

string User::getUsername() {
    return username;
}
string User::getPassword() {
    return password;
}
User::User(map<string, string> params) {
    username = params["username"];
    password = params["password"];
    email = params["email"];
    age = stoi(params["age"]);
}
User::User(string _email, string _username, string _password, string _age) : email(_email), username(_username), password(_password), age(stoi(_age)) {}
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