#include "comment.h"
using namespace std;

Comment::Comment(string _content, int _id) : content(_content), id(_id) {}

int Comment::getId() {
    return id;
}
std::string Comment::getContent() {
    return content;
}
bool Comment::isDeleted() {
    return deleted;
}
