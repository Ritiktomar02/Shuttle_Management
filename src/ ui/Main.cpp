#include <iostream>
#include "services/ShuttleSystem.h"

int main() {
    ShuttleSystem sms;

    std::string adminName, adminEmail;
    std::cout << "Enter admin name to register: ";
    std::cin >> adminName;
    std::cout << "Enter admin email to register: ";
    std::cin >> adminEmail;
    sms.registerAdmin(adminName, adminEmail);

    int numRoutes;
    std::cout << "How many routes do you want to create? ";
    std::cin >> numRoutes;
    for (int i = 0; i < numRoutes; ++i) {
        std::string routeName;
        std::cout << "Enter name for route " << i + 1 << ": ";
        std::cin >> routeName;
        sms.createRoute(routeName);
    }

    int choice;
    do {
        std::cout << "\n--- 🛣️ Shuttle Management System Menu ---\n";
        std::cout << "1. Register Student\n";
        std::cout << "2. Display Shuttle Routes\n";
        std::cout << "3. Book a Ride (Student)\n";
        std::cout << "4. Show Booking History (Student)\n";
        std::cout << "5. Show Wallet Points (Student)\n";
        std::cout << "6. Update Wallet Points (Admin)\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string email;

        switch (choice) {
            case 1:
                {
                    std::string name;
                    std::cout << "Enter student name: ";
                    std::cin >> name;
                    std::cout << "Enter student email: ";
                    std::cin >> email;
                    sms.registerStudent(name, email);
                    break;
                }
            case 2:
                sms.displayRoutes();
                break;
            case 3:
                std::cout << "Enter student email: ";
                std::cin >> email;
                sms.bookRide(email);
                break;
            case 4:
                std::cout << "Enter student email: ";
                std::cin >> email;
                sms.showStudentHistory(email);
                break;
            case 5:
                std::cout << "Enter student email: ";
                std::cin >> email;
                sms.showStudentPoints(email);
                break;
            case 6:
                sms.updateStudentPoints();
                break;
            case 0:
                std::cout << "👋 Exiting Shuttle System. Goodbye!\n";
                break;
            default:
                std::cout << "❌ Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}