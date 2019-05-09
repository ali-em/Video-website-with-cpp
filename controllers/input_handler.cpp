#include "input_handler.h"

using namespace std;

Request InputHandler::get() {
    string pure;
    getline(cin, pure);
    vector<string> splitted = split(pure);
    Request result = parseToRequest(splitted);
    return Request{};
}
vector<string> InputHandler::split(string line) {
    vector<string> result;
    string temp;
    if (line.size() == 0)
        return vector<string>(0);
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

Request InputHandler::parseToRequest(vector<string> splitted) {
    RequestType rc = getReqType(splitted);

    return Request{};
}
RequestType InputHandler::getReqType(vector<string> splitted) {
    string type;
    for (auto req : splitted) {
        if (req == "?")
            break;
        type += req + " ";
    }
    return getRequestType(type);
}
bool InputHandler::hasWord(vector<string> src, string target) {
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