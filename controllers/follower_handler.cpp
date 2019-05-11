#include "follower_handler.h"
#include "../database/database.h"
using namespace std;

FollowerHandler::FollowerHandler(Database* db, View* res, Login* _login) : DB(db), Res(res), login(_login) {}
void FollowerHandler::follow(User* user, Parameters& params) {
    validateFollow(user, params);
    int pubId = stoi(params["user_id"]);
    Publisher* publisher = static_cast<Publisher*>(DB->findUserById(pubId));
    publisher->followBy(user);
    Res->send("OK");
}
void FollowerHandler::validateFollow(User* user, Parameters& params) {
    if (!Tools::isInMap(params, 1, "user_id"))
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