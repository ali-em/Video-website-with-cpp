#include "input_handler.h"

using namespace std;

Request InputHandler::get() {
    string pure;
    getline(cin, pure);
    WordsList splitted = split(pure);
    Request result = parseToRequest(splitted);
    return result;
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
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == SPACE)
            continue;
        result += str[i];
    }
    return result;
}

Request InputHandler::parseToRequest(WordsList splitted) {
    RequestType rt = getReqType(splitted);
    map<std::string, std::string> params = getReqParams(splitted, rt);
    return Request{rt, params};
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
        {"POST buy ", P_BUY},
        {"POST comments ", P_COMMENTS},
        {"GET purchased ", G_PURCHASED},
        {"GET notification ", G_NOTIFICATION},
        {"GET notification read ", G_NOTIFICATION_READ},
        {"GET films ", G_FILMS},
        {"PUT films ", PU_FILMS},
        {"DELETE films ", D_FILMS},
        {"DELETE comments ", D_COMMENTS}};
    return REQUEST_TYPE.at(str);
}