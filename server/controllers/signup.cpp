#include "signup.h"
using namespace std;

SignUp::SignUp(Database* db, Login* _login) : DB(db), login(_login) {
}
void SignUp::handleSignUp(Parameters& params) {
    validateSignUp(params);
    if (Tools::isInMap(params, "publisher") && params["publisher"] == "true") {
        Publisher* newPub = new Publisher(params);
        DB->addUser(newPub);
        login->login(newPub);
    } else {
        User* newUser = new User(params);
        DB->addUser(newUser);
        login->login(newUser);
    }
    View::success();
}
void SignUp::validateSignUp(Parameters& params) {
    if (!Tools::checkParam(params, 4, "email", "username", "password", "age"))
        throw BadRequest();
    if (DB->findUserByUsername(params["username"]))
        throw BadRequest();
    if (login->isLoggedIn())
        throw BadRequest();
}