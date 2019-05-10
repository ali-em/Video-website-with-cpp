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
    if (!login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    if (!pub->hasFilm(stoi(req.params["film_id"])))
        throw PermissionDenied();
}