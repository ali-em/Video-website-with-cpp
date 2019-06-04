#ifndef HANDLERS_H__
#define HANDLERS_H__
#include "tools.h"
class App;

class HandleTemplate : public TemplateHandler {
   public:
    HandleTemplate(std::string , std::string filePath, App* app);
    std::map<std::string, std::string> handle(Request* req);

   private:
    Parameters params;
    RequestType requestType;
    App* app;
};
#endif