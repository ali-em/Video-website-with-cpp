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