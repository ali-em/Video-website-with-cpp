#ifndef FILM_MANAGER_H
#define FILM_MANAGER_H
#include <string>
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "notification_handler.h"
#include "recommendation_system.h"
#include "tools.h"
class Database;
class FilmManager {
   public:
    FilmManager(Database*, RecommendationSystem*, Login*);
    Response* handleAddFilm(Parameters&);
    void handleEditFilm(Parameters&);
    Response* handleDeleteFilm(Parameters&);
    Parameters handleGetFilms(Parameters&);
    Response* handleRate(Parameters&);
    Parameters handleGetPurchased(Parameters&);
    std::string handleGetPublished(Parameters&);
    Parameters getFilmDetails(int filmId);

   private:
    Database* DB;
    Login* login;
    RecommendationSystem* RS;
    void validateEdit(Parameters&);
    void validateAdd(Parameters&);
    void validateDelete(Parameters&);
    void validateGet();
    std::vector<Film*> filterFilms(Parameters&, std::vector<Film*>, bool includeDeleted = false);
};

#endif