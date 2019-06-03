#include "handleRequest.h"
#include "app.h"
using namespace std;

HandleRequest::HandleRequest(string type, App* a) {
    requestType = Tools::getRequestType(type);
    app = a;
}
Response* HandleRequest::callback(Request* req) {
    params = Tools::makeMapFromRequest(req);
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
