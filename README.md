# 🏦 Banking System — CSE333 Group Project

**Course:** CSE333 – Data Structures and Algorithms
**Term:** Spring 2026
**Faculty:** Faculty of Engineering – Specialized Programs

---

## 👥 Group Members

| # | Name | ID |
|---|------|----|
| 1 | Ahmed Waleed Hussien | 2300682 |
| 2 | Omar Sherif Metawei | 2300165 |
| 3 | Ahmed Eid Fares | 2300061 |
| 4 | Mazen Hesham Mohamed | 2300624 |
| 5 | Kevin Osama Ayed | 2300358 |

---

## 📋 Project Description

A simplified banking system implemented in C++ that allows users to manage bank accounts through a clean menu-driven interface. The system supports full account lifecycle management — from creation and deletion to deposits, withdrawals, transfers, and transaction history — with all data persisted across sessions through file storage.

The project was built around three core data structures from the course, each chosen for a specific purpose, demonstrating how different structures solve different problems within the same application.

---

## 🗂️ Data Structures Used

### 1. Hash Table (`HashTable.h / HashTable.cpp`)
**Used for:** Main account storage and lookup.

The hash table maps each `accountID` to its `Account` object using the formula `id % 101`. This gives **O(1) average-case** performance for insert, search, and delete — which matters because every operation (deposit, withdraw, transfer) starts with a lookup by ID. Chaining (using a vector per bucket) handles any collisions.

### 2. Binary Search Tree — BST (`BST.h / BST.cpp`)
**Used for:** Sorted display of all accounts.

The BST stores pointers to the same `Account` objects held by the hash table. Because a BST's in-order traversal always visits nodes from smallest to largest, calling `inorder()` prints all accounts sorted by `accountID` automatically — no sorting step needed. Lookup is **O(log n)**.

### 3. Linked List (`LinkedList.h / LinkedList.cpp`)
**Used for:** Per-account transaction history.

Each `Account` owns a linked list of `Transaction` records. New transactions are always inserted at the **head** (front) of the list, so the most recent transaction is always first — no traversal needed to add a new record. This gives **O(1)** insertion and naturally displays history newest-first.

---

## ✅ Implemented Features

- **Create Account** — generates a unique ID automatically, supports `savings` and `current` types
- **Deposit** — validates amount, updates balance, records transaction with timestamp
- **Withdraw** — validates amount, enforces overdraft protection
- **Transfer** — moves funds between two accounts, records on both histories
- **Search Account** — O(1) lookup by account ID via hash table
- **Display All Accounts** — sorted by account ID via BST in-order traversal
- **Transaction History** — per-account history displayed newest-first via linked list
- **Delete Account** — removes from both hash table and BST, warns if balance remains
- **File Persistence** — data is loaded on startup and saved on exit automatically
- **Input Validation** — rejects letters where numbers are expected, rejects empty strings
- **GUI** — Graphical interface built with Qt Widgets (Qt Creator), featuring dedicated windows and input forms for each operation alongside a styled transaction display panel

---

## 📁 Project Structure

```
project/
│
├── data/
│   └── accounts.txt          
│
├── include/
│   ├── Account.h
│   ├── Bank.h
│   ├── BST.h
│   ├── HashTable.h
│   ├── LinkedList.h
│   ├── Transaction.h
│   └── Utils.h
│
├── src/
│   ├── Account.cpp
│   ├── Bank.cpp
│   ├── BST.cpp
│   ├── HashTable.cpp
│   ├── LinkedList.cpp
│   ├── Transaction.cpp
│   ├── Utils.cpp
│   └── main.cpp
│
├── tests/
│   └── test_cases.txt        
│
├── presentation/
│   └── slides.pptx
│
└── README.md
```

---

## ⚙️ How to Compile and Run

### Requirements
- A C++ compiler that supports C++11 or later (e.g. `g++`)
- A terminal / command prompt

### Compile

```bash
g++ -std=c++11 src/*.cpp -o banking_system
```

### Run

```bash
./banking_system
```

> On Windows, use `BankingSystemGUI_boxed.exe` instead.

### Notes
- Make sure the `data/` folder exists before running. The program reads and writes `data/accounts.txt` automatically.
- If no data file is found, the system starts with an empty account list.

---

## 🧪 Testing

All test cases are documented in `tests/test_cases.txt`.

The file covers 33 manual test cases across these categories:

| Category | Test IDs |
|----------|----------|
| Account Creation | TC-01 to TC-04 |
| Deposit | TC-05 to TC-09 |
| Withdraw | TC-10 to TC-13 |
| Transfer | TC-14 to TC-18 |
| Search | TC-19 to TC-20 |
| Display All | TC-21 |
| Transaction History | TC-22 to TC-24 |
| Delete Account | TC-25 to TC-27 |
| Input Validation | TC-28 to TC-29 |
| File Persistence | TC-30 to TC-31 |
| Menu Behaviour | TC-32 to TC-33 |

Each test case includes the steps to follow, exact input to enter, and the expected output to verify against.

---

## 🤖 AI Usage Declaration

### Tools Used
- **Claude (Anthropic)** — primary AI tool used throughout the project

### What it was used for
- Brainstorming the overall system design and which data structures to use
- Explaining C++ concepts (e.g. how BST in-order traversal produces sorted output)
- Debugging compile errors and logic issues
- Improving code comments and documentation
- Generating the initial structure of test cases

### What was modified or rejected
- AI-generated code was always reviewed and often restructured to match our project's specific file layout and naming conventions
- Some suggested implementations were rejected when they used C++ features beyond the course scope (e.g. smart pointers), and replaced with manual pointer management
- AI-suggested test cases were expanded and rewritten to match our exact account data and expected output values

### Example where AI output was not fully correct
When asked to write `Bank.cpp`, the AI generated `accounts.insert(acc)` passing an `Account` by value, but our `HashTable::insert()` takes an `Account*` pointer. The generated code would not compile. We identified this mismatch, understood why it happened (value vs. pointer semantics), and corrected it to `accounts.insert(new Account(acc))`.

### What the group understood and implemented themselves
Every member owns their files completely. We can explain every design decision, justify each data structure choice, discuss the time complexity of all operations, and answer modification questions. The AI was used as a learning and debugging aid — not as a replacement for understanding.

---

*CSE333 — Data Structures and Algorithms — Spring 2026*
