#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include <vector>

class Comment {
   public:
    Comment(std::string, int);
    void remove();
    int getId();
    std::string getContent();
    bool isDeleted();

   private:
    int id;
    std::vector<Comment*> replies;
    std::string content;
    bool deleted = false;
};

#endif