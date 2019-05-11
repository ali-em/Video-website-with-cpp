#include "purchase.h"
using namespace std;

Purchase::Purchase(int _userId, int _filmId, double _price, double _rate)
    : userId(_userId), filmId(_filmId), price(_price), rate(_rate) {}

double Purchase::getMoney() {
    if (hasGotten)
        return 0;
    hasGotten = true;
    double percent;
    if (rate < 5)
        percent = .8;
    else if (rate < 8)
        percent = .9;
    else
        percent = .95;
    double result = percent * price;
    price -= result;

    return result;
}