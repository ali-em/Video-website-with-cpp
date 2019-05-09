#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "film.h"
#include "user.h"

class Publisher : public User {
   public:
    Publisher(std::map<std::string, std::string>);
    void addFilm(Film*);

   private:
    std::vector<Film*> publishedFilms;
    std::vector<User*> followers;
};

#endif