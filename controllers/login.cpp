#include "login.h"
#include "../database/database.h"

using namespace std;

Login::Login(Database* db, View* view) : DB(db), Res(view) {}
void Login::login(User* user) {
    currentUser = user;
    _isLoggedIn = true;
}
User* Login::getCurrentUser() {
    return currentUser;
}
void Login::handleLogin(Parameters& params) {
    if (!Tools::isInMap(params, 2, "username", "password"))
        throw BadRequest();
    User* user = DB->findUserByUsernameAndPassword(params["username"], params["password"]);
    if (user) {
        login(user);
        Res->send("OK");
    } else
        throw BadRequest();
}
bool Login::isLoggedIn() { return _isLoggedIn; }