#ifndef FILM_MANAGER_H
#define FILM_MANAGER_H
#include <string>
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "tools.h"
class Database;
class FilmManager {
   public:
    FilmManager(Database*, View*, Login*);
    void handleAddFilm(Parameters&);
    void handleEditFilm(Parameters&);
    void handleDeleteFilm(Parameters&);
    void handleGetFilms(Parameters&);
    void handleRate(Parameters&);
    void handleGetPurchased(Parameters&);

   private:
    Database* DB;
    View* Res;
    Login* login;
    void validateEdit(Parameters&);
    void validateAdd(Parameters&);
    void validateDelete(Parameters&);
    void validateGet();
    std::vector<Film*> filterFilms(Parameters&, std::vector<Film*>);
};

#endif