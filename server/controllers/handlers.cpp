#include "handlers.h"
#include "app.h"
using namespace std;

HandleTemplate::HandleTemplate(string request, string filePath, App* _app) : TemplateHandler(filePath), app(_app) {
    requestType = Tools::getRequestType(request);
}
map<string, string> HandleTemplate::handle(Request* req) {
    Parameters result;
    Parameters params = Tools::makeMapFromRequest(req);
    Request_struct request{requestType, params};
    result = app->handleTemplates(request);
    return result;
}