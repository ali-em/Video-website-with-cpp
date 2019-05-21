#include "notification_handler.h"
using namespace std;

void NotificationHandler::sendReplyNotif(User* sender, User* reciever) {
    string msg = "Publisher " + sender->getUsername() + " with id " + to_string(sender->getId()) + " reply to your comment.";
    Notification* notif = new Notification(msg);
    reciever->addNotif(notif);
}
void NotificationHandler::sendRegisterFilmNotif(Publisher* sender) {
    string msg = "Publisher " + sender->getUsername() + " with id " + to_string(sender->getId()) + " register new film.";
    sender->sendNotifToFollowers(new Notification(msg));
}
void NotificationHandler::sendFollowNotif(User* sender, User* reciever) {
    string msg = "User " + sender->getUsername() + " with id " + to_string(sender->getId()) + " follow you.";
    reciever->addNotif(new Notification(msg));
}
void NotificationHandler::sendBuyNotif(User* sender, User* reciever, Film* film) {
    string msg = "User " + sender->getUsername() + " with id " + to_string(sender->getId()) + " buy your film " + film->getName() + " with id " + to_string(film->getId()) + ".";
    reciever->addNotif(new Notification(msg));
}
void NotificationHandler::sendRateNotif(User* sender, User* reciever, Film* film) {
    string msg = "User " + sender->getUsername() + " with id " + to_string(sender->getId()) + " rate your film " + film->getName() + " with id " + to_string(film->getId()) + ".";
    reciever->addNotif(new Notification(msg));
}
void NotificationHandler::sendCommentNotif(User* sender, User* reciever, Film* film) {
    string msg = "User " + sender->getUsername() + " with id " + to_string(sender->getId()) + " comment on your film " + film->getName() + " with id " + to_string(film->getId()) + ".";
    reciever->addNotif(new Notification(msg));
}
void NotificationHandler::getNotifications(User* user) {
    vector<string> notifs = user->getUnReadNotifications();
    reverse(notifs.begin(), notifs.end());
    View::showNotifications(notifs);
}
void NotificationHandler::getReadNotifications(User* user, Parameters& params) {
    vector<string> notifs = user->getReadNotifications();
    reverse(notifs.begin(), notifs.end());
    vector<string> filtered;
    for (int i = 0; i < stoi(params["limit"]) && i < notifs.size(); i++)
        filtered.push_back(notifs[i]);
    View::showNotifications(filtered);
}