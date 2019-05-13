#include "comment_handler.h"
#include "../database/database.h"
using namespace std;

CommentHandler::CommentHandler(Database* db, View* view, Login* _login) : DB(db), Res(view), login(_login) {}

void CommentHandler::sendComment(Parameters& params) {
    validateSendingComment(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->addComment(login->getCurrentUser(), params["content"]);
    Res->send("OK");
}
void CommentHandler::validateSendingComment(Parameters& params) {
    if (!Tools::isInMap(params, 2, "film_id", "content"))
        throw BadRequest();
    User* user = login->getCurrentUser();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    if (!user->isPurchased(film))
        throw PermissionDenied();
}
void CommentHandler::sendReply(Parameters& params) {
    validateReply(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->setReply(params);
    Res->send("OK");
}
void CommentHandler::validateReply(Parameters& params) {
    if (!Tools::isInMap(params, 3, "film_id", "comment_id", "content"))
        throw BadRequest();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    if (film == NULL)
        throw NotFound();
}