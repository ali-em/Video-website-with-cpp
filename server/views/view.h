#ifndef VIEW_H
#define VIEW_H

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include "../models/modelHeaders.h"
class View {
   public:
    Parameters get();
    static void send(std::string);
    static void sendError(std::exception&);
    static std::string printFilms(std::vector<Film*>&);
    static Parameters showFilmDetails(FilmInfo, std::string comments, std::vector<Film*>);
    static void showFollowers(std::vector<UserInfo>);
    static void success();
    static void showNotifications(WordsList&);

   private:
    static void showFilmInfo(FilmInfo);
};

#endif
