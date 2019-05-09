#include "app.h"
using namespace std;
void App::run() {
    while (1) {
        Request req = Req.get();
        handleRequest(req);
        if (!isLoggedIn) continue;
    }
}
void App::handleRequest(Request req) {
    if (req.command == P_SIGN_UP)
        signUp(req);
}
void App::signUp(Request req) {
    validateSignUp(req);
    if (isInMap(req.params, 1, "publisher") && req.params["publisher"] == "true") {
        Publisher* newPub = new Publisher(req.params);
        DB.addUser(newPub);
    } else {
        User* newUser = new User(req.params);
        DB.addUser(newUser);
    }
}
void App::validateSignUp(Request req) {
    if (!isInMap(req.params, 4, "email", "username", "password", "age"))
        throw;
    if (DB.findUserByUsername(req.params["username"]))
        throw;
}
bool App::isInMap(std::map<string, string> m, int counter, const char* keys...) {
    va_list args;
    string temp;
    for (int i = 0; i < counter; i++) {
        if (i == 0) {
            va_start(args, keys);
            temp = keys;
        } else
            temp = va_arg(args, char*);
        if (m.find(temp) == m.end())
            return false;
    }
    return true;
}
