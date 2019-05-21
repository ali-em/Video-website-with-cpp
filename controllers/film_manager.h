#ifndef FILM_MANAGER_H
#define FILM_MANAGER_H
#include <string>
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "notification_handler.h"
#include "tools.h"
class Database;
class FilmManager {
   public:
    FilmManager(Database*, Login*);
    void handleAddFilm(Parameters&);
    void handleEditFilm(Parameters&);
    void handleDeleteFilm(Parameters&);
    void handleGetFilms(Parameters&);
    void handleRate(Parameters&);
    void handleGetPurchased(Parameters&);
    void handleGetPublished(Parameters&);

   private:
    Database* DB;
    Login* login;
    void validateEdit(Parameters&);
    void validateAdd(Parameters&);
    void validateDelete(Parameters&);
    void validateGet();
    std::vector<Film*> filterFilms(Parameters&, std::vector<Film*>, bool includeDeleted = false);
};

#endif