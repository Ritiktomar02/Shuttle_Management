#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <ctime>
#include <iomanip>

class Booking {
public:
    std::string from, to;
    int pointsUsed;
    std::string timestamp;

    Booking(const std::string &f, const std::string &t, int p)
        : from(f), to(t), pointsUsed(p) {
        std::time_t now = std::time(0);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        timestamp = buffer;
    }
};

#endif // BOOKING_H