#include "purchase.h"
using namespace std;

Purchase::Purchase(double _price, double _rate)
    : price(_price), rate(_rate) {}

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