#ifndef DATABASE_H
#define DATABASE_H

#include <algorithm>
#include <string>
#include <vector>
#include "../models/modelHeaders.h"
class Database {
   public:
    Database();
    ~Database();
    User* findUserByUsername(std::string);
    void addUser(User*);
    User* findUserById(int userId);
    User* findUserByUsernameAndPassword(std::string, std::string);
    void addFilm(Film*);
    Film* getFilmById(int id);
    std::vector<Film*> getFilms(bool includeDeleted = false);
    void addPurchase(Purchase*);
    std::string getRecommendedFilms(User*, Film*);
    Publisher* getPublisherByFilmId(int id);
    std::vector<Purchase*> getPurchases();

   private:
    int userId = 1, filmId = 1, purchaseId = 1, notificationId = 1;
    std::vector<User*> users;
    std::vector<Film*> films;
    std::vector<Comment*> comments;
    std::vector<Purchase*> purchases;
};

#endif