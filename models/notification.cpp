#include "notification.h"
using namespace std;

Notification::Notification(string _content) : content(_content) {}
void Notification::read() {
    _isRead = true;
}
bool Notification::isRead() {
    return _isRead;
}
std::string Notification::getContent() {
    return content;
}
