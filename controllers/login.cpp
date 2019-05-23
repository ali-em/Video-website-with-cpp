#include "login.h"
#include "../database/database.h"

using namespace std;

Login::Login(Database* db) : DB(db) {}
void Login::login(User* user) {
    currentUser = user;
    _isLoggedIn = true;
}
User* Login::getCurrentUser() {
    return currentUser;
}
void Login::handleLogin(Parameters& params) {
    if (!Tools::checkParam(params, 2, "username", "password") || _isLoggedIn)
        throw BadRequest();
    User* user = DB->findUserByUsernameAndPassword(params["username"], params["password"]);
    if (user) {
        login(user);
        View::success();
    } else
        throw BadRequest();
}
bool Login::isLoggedIn() { return _isLoggedIn; }

void Login::logout() {
    if (!_isLoggedIn)
        throw BadRequest();
    _isLoggedIn = false;
    View::success();
}