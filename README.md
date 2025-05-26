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

Banking Management System
│
├── Global Definitions & Constants
│   ├── #includes (stdio.h, stdlib.h, string.h, etc.)
│   ├── #defines (MAX_ACCOUNTS, FILE NAMES, etc.)
│   ├── Structs
│   │   ├── Account
│   │   └── Transaction
│   ├── Global Variables
│       ├── accounts[]
│       ├── transactions[]
│       ├── acc_count
│       └── trans_count
│
├── Utility Functions
│   ├── clear_input_buffer()
│   ├── is_valid_phone()
│   ├── get_valid_amount()
│   ├── get_current_date()
│   └── generate_account_number()
│
├── Transaction Management
│   └── add_transaction()
│
├── File Operations
│   ├── save_data()
│   └── load_data()
│
├── Account Operations
│   ├── create_account()
│   ├── view_accounts()
│   ├── find_account_index()
│   ├── deposit()
│   ├── withdraw()
│   ├── transfer_funds()
│   ├── search_account()
│   ├── modify_account()
│   ├── delete_account()
│
├── Reporting
│   ├── view_transactions()
│   ├── generate_statement()
│   └── search_by_name()
│
└── (Main Menu Logic - assumed but not shown in the snippet)

         


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

