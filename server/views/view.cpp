#include "view.h"
using namespace std;

void View::send(std::string msg) {
    cout << msg << endl;
}
void View::sendError(std::exception& ex) {
    cout << ex.what() << endl;
}
string View::printFilms(vector<Film*>& films, bool includeDelete) {
    stringstream ss;
    for (auto f : films) {
        ss << "    <div class='mui-panel mui-col-md-6 mui-col-md-offset-3'>"
           << "            <div class='mui--text-headline'>"
           << f->getName()
           << "</div>"
           << "            <div class='mui--text-dark-secondary mui--text-caption'>"
           << f->getYear()
           << "</div>"
           << "            <hr>"
           << "            <div>"
           << "                <table class='mui-table'>"
           << "                    <tr>"
           << "                        <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Length</td>"
           << "                        <td class='mui--text-dark mui--text-body1'>"
           << f->getLength()
           << " minutes</td>"
           << "                    </tr>"
           << "                    <tr>"
           << "                        <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Director</td>"
           << "                        <td class='mui--text-dark mui--text-body1'>"
           << f->getDirector()
           << "</td>"
           << "                    </tr>"
           << "                    <tr>"
           << "                        <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Rating</td>"
           << "                        <td class='mui--text-dark mui--text-body1'>"
           << setprecision(2) << f->getRate()
           << "</td>"
           << "                    </tr>"
           << "                    <tr>"
           << "                        <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Price</td>"
           << "                        <td class='mui--text-dark mui--text-body1'>"
           << f->getPrice()
           << "$</td>"
           << "                    </tr>";
        if (includeDelete)
            ss << "                    <tr>"
               << "                        <td colspan='2'>"
               << "                           <a href='/delete?film_id=" << f->getId() << "'> <button class=' mui-btn--raised mui-btn mui-btn--flat mui-btn--danger'>Delete</button> </a></td>"
               << "                        </td>"
               << "                    </tr>"
               << "                    <tr>";

        ss << ""
           << "                        <td colspan='2'>"
           << "                        <a href='/film?film_id=" << f->getId() << "'>    <button class=' mui-btn mui-btn--flat mui-btn--primary'>More</button> </a> </td>"
           << ""
           << "                        </td>"
           << "                    </tr>"
           << "                </table>"
           << "            </div>"
           << "        </div>";
    }
    return ss.str();
}
void View::showFilmInfo(FilmInfo filmInfo) {
    cout << filmInfo.id << DIVIDER << filmInfo.name << DIVIDER << filmInfo.length
         << DIVIDER << filmInfo.price << DIVIDER << setprecision(2) << filmInfo.rate << DIVIDER << filmInfo.year
         << DIVIDER << filmInfo.director;
}
Parameters View::showFilmDetails(FilmInfo filmInfo, string comments, std::vector<Film*> RecommendedFilms) {
    stringstream ss;
    Parameters result;
    ss << "     <div class='mui--text-headline'>"
       << filmInfo.name
       << "</div>"
       << "        <div class='mui--text-dark-secondary mui--text-caption'>"
       << filmInfo.year
       << "</div>"
       << "        <hr>"
       << "        <div>"
       << "            <table class='mui-table'>"
       << "                <tr>"
       << "                    <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Length</td>"
       << "                    <td class='mui--text-dark mui--text-body1'>"
       << filmInfo.year
       << " minutes</td>"
       << "                </tr>"
       << "                <tr>"
       << "                    <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Director</td>"
       << "                    <td class='mui--text-dark mui--text-body1'>"
       << filmInfo.director
       << "</td>"
       << "                </tr>"
       << "                <tr>"
       << "                    <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Rating</td>"
       << "                    <td class='mui--text-dark mui--text-body1'>"
       << filmInfo.rate
       << "</td>"
       << "                </tr>"
       << "                <tr>"
       << "                    <td class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Price</td>"
       << "                    <td class='mui--text-dark mui--text-body1'>"
       << filmInfo.price
       << "$</td>"
       << "                </tr>"
       << "                <tr>"
       << "                    <td colspan='2' class='mui--text-dark mui--text-body1' style='font-weight: bold;'>Summary</td>"
       << ""
       << "                </tr>"
       << "                <tr>"
       << "                    <td colspan='2'>"
       << filmInfo.summary
       << "                    </td>"
       << "                </tr>"
       << "                <tr>"
       << "                    <td colspan='2'> <a href='/buy?film_id="
       << filmInfo.id
       << "'                        ><button"
       << "                            class=' mui-col-md-offset-4 mui-col-md-4  mui-btn--raised mui-btn mui-btn--primary'>Buy</button> </a>"
       << "                    </td>"
       << "                </tr>"
       << "                <tr>"
       << "                    <td colspan='2'>"
       << "                        <button"
       << "                            class=' mui-col-md-offset-4 mui-col-md-4  mui-btn--flat mui-btn mui-btn--primary'>Rate</button>"
       << "                    </td>"
       << "                </tr>"
       << "            </table>"
       << "        </div>";
    result["film"] = ss.str();
    result["comments"] = comments;
    return result;
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
