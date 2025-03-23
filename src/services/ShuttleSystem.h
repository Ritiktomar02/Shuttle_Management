#ifndef SHUTTLESYSTEM_H
#define SHUTTLESYSTEM_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Student.h"
#include "Admin.h"
#include "ShuttleRoute.h"

class ShuttleSystem {
    std::unordered_map<std::string, Student> students;
    std::unordered_map<std::string, Admin> admins;
    std::vector<ShuttleRoute> routes;

public:
    void registerAdmin(const std::string &name, const std::string &email) {
        admins[email] = Admin(name, email);
        std::cout << "✅ Admin registered: " << name << " (" << email << ")\n";
    }

    void registerStudent(const std::string &name, const std::string &email) {
        students[email] = Student(name, email);
        std::cout << "✅ Student registered: " << name << " (" << email << ")\n";
    }

    void createRoute(const std::string &name) {
        ShuttleRoute route(name);
        std::string startStop, endStop;
        std::cout << "Enter starting stop: ";
        std::cin >> startStop;
        route.addStop(startStop); // Starting stop

        int numStops;
        std::cout << "How many intermediate stops? ";
        std::cin >> numStops;

        for (int i = 0; i < numStops; ++i) {
            std::string stopName;
            std::cout << "Enter name for stop " << i + 1 << ": ";
            std::cin >> stopName;
            route.addStop(stopName);
        }

        std::cout << "Enter destination stop: ";
        std::cin >> endStop;
        route.addStop(endStop); // Destination stop

        // Ask for costs between consecutive stops
        for (size_t i = 0; i < route.stops.size() - 1; ++i) {
            int cost;
            std::cout << "Enter cost in points from " << route.stops[i].name << " to " << route.stops[i + 1].name << ": ";
            std::cin >> cost;
            route.addCost(cost);
        }

        routes.push_back(route);
        std::cout << "🚌 Shuttle route created: " << name << " with " << numStops + 2 << " stops (including start and end).\n";
    }

    void displayRoutes() const {
        if (routes.empty()) {
            std::cout << "⚠️ No routes available.\n";
            return;
        }
        for (const ShuttleRoute &route : routes) {
            std::cout << "Route: " << route.name << " | Total Cost: " << route.totalCost() << " points\n";
            for (size_t i = 0; i < route.stops.size(); ++i) {
                std::cout << "  Stop: " << route.stops[i].name << "\n";
            }
        }
    }

    void bookRide(const std::string &email) {
        if (students.find(email) == students.end()) {
            std::cout << "❌ Student not found.\n";
            return;
        }

        if (routes.empty()) {
            std::cout << "⚠️ No routes available.\n";
            return;
        }

        std::string startStop, endStop;
        std::cout << "Enter starting stop: ";
        std::cin >> startStop;
        std::cout << "Enter destination stop: ";
        std::cin >> endStop;

        int cheapestCost = std::numeric_limits<int>::max();
        ShuttleRoute *cheapestRoute = nullptr;

        for (ShuttleRoute &route : routes) {
            int startIndex = -1, endIndex = -1;

            // Find the indices of the start and end stops
            for (size_t i = 0; i < route.stops.size(); ++i) {
                if (route.stops[i].name == startStop) {
                    startIndex = i;
                }
                if (route.stops[i].name == endStop) {
                    endIndex = i;
                }
            }

            // If both stops are found in the route
            if (startIndex != -1 && endIndex != -1 && startIndex < endIndex) {
                int totalCost = route.costBetweenStops(startIndex, endIndex);
                if (totalCost < cheapestCost) {
                    cheapestCost = totalCost;
                    cheapestRoute = &route;
                }
            }
        }

        if (cheapestRoute) {
            Student &student = students[email];
            if (student.walletPoints < cheapestCost) {
                std::cout << "❌ Not enough points to book this ride.\n";
                return;
            }

            student.walletPoints -= cheapestCost;
            student.history.emplace_back(startStop, endStop, cheapestCost);
            std::cout << "✅ Ride booked from " << startStop << " to " << endStop
                      << " on route " << cheapestRoute->name << " for " << cheapestCost << " points.\n";
        } else {
            std::cout << "❌ No available route from " << startStop << " to " << endStop << ".\n";
        }
    }

    void showStudentHistory(const std::string &email) const {
        auto it = students.find(email);
        if (it == students.end()) {
            std::cout << "❌ Student not found.\n";
            return;
        }

        const Student &student = it->second;
        std::cout << "📜 Booking History for " << student.name << " (" << student.email << "):\n";
        if (student.history.empty()) {
            std::cout << "No bookings yet.\n";
            return;
        }
        for (const Booking &b : student.history) {
            std::cout << "From: " << b.from << " → " << b.to
                      << " | Points: " << b.pointsUsed
                      << " | Time: " << b.timestamp << "\n";
        }
    }

    void showStudentPoints(const std::string &email) const {
        auto it = students.find(email);
        if (it == students.end()) {
            std::cout << "❌ Student not found.\n";
            return;
        }

        std::cout << "💰 " << it->second.name << "'s Wallet Points: " << it->second.walletPoints << "\n";
    }

    void updateStudentPoints() {
        std::string adminEmail;
        std::cout << "Enter Admin Email: ";
        std::cin >> adminEmail;

        if (admins.find(adminEmail) == admins.end()) {
            std::cout << "❌ Unauthorized. Admin not found.\n";
            return;
        }

        if (students.empty()) {
            std::cout << "⚠️ No students registered.\n";
            return;
        }

        std::vector<std::string> studentEmails;
        int idx = 1;
        std::cout << "\n📍 Select Student:\n";
        for (const auto &pair : students) {
            std::cout << idx++ << ". " << pair.second.name << " (" << pair.second.email
                      << ") | Points: " << pair.second.walletPoints << "\n";
            studentEmails.push_back(pair.first);
        }

        int choice;
        std::cout << "Enter student number: ";
        std::cin >> choice;
        if (choice < 1 || choice > static_cast<int>(studentEmails.size())) {
            std::cout << "❌ Invalid selection.\n";
            return;
        }

        Student &student = students[studentEmails[choice - 1]];

        std::cout << "Choose Action:\n1. Add Points\n2. Deduct Points\nEnter choice: ";
        int action;
        std::cin >> action;

        int amount;
        std::cout << "Enter amount: ";
        std::cin >> amount;

        if (action == 1) {
            student.walletPoints += amount;
            std::cout << "✅ Added " << amount << " points. New balance: " << student.walletPoints << "\n";
        } else if (action == 2) {
            if (student.walletPoints < amount) {
                std::cout << "❌ Insufficient points.\n";
                return;
            }
            student.walletPoints -= amount;
            std::cout << "✅ Deducted " << amount << " points. New balance: " << student.walletPoints << "\n";
        } else {
            std::cout << "❌ Invalid action.\n";
        }
    }
};

#endif // SHUTTLESYSTEM_H