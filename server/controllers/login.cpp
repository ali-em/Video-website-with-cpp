#include "login.h"
#include "../database/database.h"

using namespace std;

Login::Login(Database* db) : DB(db) {}
void Login::login(User* user) {
    currentUser = user;
    _isLoggedIn = true;
}
User* Login::getCurrentUser() {
    if (currentUser == NULL)
        throw PermissionDenied();
    return currentUser;
}
void Login::setSessionId(std::string id) {
    if (id != "") {
        currentUser = DB->findUserById(stoi(id));
        _isLoggedIn = true;
    } else {
        cout << "**********************************************" << endl;
        _isLoggedIn = false;
    }
}

Response* Login::handleLogin(Parameters& params) {
    if (!Tools::checkParam(params, 2, "username", "password") || _isLoggedIn) throw BadRequest();
    User* user = DB->findUserByUsernameAndPassword(params["username"], params["password"]);
    if (user) {
        params["session"] = to_string(user->getId());
        _isLoggedIn = true;
    } else
        throw BadRequest();
    Response* res = Response::redirect("/");
    return res;
}
bool Login::isLoggedIn() { return _isLoggedIn; }

Response* Login::logout(Parameters& params) {
    if (!_isLoggedIn) {
        throw BadRequest();
    }
    _isLoggedIn = false;
    params["session"] = "";
    return Response::redirect("/login");
}