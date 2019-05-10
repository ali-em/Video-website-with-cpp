#include "database.h"
using namespace std;

User* Database::findUserByUsername(string username) {
    for (auto user : users)
        if (user->getUsername() == username)
            return user;
    return NULL;
}
void Database::addUser(User* user) {
    users.push_back(user);
    user->setId(userId++);
}
User* Database::findUserByUsernameAndPassword(std::string username, std::string password) {
    for (auto user : users)
        if (user->getUsername() == username && user->getPassword() == password)
            return user;
    return NULL;
}
void Database::addFilm(Film* newFilm) {
    films.push_back(newFilm);
    newFilm->setId(filmId++);
}

Film* Database::getFilmById(int id) {
    for (auto f : films)
        if (f->getId() == id)
            return f;
    return NULL;
}
