#include "signup.h"
using namespace std;

SignUp::SignUp(Database* db, View* view) : Res(view), DB(db) {
}
void SignUp::signUp(Request req) {
    validateSignUp(req);
    if (isInMap(req.params, 1, "publisher") && req.params["publisher"] == "true") {
        Publisher* newPub = new Publisher(req.params);
        DB->addUser(newPub);
        login(newPub);
    } else {
        User* newUser = new User(req.params);
        DB->addUser(newUser);
        login(newUser);
    }
    Res->send("OK");
}
void SignUp::validateSignUp(Request req) {
    if (!isInMap(req.params, 4, "email", "username", "password", "age"))
        throw BadRequest();
    if (DB->findUserByUsername(req.params["username"]))
        throw BadRequest();
}