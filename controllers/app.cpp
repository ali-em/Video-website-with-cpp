#include "app.h"
using namespace std;
void App::run() {
    login = new Login(&DB, &Res);
    signUp = new SignUp(&DB, &Res, login);
    fm = new FilmManager(&DB, &Res, login);
    fh = new FollowerHandler(&DB, &Res, login);
    while (1) {
        try {
            Request req = Req.get();
            handleRequest(req);
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

    else if (!login->isLoggedIn())
        throw PermissionDenied();

    else if (req.command == G_FILMS)
        fm->handleGetFilms(req);
    else if (req.command == P_FOLLOWERS)
        fh->follow(login->getCurrentUser(), req.params);

    else if (!login->getCurrentUser()->isPublisher())
        throw PermissionDenied();

    else if (req.command == P_FILMS)
        fm->handleAddFilm(req);
    else if (req.command == PU_FILMS)
        fm->handleEditFilm(req);
    else if (req.command == D_FILMS)
        fm->handleDeleteFilm(req);
    else if (req.command == G_FOLLOWERS)
        fh->getFollower();
}
