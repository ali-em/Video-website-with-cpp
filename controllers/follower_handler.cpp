#include "follower_handler.h"
#include "../database/database.h"
using namespace std;

FollowerHandler::FollowerHandler(Database* db, Login* _login) : DB(db), login(_login) {}
void FollowerHandler::follow(User* user, Parameters& params) {
    validateFollow(user, params);
    int pubId = stoi(params["user_id"]);
    Publisher* publisher = static_cast<Publisher*>(DB->findUserById(pubId));
    publisher->followBy(user);
    NotificationHandler::sendFollowNotif(user, publisher);
    View::success();
}
void FollowerHandler::validateFollow(User* user, Parameters& params) {
    if (!Tools::isInMap(params, "user_id"))
        throw BadRequest();
    int pubId = stoi(params["user_id"]);
    User* publisher = DB->findUserById(pubId);
    if (!publisher)
        throw NotFound();
    if (!publisher->isPublisher())
        throw BadRequest();
    if (publisher == user)
        throw BadRequest();
    Publisher* pub = static_cast<Publisher*>(publisher);
    if (pub->isFollowedBy(user))
        throw BadRequest();
}

void FollowerHandler::getFollower() {
    Publisher* publisher = static_cast<Publisher*>(login->getCurrentUser());
    View::showFollowers(publisher->getFollowersInfo());
}
