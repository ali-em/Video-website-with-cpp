#include "signup.h"
using namespace std;

SignUp::SignUp(Database* db, View* view, Login* _login) : Res(view), DB(db), login(_login) {
}
void SignUp::handleSignUp(Parameters& params) {
    validateSignUp(params);
    if (Tools::isInMap(params, 1, "publisher") && params["publisher"] == "true") {
        Publisher* newPub = new Publisher(params);
        DB->addUser(newPub);
        login->login(newPub);
    } else {
        User* newUser = new User(params);
        DB->addUser(newUser);
        login->login(newUser);
    }
    Res->send("OK");
}
void SignUp::validateSignUp(Parameters& params) {
    if (!Tools::isInMap(params, 4, "email", "username", "password", "age"))
        throw BadRequest();
    if (DB->findUserByUsername(params["username"]))
        throw BadRequest();
}