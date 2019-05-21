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
    for (auto f : films)
        cout << i++ << ". "
             << f->getInfo() << endl;
}
void View::showFilmDetails(string details, string comments, string recommended) {
    cout << details << endl
         << comments << endl
         << "Recommendation Film" << endl
         << "#. Film Id" << DIVIDER << "Film Name" << DIVIDER << "Film Length" << DIVIDER << "Film Director" << endl
         << recommended << endl;
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
