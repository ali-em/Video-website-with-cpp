#ifndef FILM_H
#define FILM_H
#include <string>
#include <vector>
#include "purchase.h"
#include "request_type.h"
class Film {
   public:
    Film(Request& req);
    void setId(int);

   private:
    int id;
    std::string name;
    std::string summary;
    std::string director;
    std::string length;
    int year;
    double price;
    int totalScore;
    int numberOfScores;
    std::vector<Purchase*> purchases;
    bool deleted = false;
};

#endif