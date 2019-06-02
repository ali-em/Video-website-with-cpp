#include "signup.h"
using namespace std;

SignUp::SignUp(Database* db, Login* _login) : DB(db), login(_login) {
}
Response* SignUp::handleSignUp(Parameters& params) {
    validateSignUp(params);
    Response* res = Response::redirect("/");
    if (Tools::isInMap(params, "publisher") && params["publisher"] == "true") {
        Publisher* newPub = new Publisher(params);
        DB->addUser(newPub);
        params["session"] = to_string(newPub->getId());
    } else {
        User* newUser = new User(params);
        DB->addUser(newUser);
        params["session"] = to_string(newUser->getId());
    }
    return res;
}
void SignUp::validateSignUp(Parameters& params) {
    if (!Tools::checkParam(params, 4, "email", "username", "password", "age"))
        throw BadRequest();
    if (DB->findUserByUsername(params["username"]))
        throw BadRequest();
    if (login->isLoggedIn())
        throw BadRequest();
}