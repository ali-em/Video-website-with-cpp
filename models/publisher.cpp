#include "publisher.h"
using namespace std;
Publisher::Publisher(std::map<std::string, std::string> params) : User(params) {
    publisher = true;
}
void Publisher::addFilm(Film* film) {
    publishedFilms.push_back(film);
}
bool Publisher::hasFilm(int id) {
    for (auto f : publishedFilms)
        if (f->getId() == id && !f->isDeleted())
            return true;
    return false;
}
vector<Film*> Publisher::getFilms() {
    return publishedFilms;
}
bool Publisher::isFollowedBy(User* user) {
    for (auto follower : followers) {
        if (follower == user)
            return true;
    }
    return false;
}
void Publisher::followBy(User* user) {
    followers.push_back(user);
}
vector<UserInfo> Publisher::getFollowersInfo() {
    vector<UserInfo> result;
    for (auto f : followers) {
        result.push_back(f->getInfo());
    }
    return result;
}
void Publisher::getMoney() {
    for (auto film : publishedFilms)
        money += film->getTotalSell();
}
