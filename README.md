# banking-system-
A secure and efficient banking system built purely in C. Features include user account management, transactions, password encryption, role-based access, file-based data storage, and robust error handling.
# 🏦 Silly Savings –  C-Based Banking System

A secure, file-based banking interface written purely in C. Developed by a team of PES University students, it features user and transaction management, authentication, data storage, and robust error handling.

## 👨‍💻 Team

Atharva M

Aryan Singh

Anvith Vegi

Anvi Srinivas

Project developed at PES University as part of foundational systems programming.


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
- **💾 File-Based Storage:** Persistent storage using binary files with struct serialization.
- **📊 Reports & Interest:** Generate statements and calculate interest.
- **🛡 Error Handling:** Input validation, data integrity checks, and logging.

---

## 🧩 System Architecture

+-----------------------------------+
|         Banking System            |
|-----------------------------------|
|   User Interaction (CLI/Console)  |
|-----------------------------------|
|   Core Functional Modules         |
|   - Account Management            |
|   - Transaction Management        |
|   - Search & Reporting            |
|   - Data Persistence              |
|-----------------------------------|
|   Data Storage Files              |
|   - bank_data.dat                 |
|   - transactions.dat              |
|-----------------------------------|
         


## 🧱 Code Overview 

| Part                  | Description                                   |
|-----------------------|-----------------------------------------------|
| `Utility`             | Input validation, formatting, utilities       |
| `File Handling`       | File operations, backups, logging             |
| `Account Operations`  | Add Account, Modify Accounts, Delete Accounts |
| `Main Function`       | Menu Driven Main function, Transactions       |
| `transaction.dat`     | Deposit, withdrawal, transfer, history        |
| `bank_data.dat`       | Banking Details, Account Details              |

---

