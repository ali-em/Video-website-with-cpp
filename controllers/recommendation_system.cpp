#include "recommendation_system.h"

using namespace std;

RecommendationSystem::RecommendationSystem(Database* db) : DB(db) {}

void RecommendationSystem::addFilm() {
    if (matrix.size() == 0) {
        matrix.push_back(vector<int>(1, 0));
        return;
    }
    for (int i = 0; i < matrix.size(); i++)
        matrix[i].push_back(0);
    matrix.push_back(vector<int>(matrix[0].size(), 0));
}

void RecommendationSystem::update(User* user, int newFilmId) {
    vector<Film*> purchasedFilms = user->getPurchased();
    for (auto p : purchasedFilms) {
        increaseCell(newFilmId - 1, p->getId() - 1);
        increaseCell(p->getId() - 1, newFilmId - 1);
    }
}

void RecommendationSystem::increaseCell(int row, int col) {
    if (row != col)
        matrix[row][col]++;
}

vector<Film*> RecommendationSystem::getRecommended(User* user, int newFilmId) {
    vector<int> filmRate = matrix[newFilmId - 1];
    vector<Film*> filmIds;
    for (int i = 0; i < 5 && i < matrix.size(); i++) {
        int index = 0;
        bool found = false;
        for (int j = 0; j < filmRate.size(); j++) {
            Film* film = DB->getFilmById(j + 1);
            if (filmRate[j] >= filmRate[index] && j + 1 != newFilmId &&
                filmRate[j] != -1 && !film->isDeleted() && !user->isPurchased(film)) {
                index = j;
                found = true;
            }
        }
        if (found) {
            filmRate[index] = -1;
            filmIds.push_back(DB->getFilmById(index + 1));
        }
    }
    return filmIds;
}
