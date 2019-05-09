#include "publisher.h"
using namespace std;
Publisher::Publisher(std::map<std::string, std::string> params) : User(params) {
    publisher = true;
}
void Publisher::addFilm(Film* film) {
    publishedFilms.push_back(film);
}