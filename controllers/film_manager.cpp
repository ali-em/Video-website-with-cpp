#include "film_manager.h"
#include "../database/database.h"

using namespace std;

FilmManager::FilmManager(Database* db, View* view, Login* _login) : DB(db), Res(view), login(_login) {}

void FilmManager::handleAddFilm(Parameters& params) {
    validateAdd(params);
    Film* newFilm = new Film(params);
    DB->addFilm(newFilm);
    static_cast<Publisher*>(login->getCurrentUser())->addFilm(newFilm);
    Res->send("OK");
}
void FilmManager::validateAdd(Parameters& params) {
    if (!Tools::isInMap(params, 6, "name", "year", "length", "price", "summary", "director"))
        throw BadRequest();
    if (!login->isLoggedIn() || !login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    if (params.size() % 2 == 1)
        throw BadRequest();
}
void FilmManager::handleEditFilm(Parameters& params) {
    validateEdit(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->edit(params);
    Res->send("OK");
}
void FilmManager::validateEdit(Parameters& params) {
    if (!Tools::isInMap(params, 1, "film_id"))
        throw BadRequest();
    if (!login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    if (!pub->hasFilm(stoi(params["film_id"])))
        throw PermissionDenied();
}

void FilmManager::handleDeleteFilm(Parameters& params) {
    validateDelete(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->_delete();
    Res->send("OK");
}

void FilmManager::validateDelete(Parameters& params) {
    if (!Tools::isInMap(params, 1, "film_id"))
        throw BadRequest();
    if (!DB->getFilmById(stoi(params["film_id"])))
        throw NotFound();
    if (!login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    if (!pub->hasFilm(stoi(params["film_id"])))
        throw PermissionDenied();
}
void FilmManager::handleGetFilms(Parameters& params) {
    validateGet();
    User* currentUser = login->getCurrentUser();
    if (Tools::isInMap(params, 1, "film_id")) {
        Film* film = DB->getFilmById(stoi(params["film_id"]));

        Res->showFilmDetails(film->getDetails(), film->getComments(), DB->getRecommendedFilms(currentUser));
        return;
    }
    vector<Film*> filtered;
    if (!currentUser->isPublisher())
        filtered = filterFilms(params, DB->getFilms());
    else {
        Publisher* pub = static_cast<Publisher*>(currentUser);
        filtered = filterFilms(params, pub->getFilms());
    }
    Res->printFilms(filtered);
}

void FilmManager::validateGet() {
    if (!login->isLoggedIn())
        throw PermissionDenied();
}

vector<Film*> FilmManager::filterFilms(Parameters& params, vector<Film*> films) {
    vector<Film*> result;
    for (auto f : films)
        if (f->isMatch(params))
            result.push_back(f);
    return result;
}
void FilmManager::handleRate(Parameters& params) {
    User* user = login->getCurrentUser();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    if (film == NULL)
        throw NotFound();
    if (user->isPurchased(film))
        film->setRate(user, stoi(params["score"]));
    else
        throw PermissionDenied();
    Res->send("OK");
}
void FilmManager::handleGetPurchased(Parameters& params) {
    validateGet();
    User* user = login->getCurrentUser();
    vector<Film*> films = filterFilms(params, user->getPurchased());
    Res->printFilms(films);
}
