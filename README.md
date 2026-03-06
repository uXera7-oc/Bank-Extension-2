# Bank System Extension 2 – Console Banking System with Users & Permissions (C++)

This repository contains **Bank System Extension 2**, an advanced **console-based banking system** written in **C++**, designed to manage **clients, users, permissions, and financial transactions**.

This project represents a **major extension** to the previous banking projects, evolving from simple client management into a **multi-user banking system** with **role-based access control**.

It is part of the practical learning path of  
**Cplusplus Problems V3**, focusing on building **realistic, scalable, and secure console applications**.

---

## 📂 Project Overview
The system is built using the **Divide and Conquer principle**, where each responsibility is handled by **dedicated, reusable functions**, improving readability, maintainability, and extensibility.

The application simulates a small banking environment using **file-based persistence**:

- **ClientsRecords.txt** → Stores client data  
- **Users.txt** → Stores system users and permissions  

---

## 🧱 Core Features

### 🔹 Client Management
- Add new clients
- Delete existing clients
- Update client information
- Find clients by account number
- Display all clients in formatted tables

### 🔹 Transactions System
- Deposit money
- Withdraw money with balance validation
- Display total balances of all clients
- Independent transaction menu

### 🔹 User Management (Extension 2)
- Login system (Username & Password)
- Add, delete, update, and find users
- List all system users
- File-based user persistence

### 🔹 Permissions & Security
- Role-based access control using **bitwise permissions**
- Each user can be granted specific privileges:
  - View clients
  - Add clients
  - Delete clients
  - Update clients
  - Find clients
  - Perform transactions
  - Manage users
- Full access option for administrators
- Access denied messages for unauthorized actions

---

## 🧾 System Design Highlights
- Multi-level menus:
  - Main Menu
  - Transactions Menu
  - Manage Users Menu
- Clean separation between:
  - Business logic functions
  - Screen/UI functions
- Data is always:
  - Loaded from files
  - Modified in memory
  - Safely rewritten back to files
- Continuous loop-based execution until logout or exit

---

## 🛠️ Technologies Used
- **Language:** C++
- **File Handling:** `<fstream>`
- **Data Structures:** `struct`, `vector`
- **Enums:** Menu navigation & permissions
- **Formatting:** `<iomanip>`
- **Standard Libraries:** `<iostream>`, `<string>`, `<cctype>`

---

## 🎯 Learning Objectives
This project strengthens understanding of:

- Designing **secure multi-user systems**
- Implementing **authentication & authorization**
- Using **bitwise operations** for permissions
- Managing persistent data using files
- Building modular, extendable console applications
- Applying **Clean Code** and **Divide & Conquer** principles

---

## 🧠 Concepts Demonstrated

### 🔹 C++ Fundamentals
- Conditions & control flow
- Loops & menu-driven programs
- Input/output handling

### 🔹 Advanced Modularity
- Reusable utility functions
- Logical grouping of features
- Centralized file operations

### 🔹 File-Based Database Simulation
- Reading structured records
- Rewriting files safely
- Synchronizing memory and storage

### 🔹 User Access Control
- Bitmask permissions
- Admin vs restricted users
- Secure feature-level authorization

---

## 🧪 Recommended Development Environment
- **Visual Studio (Windows)**  

The project is compatible with any standard C++ compiler supporting modern C++ features.

---

## 📌 Important Notes
- This project is **educational**, not production-ready
- No database is used (file-based persistence only)
- You must:
  - Start by adding users manually in **Users.txt** or through admin
  - Ensure permissions are set correctly
- The system demonstrates **real-world console application architecture**

---

## 🔄 Project Evolution
This extension builds upon earlier banking projects by adding:
- Login system
- User roles & permissions
- Admin-controlled system behavior
- More realistic banking workflows

---

## 🙏 Acknowledgment
Special thanks to:
- **Professor Abouhodhoud**
- **Programming Advices**

---

⭐ If you find this project useful, feel free to star the repository and use it as a reference for building advanced C++ console systems.
