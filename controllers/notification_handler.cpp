#include "notification_handler.h"
using namespace std;
NotificationHandler::NotificationHandler(Database* db, View* view, Login* _login) : DB(db), Res(view), login(_login) {}

void NotificationHandler::sendReplyNotif(User* sender, User* reciever);
void NotificationHandler::sendRegisterFilmNotif(User* sender, User* reciever);
void NotificationHandler::sendFollowNotif(User* sender, User* reciever);
void NotificationHandler::sendBuyNotif(User* sender, User* reciever);
void NotificationHandler::sendRateNotif(User* sender, User* reciever);
void NotificationHandler::sendCommentNotif(User* sender, User* reciever);
