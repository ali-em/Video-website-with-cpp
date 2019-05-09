#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "film.h"
#include "user.h"

class Publisher : public User {
   public:
   private:
    std::vector<Film*> publishedFilms;
    std::vector<User*> followers;
};

#endif