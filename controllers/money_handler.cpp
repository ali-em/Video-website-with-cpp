#include "money_handler.h"
#include "../database/database.h"
using namespace std;

MoneyHandler::MoneyHandler(Database* db, View* res, Login* _login) : DB(db), Res(res), login(_login) {}

void MoneyHandler::handleMoneyRequest(Parameters params) {
    User* user = login->getCurrentUser();
    if (Tools::isInMap(params, 1, "amount"))
        user->chargeMoney(stoi(params["amount"]));
    else {
        if (!user->isPublisher())
            throw PermissionDenied();
        else
            static_cast<Publisher*>(user)->getMoney();
    }
    Res->send("OK");
}
void MoneyHandler::handleBuyRequest(Parameters& params) {
    validateBuy(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    Purchase* purchase = new Purchase(film->getPrice(), film->getRate());
    DB->addPurchase(purchase);
    User* user = login->getCurrentUser();
    user->addToPurchased(film);
    Res->send("OK");
}

void MoneyHandler::validateBuy(Parameters& params) {
    if (!Tools::isInMap(params, 1, "film_id"))
        throw BadRequest();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    User* user = login->getCurrentUser();
    if (film->getPrice() > user->getMoney())
        throw BadRequest();
    if (user->isPurchased(film))
        throw BadRequest();
}