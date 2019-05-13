#include "film.h"
#include "user.h"
using namespace std;

Film::Film(Parameters& params) {
    name = params["name"];
    year = stoi(params["year"]);
    length = stoi(params["length"]);
    price = stoi(params["price"]);
    summary = params["summary"];
    director = params["director"];
}
void Film::setId(int _id) { id = _id; }
int Film::getId() const { return id; }

void Film::edit(Request& req) {
    if (Tools::isInMap(req.params, 1, "name"))
        name = req.params["name"];
    if (Tools::isInMap(req.params, 1, "year"))
        year = stoi(req.params["year"]);
    if (Tools::isInMap(req.params, 1, "length"))
        length = stoi(req.params["length"]);
    if (Tools::isInMap(req.params, 1, "summary"))
        summary = req.params["summary"];
    if (Tools::isInMap(req.params, 1, "director"))
        summary = req.params["director"];
}

bool Film::isDeleted() {
    return deleted;
}

void Film::_delete() {
    deleted = true;
}

bool Film::isMatch(Parameters& params) {
    if (Tools::isInMap(params, 1, "name") && name != params["name"] ||
        Tools::isInMap(params, 1, "year") && year != stoi(params["year"]) ||
        Tools::isInMap(params, 1, "min_year") && year < stoi(params["min_year"]) ||
        Tools::isInMap(params, 1, "max_year") && year > stoi(params["max_year"]) ||
        Tools::isInMap(params, 1, "min_rate") && rate < stoi(params["min_rate"]) ||
        Tools::isInMap(params, 1, "length") && length != stoi(params["length"]) ||
        Tools::isInMap(params, 1, "summary") && summary != params["summary"] ||
        Tools::isInMap(params, 1, "director") && summary != params["director"])
        return false;
    return true;
}

string Film::getInfo() {
    stringstream result;
    result << id << DIVIDER << name << DIVIDER << length
           << DIVIDER << price << DIVIDER << setprecision(2) << rate << DIVIDER << year
           << DIVIDER << director;
    return result.str();
}
double Film::getTotalSell() {
    double result = 0;
    for (auto purchase : purchases)
        result += purchase->getMoney();
    return result;
}
int Film::getPrice() const {
    return price;
}
float Film::getRate() const {
    return rate;
}
void Film::calcRate() {
    float i = 0, sum = 0;
    for (auto r : rating) {
        sum += r.second;
        i++;
    }
    if (i == 0)
        rate = 0;
    else
        rate = sum / i;
}
void Film::setRate(User* user, int _rate) {
    for (int i = 0; i < rating.size(); i++) {
        auto r = &rating[i];
        if (r->first == user) {
            r->second = _rate;
            return;
        }
    }
    rating.push_back(pair<User*, int>(user, _rate));
    calcRate();
}
string Film::getShortInfo() {
    stringstream result;
    result << id << DIVIDER
           << name << DIVIDER
           << length << DIVIDER
           << director << DIVIDER;
    return result.str();
}
void Film::addComment(User* user, string content) {
    Comment* comment = new Comment(content, commentId++);
    comments.push_back(comment);
}
string Film::getDetails() {
    stringstream details;
    details << "Details of Film " << name << endl
            << "Id = " << id << endl
            << "Director = " << director << endl
            << "Length = " << length << endl
            << "Year = " << year << endl
            << "Summary = " << summary << endl
            << "rate = " << rate << endl
            << "price = " << price << endl;
    return details.str();
}
string Film::getComments() {
    stringstream result;
    result << "Comments" << endl;
    for (auto comment : comments) {
        if (!comment->isDeleted())
            result << comment->getInfo();
    }
    return result.str();
}
bool Film::operator<(const Film* f) const {
    if (f->getRate() == rate)
        return id < f->getId();
    return rate < f->getRate();
}
void Film::setReply(Parameters& params) {
    if (comments.size() < stoi(params["comment_id"]))
        throw NotFound();
    Comment* reply = new Comment(params["content"]);
    comments[stoi(params["comment_id"]) - 1]->setReply(reply);
}