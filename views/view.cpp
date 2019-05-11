#include "view.h"
using namespace std;

void View::send(std::string msg) {
    cout << msg << endl;
}
void View::sendError(std::exception& ex) {
    cout << ex.what() << endl;
}
void View::printFilms(vector<Film*>& films) {
    int i = 1;
    cout << "#. "
         << "Film id" << DIVIDER
         << "Film Name" << DIVIDER
         << "Film Length" << DIVIDER
         << "Film price" << DIVIDER
         << "rate" << DIVIDER
         << "Production Year" << DIVIDER
         << "Film Director" << endl;
    for (auto f : films)
        cout << i++ << ". "
             << f->getInfo() << endl;
}
void View::showFilmDetails(Film* film) {
    // cout << "Details of Film " << film->getName() << endl
    // << ""
}
void View::showFollowers(std::vector<UserInfo> followers) {
    cout << "List of Followers" << endl
         << "#. User Id" << DIVIDER
         << "User Username" << DIVIDER
         << "User email" << endl;

    int i = 1;
    for (auto f : followers)
        cout << i++ << ". "
             << f.userId << DIVIDER
             << f.username << DIVIDER
             << f.email << endl;
}
