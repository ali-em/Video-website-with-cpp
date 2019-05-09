#include "app.h"
using namespace std;
void App::run() {
    login = new Login(&DB, &Res);
    signUp = new SignUp(&DB, &Res, login);
    fm = new FilmManager(&DB, &Res, login);
    while (1) {
        try {
            Request req = Req.get();
            handleRequest(req);
            if (!login->isLoggedIn())
                throw PermissionDenied();
        } catch (exception& err) {
            Res.sendError(err);
        }
    }
}
void App::handleRequest(Request req) {
    if (req.command == P_SIGN_UP)
        signUp->handleSignUp(req);
    else if (req.command == P_LOGIN)
        login->handleLogin(req);
    else if (req.command == P_FILMS)
        fm->handleAddFilm(req);
}
