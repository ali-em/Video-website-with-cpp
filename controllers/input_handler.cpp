#include "input_handler.h"
using namespace std;

Request InputHandler::get() {
    string pure;
    getline(cin, pure);
    vector<string> splitted = split(pure);
    for (auto s : splitted)
        cout << s << endl;
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