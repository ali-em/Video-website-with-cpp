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
    void validateAdd(Request&);
    void handleEditFilm(Request&);
    void validateEdit(Request&);

   private:
    Database* DB;
    View* Res;
    Login* login;
};

#endif