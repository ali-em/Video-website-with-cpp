#ifndef FILM_MANAGER_H
#define FILM_MANAGER_H
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "tools.h"
class Database;
class FilmManager {
   public:
    FilmManager(Database*, View*, Login*);
    void handleAddFilm(Request&);
    void handleEditFilm(Request&);
    void handleDeleteFilm(Request&);
    void handleGetFilms(Request&);

   private:
    Database* DB;
    View* Res;
    Login* login;
    void validateEdit(Request&);
    void validateAdd(Request&);
    void validateDelete(Request&);
    void validateGet();
    std::vector<Film*> filterFilms(Request&, std::vector<Film*>);
};

#endif