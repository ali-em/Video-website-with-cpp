#ifndef MIDDLEWARE_H___
#define MIDDLEWARE_H___
#include "../models/modelHeaders.h"
#include "../server.hpp"
#include "tools.h"
class App;
class HandleRequest : public RequestHandler {
   public:
    ~HandleRequest(){};
    HandleRequest(std::string type, App *);
    Response *callback(Request *);

   private:
    App *app;
    RequestType getRequestType(std::string str);
    RequestType requestType;
    Parameters params;
    Parameters makeMapFromRequest(Request *);
};

#endif