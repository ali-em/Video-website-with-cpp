#include "film.h"
#include "user.h"
using namespace std;

Film::Film(Request& req) {
    name = req.params["name"];
    year = stoi(req.params["year"]);
    length = stoi(req.params["length"]);
    price = stoi(req.params["price"]);
    director = req.params["director"];
}
void Film::setId(int _id) { id = _id; }
int Film::getId() { return id; }

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
        Tools::isInMap(params, 1, "min_rate") && getRate() < stoi(params["min_rate"]) ||
        Tools::isInMap(params, 1, "length") && length != stoi(params["length"]) ||
        Tools::isInMap(params, 1, "summary") && summary != params["summary"] ||
        Tools::isInMap(params, 1, "director") && summary != params["director"])
        return false;
    return true;
}

string Film::getInfo() {
    stringstream result;
    result << id << DIVIDER << name << DIVIDER << length
           << DIVIDER << price << DIVIDER << setprecision(2) << getRate() << DIVIDER << year
           << DIVIDER << director;
    return result.str();
}
double Film::getTotalSell() {
    double result = 0;
    for (auto purchase : purchases)
        result += purchase->getMoney();
    return result;
}
int Film::getPrice() {
    return price;
}
double Film::getRate() {
    double i = 0, sum = 0;
    for (auto r : rating) {
        sum += r.second;
        i++;
    }
    if (i == 0)
        return 0;
    return sum / i;
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
}
