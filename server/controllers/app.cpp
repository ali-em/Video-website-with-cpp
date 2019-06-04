#include "app.h"
using namespace std;
void App::run() {
    preSetup();
    try {
        MyServer server(5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup", new ShowPage("static/signup.html"));
        server.get("/login", new ShowPage("static/login.html"));
        server.get("/permission-denied", new ShowPage("static/permission-denied.html"));
        server.get("/badRequest", new ShowPage("static/bad-request.html"));
        server.get("/addFilm", new ShowPage("static/add_film.html"));

        server.post("/addFilm", new HandleRequest("POST films", this));
        server.get("/delete", new HandleRequest("POST delete_films", this));
        server.post("/signup", new HandleRequest("POST signup", this));
        server.post("/login", new HandleRequest("POST login", this));
        server.get("/logout", new HandleRequest("POST logout", this));
        server.get("/buy", new HandleRequest("POST buy", this));
        server.get("/", new HomeHandler("templates/home.html", this));
        server.get("/film", new FilmHandler("templates/film.html", this));
        server.post("/rate", new HandleRequest("POST rate", this));
        server.get("/handcuff.png", new ShowImage("images/handcuff.png"));
        server.get("/mui.css", new ShowPage("css/mui.css"));
        server.get("/style.css", new ShowPage("css/style.css"));
        server.get("/mui.js", new ShowPage("js/mui.js"));
        server.get("/include.js", new ShowPage("js/include.js"));
        server.get("/nav.html", new ShowPage("static/nav.html"));

        server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
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
Response* App::handleRequest(Request_struct& req) {
    Response* res;
    if (req.params["session"] == "" || DB.findUserById(stoi(req.params["session"])) == NULL)
        req.params["session"] = "";
    login->setSessionId(req.params["session"]);
    if (req.command == P_SIGN_UP)
        res = signUp->handleSignUp(req.params);
    else if (req.command == P_LOGIN)
        res = login->handleLogin(req.params);
    else if (req.command == P_LOGOUT)
        res = login->logout(req.params);

    else if (!login->isLoggedIn())
        throw PermissionDenied();

    else if (req.command == P_FOLLOWERS)
        fh->follow(login->getCurrentUser(), req.params);
    else if (req.command == P_MONEY)
        mh->handleMoneyRequest(req.params);
    else if (req.command == P_BUY)
        res = mh->handleBuyRequest(req.params);
    else if (req.command == P_RATE)
        res = fm->handleRate(req.params);
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
        res = fm->handleAddFilm(req.params);
    else if (req.command == PU_FILMS)
        fm->handleEditFilm(req.params);
    else if (req.command == D_FILMS)
        res = fm->handleDeleteFilm(req.params);
    else if (req.command == G_PUBLISHED)
        fm->handleGetPublished(req.params);
    else if (req.command == G_FOLLOWERS)
        fh->getFollower();
    else if (req.command == P_REPLIES)
        ch->sendReply(req.params);
    else if (req.command == D_COMMENTS)
        ch->deleteComment(req.params);
    return res;
}

Parameters App::handleTemplates(Request_struct& req) {
    if (req.params["session"] == "" || DB.findUserById(stoi(req.params["session"])) == NULL)
        req.params["session"] = "";
    login->setSessionId(req.params["session"]);
    try {
        if (req.command == G_FILMS)
            return fm->handleGetFilms(req.params);
    } catch (PermissionDenied) {
        throw Server::Exception("Permission Denied");
    } catch (NotFound) {
        throw Server::Exception("Not found");
    } catch (BadRequest) {
        throw Server::Exception("Bad Request");
    }
}
