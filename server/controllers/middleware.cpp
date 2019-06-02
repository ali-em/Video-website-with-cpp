#include "middleware.h"
#include "app.h"
using namespace std;

HandleRequest::HandleRequest(string type, App* a) {
    requestType = getRequestType(type);
    app = a;
}
Response* HandleRequest::callback(Request* req) {
    params = makeMapFromRequest(req);
    Response* res;
    Request_struct request = {requestType, params};
    try {
        res = app->handleRequest(request);
    } catch (BadRequest) {
        res = Response::redirect("/badRequest");
    } catch (NotFound) {
        res = Response::redirect("/404");
    } catch (PermissionDenied) {
        res = Response::redirect("/permission-denied");
    }
    res->setSessionId(request.params["session"]);
    return res;
}

Parameters HandleRequest::makeMapFromRequest(Request* req) {
    Parameters result;
    static string possible[] = {
        "film_id",
        "publisher",
        "age",
        "username",
        "password",
        "name",
        "email",
        "user_id",
        "summary",
        "director",
        "length",
        "year",
        "min_year",
        "max_year",
        "rate",
        "price",
        "min_rate",
        "max_rate",
        "comment_id",
        "content",
        "amount",
        "score",
        "limit"};
    for (auto p : possible) {
        string content = req->getBodyParam(p) != "" ? req->getBodyParam(p) : req->getQueryParam(p);
        if (content != "")
            result[p] = content;
    }
    result["session"] = req->getSessionId();
    return result;
}

RequestType HandleRequest::getRequestType(string str) {
    std::map<std::string, RequestType> REQUEST_TYPE = {
        {"POST signup", P_SIGN_UP},
        {"POST login", P_LOGIN},
        {"POST films", P_FILMS},
        {"POST replies", P_REPLIES},
        {"POST followers", P_FOLLOWERS},
        {"GET followers", G_FOLLOWERS},
        {"POST rate", P_RATE},
        {"POST buy", P_BUY},
        {"POST comments", P_COMMENTS},
        {"POST money", P_MONEY},
        {"GET purchased", G_PURCHASED},
        {"GET notifications", G_NOTIFICATION},
        {"GET notifications read", G_NOTIFICATION_READ},
        {"GET films", G_FILMS},
        {"GET published", G_PUBLISHED},
        {"POST put_films", PU_FILMS},
        {"POST delete_films", D_FILMS},
        {"POST logout", P_LOGOUT},
        {"GET money", G_MONEY},
        {"POST delete_comments", D_COMMENTS},
        {"", EMPTY}};
    return REQUEST_TYPE.at(str);
}