#ifndef MONEY_HANDLER
#define MONEY_HANDLER
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "notification_handler.h"
#include "recommendation_system.h"
#include "tools.h"
class Database;

class MoneyHandler {
   public:
    MoneyHandler(Database*, RecommendationSystem*, Login*);
    void handleMoneyRequest(Parameters);
    void handleBuyRequest(Parameters&);
    void validateBuy(Parameters&);
    void getMoney();
    void getSystemMoney();

   private:
    Database* DB;
    Login* login;
    RecommendationSystem* RS;
};

#endif