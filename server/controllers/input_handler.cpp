#include "input_handler.h"

using namespace std;

Request_struct InputHandler::get() {
    string pure;

    if (!getline(cin, pure))
        return Request_struct{FINISH, {}};
    WordsList splitted = split(pure);
    if (splitted.size() < 2)
        return Request_struct{EMPTY, {}};
    return parseToRequest(splitted);
}

WordsList InputHandler::split(string line) {
    WordsList result;
    string temp;
    if (line.size() == 0)
        return WordsList(0);
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == SPACE) {
            if (temp != " " && temp.length() > 0)
                result.push_back(trim(temp));
            temp = "";
        } else
            temp += line[i];
    }
    if (temp.size() > 0)
        result.push_back(trim(temp));
    return result;
}

string InputHandler::trim(string str) {
    string result;
    for (int i = 0; i < str.length(); i++)
        if (str[i] != SPACE)
            result += str[i];
    return result;
}

Request_struct InputHandler::parseToRequest(WordsList splitted) {
    RequestType rt = getReqType(splitted);
    map<std::string, std::string> params = getReqParams(splitted, rt);
    return Request_struct{rt, params};
}
Parameters InputHandler::getReqParams(WordsList splitted, RequestType rt) {
    Parameters result;
    WordsList parameters = getReqPart(splitted);
    validateRequest(parameters, rt);
    for (int i = 0; i < parameters.size(); i += 2)
        result[parameters[i]] = parameters[i + 1];
    return result;
}
WordsList InputHandler::getReqPart(WordsList splitted) {
    bool foundQMark = false;
    WordsList result;
    for (int i = 0; i < splitted.size(); i++) {
        if (splitted[i] == "?") {
            foundQMark = true;
            continue;
        }
        if (foundQMark)
            result.push_back(splitted[i]);
    }
    return result;
}
void InputHandler::validateRequest(WordsList params, RequestType rt) {
    if (params.size() % 2 == 1)
        throw BadRequest();
}
RequestType InputHandler::getReqType(WordsList splitted) {
    string type;
    for (auto req : splitted) {
        if (req == "?")
            break;
        type += req + " ";
    }
    if (splitted[0] != "PUT" && splitted[0] != "POST" &&
        splitted[0] != "DELETE" && splitted[0] != "GET")
        throw BadRequest();
    try {
        return getRequestType(type);
    } catch (...) {
        throw NotFound();
    }
}

bool InputHandler::hasWord(WordsList src, string target) {
    for (auto w : src)
        if (w == target)
            return true;
    return false;
}

RequestType InputHandler::getRequestType(string str) {
    std::map<std::string, RequestType> REQUEST_TYPE = {
        {"POST signup ", P_SIGN_UP},
        {"POST login ", P_LOGIN},
        {"POST films ", P_FILMS},
        {"POST replies ", P_REPLIES},
        {"POST followers ", P_FOLLOWERS},
        {"GET followers ", G_FOLLOWERS},
        {"POST rate ", P_RATE},
        {"POST buy ", P_BUY},
        {"POST comments ", P_COMMENTS},
        {"POST money ", P_MONEY},
        {"GET purchased ", G_PURCHASED},
        {"GET notifications ", G_NOTIFICATION},
        {"GET notifications read ", G_NOTIFICATION_READ},
        {"GET films ", G_FILMS},
        {"GET published ", G_PUBLISHED},
        {"POST put_films ", PU_FILMS},
        {"POST delete_films ", D_FILMS},
        {"POST logout ", P_LOGOUT},
        {"GET money ", G_MONEY},
        {"POST delete_comments ", D_COMMENTS},
        {"", EMPTY}};
    return REQUEST_TYPE.at(str);
}