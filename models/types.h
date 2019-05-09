#ifndef STRUCTS_H
#define STRUCTS_H
#include <map>
#include <string>

enum RequestCommand {
    P_SIGN_UP = 0,
    P_LOGIN,
    P_FILMS,
    PU_FILMS,
    G_FILMS,
    D_FILMS,
    G_FOLLOWERS,
    P_MONEY,
    P_REPLIES,
    D_COMMENTS,
    P_FOLLOWERS,
    P_RATE,
    P_COMMENTS,
    G_PURCHASED,
    G_NOTIFICATION,
    G_NOTIFICATION_READ,
    P_BUY
};
struct Request {
    RequestCommand command;
    std::map<std::string, std::string> params;
};

#endif