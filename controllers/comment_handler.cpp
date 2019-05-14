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
    validateCommentChange(params);
    if (!Tools::isInMap(params, 3, "film_id", "comment_id", "content"))
        throw BadRequest();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->setReply(params);
    Res->send("OK");
}
void CommentHandler::validateCommentChange(Parameters& params) {
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    Publisher* pub = static_cast<Publisher*>(login->getCurrentUser());
    if (film == NULL || film->isDeleted())
        throw NotFound();
    if (!pub->hasFilm(stoi(params["film_id"])))
        throw PermissionDenied();
}
void CommentHandler::deleteComment(Parameters& params) {
    validateCommentChange(params);
    if (!Tools::isInMap(params, 1, "comment_id"))
        throw BadRequest();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    film->deleteComment(stoi(params["comment_id"]));

    Res->send("OK");
}
