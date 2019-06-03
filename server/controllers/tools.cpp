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

Parameters Tools::makeMapFromRequest(Request* req) {
    Parameters result;
    static string possible[] = {
        "film_id",
        "publisher",
        "age",
        "username",
        "password",
        "name",
        "email",
        "user_id",
        "summary",
        "director",
        "length",
        "year",
        "min_year",
        "max_year",
        "rate",
        "price",
        "min_rate",
        "max_rate",
        "comment_id",
        "content",
        "amount",
        "score",
        "limit"};
    for (auto p : possible) {
        string content = req->getBodyParam(p) != "" ? req->getBodyParam(p) : req->getQueryParam(p);
        if (content != "")
            result[p] = content;
    }
    result["session"] = req->getSessionId();
    return result;
}

RequestType Tools::getRequestType(string str) {
    std::map<std::string, RequestType> REQUEST_TYPE = {
        {"POST signup", P_SIGN_UP},
        {"POST login", P_LOGIN},
        {"POST films", P_FILMS},
        {"POST replies", P_REPLIES},
        {"POST followers", P_FOLLOWERS},
        {"GET followers", G_FOLLOWERS},
        {"POST rate", P_RATE},
        {"POST buy", P_BUY},
        {"POST comments", P_COMMENTS},
        {"POST money", P_MONEY},
        {"GET purchased", G_PURCHASED},
        {"GET notifications", G_NOTIFICATION},
        {"GET notifications read", G_NOTIFICATION_READ},
        {"GET films", G_FILMS},
        {"GET published", G_PUBLISHED},
        {"POST put_films", PU_FILMS},
        {"POST delete_films", D_FILMS},
        {"POST logout", P_LOGOUT},
        {"GET money", G_MONEY},
        {"POST delete_comments", D_COMMENTS},
        {"", EMPTY}};
    return REQUEST_TYPE.at(str);
}