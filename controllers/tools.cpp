#include "tools.h"
using namespace std;

bool Tools::isInMap(std::map<string, string> m, int counter, const char* keys...) {
    va_list args;
    string temp;
    for (int i = 0; i < counter; i++) {
        if (i == 0) {
            va_start(args, keys);
            temp = keys;
        } else
            temp = va_arg(args, char*);
        if (m.find(temp) == m.end())
            return false;
    }
    return true;
}