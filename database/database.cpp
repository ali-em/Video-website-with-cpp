#include "database.h"
using namespace std;

User* Database::findUserByUsername(string username) {
    for (auto user : users)
        if (user->getUsername() == username)
            return user;
    return NULL;
}