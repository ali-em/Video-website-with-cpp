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
string Film::getName() {
    return name;
}

void Film::edit(Parameters& params) {
    if (Tools::isInMap(params, "name"))
        name = params["name"];
    if (Tools::isInMap(params, "year"))
        year = stoi(params["year"]);
    if (Tools::isInMap(params, "length"))
        length = stoi(params["length"]);
    if (Tools::isInMap(params, "summary"))
        summary = params["summary"];
    if (Tools::isInMap(params, "director"))
        summary = params["director"];
}

bool Film::isDeleted() {
    return deleted;
}

void Film::_delete() {
    deleted = true;
}

bool Film::isMatch(Parameters& params) {
    if (Tools::isInMap(params, "name") && name != params["name"] ||
        Tools::isInMap(params, "year") && year != stoi(params["year"]) ||
        Tools::isInMap(params, "min_year") && year < stoi(params["min_year"]) ||
        Tools::isInMap(params, "max_year") && year > stoi(params["max_year"]) ||
        Tools::isInMap(params, "min_rate") && rate < stoi(params["min_rate"]) ||
        Tools::isInMap(params, "length") && length != stoi(params["length"]) ||
        Tools::isInMap(params, "summary") && summary != params["summary"] ||
        Tools::isInMap(params, "director") && summary != params["director"])
        return false;
    return true;
}

FilmInfo Film::getInfo() {
    return FilmInfo{id, name, length, price, rate, year, director, ""};
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
           << director;
    return result.str();
}
void Film::addComment(User* user, string content) {
    Comment* comment = new Comment(content, commentId++);
    comments.push_back(comment);
}
FilmInfo Film::getDetails() {
    return FilmInfo{id, name, length, price, rate, year, director, summary};
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
void Film::deleteComment(int commentId) {
    if (comments[commentId - 1]->isDeleted())
        throw NotFound();
    comments[commentId - 1]->remove();
}