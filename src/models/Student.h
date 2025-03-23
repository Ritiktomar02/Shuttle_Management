#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Booking.h"

class Student {
public:
    std::string name, email;
    int walletPoints = 500;
    std::vector<Booking> history;

    Student() {}
    Student(const std::string &n, const std::string &e)
        : name(n), email(e) {}
};

#endif // STUDENT_H