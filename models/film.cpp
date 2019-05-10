#include "film.h"
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
