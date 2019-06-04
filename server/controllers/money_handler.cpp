#include "money_handler.h"
#include "../database/database.h"
using namespace std;

MoneyHandler::MoneyHandler(Database* db, RecommendationSystem* rs, Login* _login) : DB(db), RS(rs), login(_login) {}

void MoneyHandler::handleMoneyRequest(Parameters params) {
    User* user = login->getCurrentUser();
    if (Tools::checkParam(params, 1, "amount"))
        user->chargeMoney(stoi(params["amount"]));
    else {
        if (!user->isPublisher())
            throw PermissionDenied();
        else
            static_cast<Publisher*>(user)->getMoney();
    }
    View::success();
}
Response* MoneyHandler::handleBuyRequest(Parameters& params) {
    validateBuy(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    Purchase* purchase = new Purchase(film->getPrice(), film->getRate());
    DB->addPurchase(purchase);
    film->addPurchase(purchase);
    User* user = login->getCurrentUser();
    user->addToPurchased(film);
    RS->update(user, film->getId());
    NotificationHandler::sendBuyNotif(user, DB->getPublisherByFilmId(stoi(params["film_id"])), film);
    return Response::redirect("/film?film_id=" + params["film_id"]);
}

void MoneyHandler::validateBuy(Parameters& params) {
    if (!Tools::checkParam(params, 1, "film_id"))
        throw BadRequest();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    User* user = login->getCurrentUser();
    if (!film)
        throw NotFound();
    if (film->getPrice() > user->getMoney())
        throw BadRequest();
    if (user->isPurchased(film))
        throw BadRequest();
}
void MoneyHandler::getMoney() {
    User* user = login->getCurrentUser();
    if (user->getUsername() == "admin")
        getSystemMoney();
    else
        View::send(to_string((int)user->getMoney()));
}
void MoneyHandler::getSystemMoney() {
    cout << "here" << endl;
    vector<Purchase*> purchases = DB->getPurchases();
    double result = 0;
    for (auto p : purchases)
        result += p->getMoney();
    View::send(to_string((int)result));
}