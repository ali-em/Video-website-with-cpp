#include "film_manager.h"
#include "../database/database.h"

using namespace std;

FilmManager::FilmManager(Database* db, View* view, Login* _login) : DB(db), Res(view), login(_login) {}

void FilmManager::handleAddFilm(Request& req) {
    validate(req);
    Film* newFilm = new Film(req);
    DB->addFilm(newFilm);
    static_cast<Publisher*>(login->getCurrentUser())->addFilm(newFilm);
    Res->send("OK");
}
void FilmManager::validate(Request& req) {
    if (!Tools::isInMap(req.params, 6, "name", "year", "length", "price", "summary", "director"))
        throw BadRequest();
    if (!login->isLoggedIn())
        throw PermissionDenied();
    if (req.params.size() % 2 == 1)
        throw BadRequest();
}