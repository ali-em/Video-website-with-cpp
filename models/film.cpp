#include "film.h"
using namespace std;

Film::Film(Request& req) {
    name = req.params["name"];
    year = stoi(req.params["year"]);
    length = req.params["length"];
    price = stod(req.params["price"]);
    director = req.params["director"];
}
void Film::setId(int _id) { id = _id; }