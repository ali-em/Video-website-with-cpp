#include "tools.h"
#include <iostream>
using namespace std;

bool Tools::isInMap(Parameters m, string key) {
    return (m.find(key) != m.end());
}

bool Tools::checkParam(Parameters m, int counter, const char* keys...) {
    va_list args;
    string temp;
    for (int i = 0; i < counter; i++) {
        if (i == 0) {
            va_start(args, keys);
            temp = keys;
        } else
            temp = va_arg(args, char*);
        if (!isInMap(m, temp) || !validateType(m[temp], temp))
            return false;
    }
    return true;
}
bool Tools::validateType(string content, string key) {
    if (key == "film_id" ||
        key == "year" ||
        key == "price" ||
        key == "min_year" ||
        key == "max_year" ||
        key == "length" ||
        key == "age")
        return isNumber(content);
    if (key == "email")
        return isEmail(content);

    return true;
}
bool Tools::isEmail(string email) {
    return true;

    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}
bool Tools::isNumber(string content) {
    return true;
    for (auto ch : content)
        if (!isdigit(ch))
            return false;
    return true;
}
int Tools::hashCRC32(const string& my_string) {
    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    return result.checksum();
}