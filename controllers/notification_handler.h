#ifndef NOTIFICATION_HANDLER_H
#define NOTIFICATION_HANDLER_H
#include <string>
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "tools.h"
class Database;

class NotificationHandler {
   public:
    NotificationHandler(Database*, View*, Login*);

   private:
    Database* DB;
    View* Res;
    Login* login;
};

#endif