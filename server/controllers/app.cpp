#include "app.h"
using namespace std;
void App::run() {
    preSetup();
    try {
        MyServer server(5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup", new ShowPage("static/signup.html"));
        server.get("/signup", new ShowPage("static/signup.html"));
        server.get("/login", new ShowPage("static/login.html"));
        server.get("/permission-denied", new ShowPage("static/permission-denied.html"));
        // server.post("/login" , new LoginHandler());
        server.get("/handcuff.png", new ShowImage("images/handcuff.png"));
        server.get("/mui.css", new ShowPage("css/mui.css"));
        server.get("/style.css", new ShowPage("css/style.css"));
        server.get("/mui.js", new ShowPage("js/mui.js"));
        server.get("/include.js", new ShowPage("js/include.js"));
        server.get("/nav.html", new ShowPage("static/nav.html"));

        // Request_struct req = Req.get();
        // if (req.command == FINISH)
        //     break;
        // handleRequest(req);
        server.run();
    } catch (exception& err) {
        View::sendError(err);
    }
}
void App::preSetup() {
    login = new Login(&DB);
    signUp = new SignUp(&DB, login);
    rs = new RecommendationSystem(&DB);
    fm = new FilmManager(&DB, rs, login);
    fh = new FollowerHandler(&DB, login);
    mh = new MoneyHandler(&DB, rs, login);
    ch = new CommentHandler(&DB, login);
}
void App::handleRequest(Request_struct req) {
    if (req.command == EMPTY)
        return;
    if (req.command == P_SIGN_UP)
        signUp->handleSignUp(req.params);
    else if (req.command == P_LOGIN)
        login->handleLogin(req.params);
    else if (req.command == P_LOGOUT)
        login->logout();

    else if (!login->isLoggedIn())
        throw PermissionDenied();
    else if (req.command == G_FILMS)
        fm->handleGetFilms(req.params);
    else if (req.command == P_FOLLOWERS)
        fh->follow(login->getCurrentUser(), req.params);
    else if (req.command == P_MONEY)
        mh->handleMoneyRequest(req.params);
    else if (req.command == P_BUY)
        mh->handleBuyRequest(req.params);
    else if (req.command == P_RATE)
        fm->handleRate(req.params);
    else if (req.command == P_COMMENTS)
        ch->sendComment(req.params);
    else if (req.command == G_PURCHASED)
        fm->handleGetPurchased(req.params);
    else if (req.command == G_NOTIFICATION)
        NotificationHandler::getNotifications(login->getCurrentUser());
    else if (req.command == G_NOTIFICATION_READ)
        NotificationHandler::getReadNotifications(login->getCurrentUser(), req.params);
    else if (req.command == G_MONEY)
        mh->getMoney();

    else if (!login->getCurrentUser()->isPublisher())
        throw PermissionDenied();
    else if (req.command == P_FILMS)
        fm->handleAddFilm(req.params);
    else if (req.command == PU_FILMS)
        fm->handleEditFilm(req.params);
    else if (req.command == D_FILMS)
        fm->handleDeleteFilm(req.params);
    else if (req.command == G_PUBLISHED)
        fm->handleGetPublished(req.params);
    else if (req.command == G_FOLLOWERS)
        fh->getFollower();
    else if (req.command == P_REPLIES)
        ch->sendReply(req.params);
    else if (req.command == D_COMMENTS)
        ch->deleteComment(req.params);
}