#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
public:
    std::string name, email;
    Admin() {}
    Admin(const std::string &n, const std::string &e) : name(n), email(e) {}
};

#endif // ADMIN_H