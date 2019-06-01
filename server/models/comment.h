#ifndef COMMENT_H
#define COMMENT_H
#include <sstream>
#include <string>
#include <vector>

class Comment {
   public:
    Comment(std::string, int);
    Comment(std::string);
    ~Comment();
    void remove();
    int getId();
    std::string getContent();
    bool isDeleted();
    void setReply(Comment*);
    std::string getInfo();

   private:
    int id;
    std::vector<Comment*> replies;
    std::string content;
    bool deleted = false;
};

#endif