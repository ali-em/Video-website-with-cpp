#include "user.h"
using namespace std;

string User::getUsername() {
    return username;
}
User::User(map<string, string> params) {
    username = params["username"];
    password = params["password"];
    email = params["email"];
    age = stoi(params["age"]);
}
User::User(string _email, string _username, string _password, string _age) : email(_email), username(_username), password(_password), age(stoi(_age)) {}
