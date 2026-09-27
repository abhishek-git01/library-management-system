# Library Management System

A C++ based Library Management System using Object-Oriented Programming (OOP) and file handling to manage books, members, and borrowing operations.

## Features

- Add new books
- Register new library members
- Display all books
- Display all members
- Search books by title
- Search books by author
- Issue books to members
- Return books
- Prevent duplicate book and member IDs
- Prevent issuing an already issued book
- Store library records using file handling
- Maintain data between program runs

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- STL Vector

## How to Run

1. Compile `Library_Management_System.cpp` using a C++ compiler.
2. Run the generated executable.
3. Add books and register members.
4. Use the menu to search, issue, and return books.

## Data Storage

Book records are stored locally in `books.txt`.

Member records are stored locally in `members.txt`.

These data files are excluded from the repository using `.gitignore`.