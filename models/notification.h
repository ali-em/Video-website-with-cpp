#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
   public:
    Notification(std::string content);
    void read();
    bool isRead();
    std::string getContent();

   private:
    std::string content;
    bool _isRead = false;
};

#endif