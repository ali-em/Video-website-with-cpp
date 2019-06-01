#ifndef NOTIFICATION_HANDLER_H
#define NOTIFICATION_HANDLER_H
#include <algorithm>
#include <string>
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "tools.h"

class NotificationHandler {
   public:
    static void sendReplyNotif(User* sender, User* reciever);
    static void sendRegisterFilmNotif(Publisher* sender);
    static void sendFollowNotif(User* sender, User* reciever);
    static void sendBuyNotif(User* sender, User* reciever, Film* film);
    static void sendRateNotif(User* sender, User* reciever, Film* film);
    static void sendCommentNotif(User* sender, User* reciever, Film* film);
    static void getNotifications(User* user);
    static void getReadNotifications(User* user, Parameters& params);

   private:
};

#endif