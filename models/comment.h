#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include <vector>

class Comment {
   public:
   private:
    int id;
    int filmId;
    std::vector<Comment*> replies;
    std::string content;
};

#endif