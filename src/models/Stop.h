#ifndef STOP_H
#define STOP_H

#include <string>

class Stop {
public:
    std::string name;

    Stop(const std::string &n) : name(n) {}
};

#endif // STOP_H