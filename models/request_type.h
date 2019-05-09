#ifndef REQUEST_TYPE_H
#define REQUEST_TYPE_H
#include <map>
#include <string>

enum RequestType {
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
    RequestType command;
    std::map<std::string, std::string> params;
};

#endif