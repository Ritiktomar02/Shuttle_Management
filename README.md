# 🚍 Shuttle Management System

A **C++ console-based project** designed to efficiently manage campus shuttle services. It enables shuttle route creation, fare management between stops, student ride bookings, and wallet-based transactions.

---

## 📌 Overview

The **Shuttle Management System** offers a centralized and scalable approach to manage on-campus transport operations. It features **role-based functionality**, covering both **admin-controlled route management** and **student-centered booking systems**.

---

## 👥 User Roles

### 🧑‍🎓 Student
- Register/login using name and email
- Browse available shuttle routes
- Book rides between desired stops
- Wallet-based fare deduction (starting balance: 500 points)
- View full ride booking history

### 🛠️ Admin
- Register new shuttle routes
- Add stop lists and define fare between stop pairs
- View and manage all registered routes and fare matrices

---

## ✨ Key Features

- 🔐 Role-based system: Admin / Student
- 🛣️ Custom route creation with multiple stops
- 💸 Fare calculation based on selected stops
- 💼 Student wallet with auto-deduction on booking
- 📊 Booking history tracking for transparency
- 🗃️ In-memory data storage (no database required)

---

## 🧠 System Architecture

### 1. Core Modules & Components

#### A. Models (Data Layer)
- `User` – Base class for all users.
- `Student` – Inherits from User, stores wallet balance and booking history.
- `Admin` – Inherits from User, manages routes and fares.
- `Route` – Stores list of stops and their fare mapping.
- `Booking` – Stores ride booking details per student.

#### B. Services (Logic Layer)
- `BookingService` – Handles ride booking, fare deduction, and history.
- `AdminService` – Manages route registration and fare configurations.

#### C. UI Layer (Menu & Interaction)
- `MainMenu` – Role selection menu (Student/Admin).
- `StudentMenu` – Student operations like booking, wallet check, and ride history.
- `AdminMenu` – Admin operations like adding routes and setting fares.

#### D. Data Layer (In-Memory Storage)
- `routesDB` – Stores all shuttle routes.
- `studentsDB` – Stores registered students and their wallets.
- `bookingHistory` – Tracks bookings by student ID.
- `fareMatrix` – Stores fare between stops for each route.

---

## 🔁 Workflow: Booking a Shuttle Ride

### ✅ Step 1: Student Registration/Login
- Student signs up with name and email.
- Wallet initialized with 500 points.

### 🚏 Step 2: Browse Routes
- Student views all available shuttle routes and their stops.

### 🚌 Step 3: Book Ride
- Student selects start and destination stop.
- System calculates fare.
- Fare deducted from wallet, booking logged.

### 🧾 Step 4: View Booking History
- Student can view all past ride bookings with timestamps.

### 🛠️ Admin Control
- Admin adds new shuttle routes.
- Admin defines fare between stops.
- Admin can view/edit existing route details.

---

## 🗃️ In-Memory Database Schema

| Table Name     | Fields                                           | Description                            |
|----------------|--------------------------------------------------|----------------------------------------|
| `Users`        | `id`, `name`, `role`                             | Stores common user data                |
| `Students`     | `id`, `name`, `email`, `wallet`, `history`       | Student details with wallet & bookings |
| `Routes`       | `routeId`, `stops[]`, `fareMatrix`               | Stores shuttle routes and fares        |
| `Booking`      | `bookingId`, `studentId`, `routeId`, `startStop`, `endStop`, `fare`, `timestamp` | Individual bookings                    |

---

## 🛠️ Tech Stack

- **Language:** C++
- **Approach:** Object-Oriented Programming (OOP)
- **Compiler:** G++ / GCC
- **Interface:** Console-based

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/shuttle-management-system.git
cd shuttle-management-system

