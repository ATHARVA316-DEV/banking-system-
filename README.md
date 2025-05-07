# banking-system-
A secure and efficient banking system built purely in C. Features include user account management, transactions, password encryption, role-based access, file-based data storage, and robust error handling.
# 🏦 Silly Savings –  C-Based Banking System

A secure, file-based banking interface written purely in C. Developed by a team of PES University students, it features user and transaction management, authentication, data storage, and robust error handling.

---

## 📋 Table of Contents

- [Features](#features)
- [System Architecture](#system-architecture)
- [Module Overview](#module-overview)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Challenges & Solutions](#challenges--solutions)
- [Team](#team)

---

## ✨ Features

- **👥 User Management:** Create, update, delete, and view account details.
- **💰 Transactions:** Deposit, withdraw, transfer funds, view history.
- **🔐 Security:** Username/password login, SHA-256 password hashing, role-based access.
- **💾 File-Based Storage:** Persistent storage using binary files with struct serialization.
- **📊 Reports & Interest:** Generate statements and calculate interest.
- **🛡 Error Handling:** Input validation, data integrity checks, and logging.

---

## 🧩 System Architecture


                        +--------------------+
                        |    Main Menu       |
                        +--------------------+
                                  |
             +-------------------+-------------------+
             |                                       |
     +---------------+                       +--------------+
     | Admin Module  |                       | User Module  |
     +---------------+                       +--------------+
             |                                       |
     +----------------------+             +----------------------+
     | User Account Control |             | Transaction Manager  |
     +----------------------+             +----------------------+
             |                                       |
     +----------------------------+     +----------------------------+
     | File Storage (accounts.db) |<--->| File Storage (txnlog.db)  |
     +----------------------------+     +----------------------------+
--



## 🧱 Module Overview

| File             | Description                                |
|------------------|--------------------------------------------|
| `main.c`         | Entry point, menu system                   |
| `user.c`         | Account creation, update, delete, view     |
| `transaction.c`  | Deposit, withdrawal, transfer, history     |
| `security.c`     | Login system, hashing, access control      |
| `filemanager.c`  | File operations, backups, logging          |
| `utils.c`        | Input validation, formatting, utilities    |

---

## ▶️ Usage
bash
# Compile the project
gcc main.c user.c transaction.c security.c filemanager.c utils.c -o bank
 


## 🧠 How It Works
[User Input]
     |
     v
[Validation] ---> [Authentication]
     |                    |
     v                    v
[Main Menu] -------> [Admin/User Functions]
     |
     v
[Operations] ---> [File Storage]

