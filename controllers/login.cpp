#include "login.h"
#include "../database/database.h"

using namespace std;

Login::Login(Database* db, View* view) : DB(db), Res(view) {}
void Login::login(User* user) {
    currentUser = user;
    _isLoggedIn = true;
}
void Login::handleLogin(Request req) {
    if (!Tools::isInMap(req.params, 2, "username", "password"))
        throw BadRequest();
    User* user = DB->findUserByUsernameAndPassword(req.params["username"], req.params["password"]);
    if (user) {
        login(user);
        Res->send("OK");
    } else
        throw BadRequest();
}
bool Login::isLoggedIn() { return _isLoggedIn; }