#include "handlers.h"
#include "app.h"
using namespace std;
HomeHandler::HomeHandler(string filePath, App* _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> HomeHandler::handle(Request* req) {
    Parameters result;
    Parameters params = Tools::makeMapFromRequest(req);
    Request_struct request{G_FILMS, params};
    result = app->handleTemplates(request);
    return result;
}

FilmHandler::FilmHandler(string filePath, App* _app) : TemplateHandler(filePath), app(_app) {}
map<string, string> FilmHandler::handle(Request* req) {
    Parameters result;
    Parameters params = Tools::makeMapFromRequest(req);
    Request_struct request{G_FILMS, params};
    result = app->handleTemplates(request);
    return result;
}
