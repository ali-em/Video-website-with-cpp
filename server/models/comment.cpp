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
        result << " <div class='mui-panel mui-col-md-6 mui-col-md-offset-3'>"
               << rep->getContent() << "</div> ";
    return result.str();
}
void Comment::remove() {
    deleted = true;
}
Comment::~Comment() {
    for (auto r : replies)
        delete r;
}
