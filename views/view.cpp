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
         << "Film Id" << DIVIDER
         << "Film Name" << DIVIDER
         << "Film Length" << DIVIDER
         << "Film price" << DIVIDER
         << "Rate" << DIVIDER
         << "Production Year" << DIVIDER
         << "Film Director" << endl;
    for (auto f : films) {
        cout << i++ << ". ";
        showFilmInfo(f->getInfo());
        cout << endl;
    }
}
void View::showFilmInfo(FilmInfo filmInfo) {
    cout << filmInfo.id << DIVIDER << filmInfo.name << DIVIDER << filmInfo.length
         << DIVIDER << filmInfo.price << DIVIDER << setprecision(2) << filmInfo.rate << DIVIDER << filmInfo.year
         << DIVIDER << filmInfo.director;
}
void View::showFilmDetails(FilmInfo filmInfo, string comments, string recommended) {
    cout << "Details of Film " << filmInfo.name << endl
         << "Id = " << filmInfo.id << endl
         << "Director = " << filmInfo.director << endl
         << "Length = " << filmInfo.length << endl
         << "Year = " << filmInfo.year << endl
         << "Summary = " << filmInfo.summary << endl
         << "Rate = " << filmInfo.rate << endl
         << "Price = " << filmInfo.price << endl
         << endl
         << comments << endl
         << "Recommendation Film" << endl
         << "#. Film Id" << DIVIDER << "Film Name" << DIVIDER << "Film Length" << DIVIDER << "Film Director" << endl
         << recommended;
}
void View::showFollowers(std::vector<UserInfo> followers) {
    cout << "List of Followers" << endl
         << "#. User Id" << DIVIDER
         << "User Username" << DIVIDER
         << "User Email" << endl;

    int i = 1;
    for (auto f : followers)
        cout << i++ << ". "
             << f.userId << DIVIDER
             << f.username << DIVIDER
             << f.email << endl;
}
void View::success() {
    cout << "OK" << endl;
}
void View::showNotifications(WordsList& notifs) {
    cout << "#. Notification Message" << endl;
    int i = 1;
    for (auto n : notifs) {
        cout << i++ << ". " << n << endl;
    }
}
