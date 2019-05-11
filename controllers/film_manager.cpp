#include "film_manager.h"
#include "../database/database.h"

using namespace std;

FilmManager::FilmManager(Database* db, View* view, Login* _login) : DB(db), Res(view), login(_login) {}

void FilmManager::handleAddFilm(Request& req) {
    validateAdd(req);
    Film* newFilm = new Film(req);
    DB->addFilm(newFilm);
    static_cast<Publisher*>(login->getCurrentUser())->addFilm(newFilm);
    Res->send("OK");
}
void FilmManager::validateAdd(Request& req) {
    if (!Tools::isInMap(req.params, 6, "name", "year", "length", "price", "summary", "director"))
        throw BadRequest();
    if (!login->isLoggedIn() || !login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    if (req.params.size() % 2 == 1)
        throw BadRequest();
}
void FilmManager::handleEditFilm(Request& req) {
    validateEdit(req);
    Film* film = DB->getFilmById(stoi(req.params["film_id"]));
    film->edit(req);
    Res->send("OK");
}
void FilmManager::validateEdit(Request& req) {
    if (!Tools::isInMap(req.params, 1, "film_id"))
        throw BadRequest();
    if (!login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    if (!pub->hasFilm(stoi(req.params["film_id"])))
        throw PermissionDenied();
}

void FilmManager::handleDeleteFilm(Request& req) {
    validateDelete(req);
    Film* film = DB->getFilmById(stoi(req.params["film_id"]));
    film->_delete();
    Res->send("OK");
}

void FilmManager::validateDelete(Request& req) {
    if (!Tools::isInMap(req.params, 1, "film_id"))
        throw BadRequest();
    if (!DB->getFilmById(stoi(req.params["film_id"])))
        throw NotFound();
    if (!login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    if (!pub->hasFilm(stoi(req.params["film_id"])))
        throw PermissionDenied();
}
void FilmManager::handleGetFilms(Request& req) {
    validateGet();
    if (Tools::isInMap(req.params, 1, "film_id")) {
        Res->showFilmDetails(DB->getFilmById(stoi(req.params["film_id"])));
        return;
    }
    vector<Film*> filtered;
    User* currentUser = login->getCurrentUser();
    if (!currentUser->isPublisher())
        filtered = filterFilms(req, DB->getFilms());
    else {
        Publisher* pub = static_cast<Publisher*>(currentUser);
        filtered = filterFilms(req, pub->getFilms());
    }
    Res->printFilms(filtered);
}

void FilmManager::validateGet() {
    if (!login->isLoggedIn())
        throw PermissionDenied();
}

vector<Film*> FilmManager::filterFilms(Request& req, vector<Film*> films) {
    vector<Film*> result;
    for (auto f : films)
        if (f->isMatch(req.params))
            result.push_back(f);
    return result;
}