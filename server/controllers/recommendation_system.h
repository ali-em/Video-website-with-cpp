#ifndef REC_SYSTEM
#define REC_SYSTEM
#include <string>
#include <vector>
#include "../database/database.h"
#include "../models/modelHeaders.h"

class RecommendationSystem {
   public:
    RecommendationSystem(Database* DB);
    void addFilm();
    void update(User*, int);
    std::vector<Film*> getRecommended(User*, int);

   private:
    void increaseCell(int row, int col);
    std::vector<std::vector<int>> matrix;
    Database* DB;
};

#endif