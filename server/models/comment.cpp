#include "comment.h"
using namespace std;

Comment::Comment(string _content, int _id) : content(_content), id(_id) {}
Comment::Comment(string _content) : content(_content) {}

int Comment::getId() {
    return id;
}
std::string Comment::getContent() {
    return content;
}
bool Comment::isDeleted() {
    return deleted;
}
void Comment::setReply(Comment* reply) {
    replies.push_back(reply);
}
string Comment::getInfo() {
    stringstream result;
    result << id << ". " << content << endl;
    int i = 1;
    for (auto rep : replies)
        result << id << "." << i++ << ". " << rep->getContent() << endl;
    return result.str();
}
void Comment::remove() {
    deleted = true;
}
Comment::~Comment() {
    for (auto r : replies)
        delete r;
}
