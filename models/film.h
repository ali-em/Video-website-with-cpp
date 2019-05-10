#ifndef FILM_H
#define FILM_H
#include <sstream>
#include <string>
#include <vector>
#include "../controllers/tools.h"
#include "../views/view.h"
#include "purchase.h"
#include "request_type.h"
class Film {
   public:
    Film(Request& req);
    void setId(int);
    int getId();
    void edit(Request&);
    bool isDeleted();
    void _delete();
    bool isMatch(Parameters&);
    std::string getInfo();

   private:
    int id;
    std::string name;
    std::string summary;
    std::string director;
    int length;
    int year;
    int price;
    int totalScore;
    int numberOfScores;
    std::vector<Purchase*> purchases;
    bool deleted = false;
    int rate;
};

#endif