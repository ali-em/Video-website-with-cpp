#ifndef FILM_H
#define FILM_H
#include <string>
#include <vector>
#include "purchase.h"
class Film {
   public:
   private:
    int id;
    std::string name;
    std::string summary;
    std::string director;
    int year;
    double length;
    double price;
    int totalScore;
    int numberOfScores;
    std::vector<Purchase*> purchases;
};

#endif