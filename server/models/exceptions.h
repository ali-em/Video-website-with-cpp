#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

class NotFound : public std::exception {
    const char* what() const throw() {
        return "Not Found";
    }
};
class BadRequest : public std::exception {
    const char* what() const throw() {
        return "Bad Request";
    }
};
class PermissionDenied : public std::exception {
    const char* what() const throw() {
        return "Permission Denied";
    }
};

#endif