#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "film.h"
#include "user.h"

class Publisher : public User {
   public:
    Publisher(std::map<std::string, std::string>);
    void addFilm(Film*);
    bool hasFilm(int);
    std::vector<Film*> getFilms();
    bool isFollowedBy(User*);
    void followBy(User*);
    std::vector<UserInfo> getFollowersInfo();
    void getMoney();
    void sendNotifToFollowers(Notification*);

   private:
    std::vector<Film*> publishedFilms;
    std::vector<User*> followers;
};

#endif