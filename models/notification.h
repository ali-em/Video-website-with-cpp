#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
   public:
   private:
    int id;
    int userId;
    std::string content;
    bool isRead;
};

#endif