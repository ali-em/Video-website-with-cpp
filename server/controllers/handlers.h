#ifndef HANDLERS_H__
#define HANDLERS_H__
#include "tools.h"
class App;
class HomeHandler : public TemplateHandler {
   public:
    HomeHandler(std::string filePath, App* app);
    std::map<std::string, std::string> handle(Request* req);

   private:
    Parameters params;
    App* app;
};
class FilmHandler : public TemplateHandler {
   public:
    FilmHandler(std::string filePath, App* app);
    std::map<std::string, std::string> handle(Request* req);

   private:
    Parameters params;
    App* app;
};
#endif