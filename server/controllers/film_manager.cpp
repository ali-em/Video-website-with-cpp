#include "film_manager.h"
#include "../database/database.h"

using namespace std;

FilmManager::FilmManager(Database* db, RecommendationSystem* rs, Login* _login) : DB(db), login(_login), RS(rs) {}

Response* FilmManager::handleAddFilm(Parameters& params) {
    validateAdd(params);
    Film* newFilm = new Film(params);
    DB->addFilm(newFilm);
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    pub->addFilm(newFilm);
    NotificationHandler::sendRegisterFilmNotif(pub);
    RS->addFilm();

    Response* res = Response::redirect("/");
    return res;
}
void FilmManager::validateAdd(Parameters& params) {
    if (!Tools::checkParam(params, 6, "name", "year", "length", "price", "summary", "director"))
        throw BadRequest();
    if (!login->isLoggedIn() || !login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
}
void FilmManager::handleEditFilm(Parameters& params) {
    validateEdit(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->edit(params);
    View::success();
}
void FilmManager::validateEdit(Parameters& params) {
    if (!Tools::checkParam(params, 1, "film_id"))
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
    View::success();
}

void FilmManager::validateDelete(Parameters& params) {
    if (!Tools::checkParam(params, 1, "film_id"))
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
    if (Tools::isInMap(params, "film_id")) {
        getFilmDetails(stoi(params["film_id"]));
        return;
    }
    vector<Film*> filtered;
    filtered = filterFilms(params, DB->getFilms(), true);
    View::printFilms(filtered);
}
void FilmManager::getFilmDetails(int filmId) {
    Film* film = DB->getFilmById(filmId);
    User* currentUser = login->getCurrentUser();
    if (!film || film->isDeleted())
        throw NotFound();
    View::showFilmDetails(film->getDetails(), film->getComments(), RS->getRecommended(currentUser, filmId));
}
void FilmManager::handleGetPublished(Parameters& params) {
    validateGet();
    User* currentUser = login->getCurrentUser();
    vector<Film*> filtered;
    Publisher* pub = static_cast<Publisher*>(currentUser);
    filtered = filterFilms(params, pub->getFilms(), true);
    View::printFilms(filtered);
}

void FilmManager::validateGet() {
    if (!login->isLoggedIn())
        throw PermissionDenied();
}

vector<Film*> FilmManager::filterFilms(Parameters& params, vector<Film*> films, bool includeDeleted) {
    vector<Film*> result;
    for (auto f : films)
        if (f->isMatch(params) &&
            (!f->isDeleted() || includeDeleted))
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
    NotificationHandler::sendRateNotif(user, DB->getPublisherByFilmId(stoi(params["film_id"])), film);
    View::success();
}
void FilmManager::handleGetPurchased(Parameters& params) {
    validateGet();
    User* user = login->getCurrentUser();
    vector<Film*> films = filterFilms(params, user->getPurchased());
    View::printFilms(films);
}
