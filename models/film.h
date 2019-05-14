#ifndef FILM_H
#define FILM_H
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "../controllers/tools.h"
#include "comment.h"
#include "exceptions.h"
#include "purchase.h"
#include "request_type.h"
#define DIVIDER " | "
class User;
class Film {
   public:
    Film(Parameters&);
    void setId(int);
    int getId() const;
    void edit(Request&);
    bool isDeleted();
    void _delete();
    bool isMatch(Parameters&);
    std::string getInfo();
    double getTotalSell();
    int getPrice() const;
    float getRate() const;
    void setRate(User*, int);
    void addComment(User*, std::string);
    std::string getDetails();
    std::string getComments();
    bool operator<(const Film* film) const;
    std::string getShortInfo();
    void setReply(Parameters&);
    void deleteComment(int);

   private:
    int id;
    std::string name;
    std::string summary;
    std::string director;
    int length;
    int year;
    int price;
    int commentId = 1;
    bool deleted = false;
    float rate;
    std::vector<Comment*> comments;
    std::vector<std::pair<User*, int>> rating;
    std::vector<Purchase*> purchases;
    void calcRate();
};

#endif