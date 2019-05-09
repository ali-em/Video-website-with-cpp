#include "publisher.h"
using namespace std;
Publisher::Publisher(std::map<std::string, std::string> params) : User(params) {
    isPublisher = true;
}
