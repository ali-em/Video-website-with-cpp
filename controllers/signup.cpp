#include "signup.h"
using namespace std;

SignUp::SignUp(Database* db, View* view, Login* _login) : Res(view), DB(db), login(_login) {
}
void SignUp::handleSignUp(Request req) {
    validateSignUp(req);
    if (Tools::isInMap(req.params, 1, "publisher") && req.params["publisher"] == "true") {
        Publisher* newPub = new Publisher(req.params);
        DB->addUser(newPub);
        login->login(newPub);
    } else {
        User* newUser = new User(req.params);
        DB->addUser(newUser);
        login->login(newUser);
    }
    Res->send("OK");
}
void SignUp::validateSignUp(Request req) {
    if (!Tools::isInMap(req.params, 4, "email", "username", "password", "age"))
        throw BadRequest();
    if (DB->findUserByUsername(req.params["username"]))
        throw BadRequest();
}