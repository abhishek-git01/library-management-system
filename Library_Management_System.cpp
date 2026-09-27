#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cctype>

class Book {
private:
    std::string bookId;
    std::string title;
    std::string author;
    bool issued;
    std::string issuedTo;

public:
    Book() {
        bookId = "";
        title = "";
        author = "";
        issued = false;
        issuedTo = "";
    }

    Book(std::string id, std::string t, std::string a, bool status = false, std::string memberId = "") {
        bookId = id;
        title = t;
        author = a;
        issued = status;
        issuedTo = memberId;
    }

    std::string getBookId() const {
        return bookId;
    }

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    bool isIssued() const {
        return issued;
    }

    std::string getIssuedTo() const {
        return issuedTo;
    }

    void addBook() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do {
            std::cout << "\nEnter book ID: ";
            std::getline(std::cin, bookId);

            if (bookId.empty()) {
                std::cout << "Book ID cannot be empty.\n";
            }

        } while (bookId.empty());

        do {
            std::cout << "Enter book title: ";
            std::getline(std::cin, title);

            if (title.empty()) {
                std::cout << "Book title cannot be empty.\n";
            }

        } while (title.empty());

        do {
            std::cout << "Enter author name: ";
            std::getline(std::cin, author);

            if (author.empty()) {
                std::cout << "Author name cannot be empty.\n";
            }

        } while (author.empty());

        issued = false;
        issuedTo = "";

        std::cout << "\nBook added successfully!\n";
    }

    void display() const {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Book ID : " << bookId << "\n";
        std::cout << "Title   : " << title << "\n";
        std::cout << "Author  : " << author << "\n";
        std::cout << "Status  : " << (issued ? "Issued" : "Available") << "\n";

        if (issued) {
            std::cout << "Issued To: " << issuedTo << "\n";
        }

        std::cout << "----------------------------------------\n";
    }

    void issueBook(const std::string& memberId) {
        issued = true;
        issuedTo = memberId;
    }

    void returnBook() {
        issued = false;
        issuedTo = "";
    }

    void saveData(std::ofstream& file) const {
        file << bookId << "|"
             << title << "|"
             << author << "|"
             << issued << "|"
             << issuedTo << "\n";
    }
};

class Member {
private:
    std::string memberId;
    std::string name;

public:
    Member() {
        memberId = "";
        name = "";
    }

    Member(std::string id, std::string n) {
        memberId = id;
        name = n;
    }

    std::string getMemberId() const {
        return memberId;
    }

    std::string getName() const {
        return name;
    }

    void addMember() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do {
            std::cout << "\nEnter member ID: ";
            std::getline(std::cin, memberId);

            if (memberId.empty()) {
                std::cout << "Member ID cannot be empty.\n";
            }

        } while (memberId.empty());

        do {
            std::cout << "Enter member name: ";
            std::getline(std::cin, name);

            if (name.empty()) {
                std::cout << "Member name cannot be empty.\n";
            }

        } while (name.empty());

        std::cout << "\nMember registered successfully!\n";
    }

    void display() const {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Member ID : " << memberId << "\n";
        std::cout << "Name      : " << name << "\n";
        std::cout << "----------------------------------------\n";
    }

    void saveData(std::ofstream& file) const {
        file << memberId << "|" << name << "\n";
    }
};

class LibrarySystem {
private:
    std::vector<Book> books;
    std::vector<Member> members;

    std::string toLower(std::string text) const {
        std::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            }
        );

        return text;
    }

public:
    void loadBooks() {
        std::ifstream file("books.txt");

        if (!file) {
            return;
        }

        std::string id;
        std::string title;
        std::string author;
        std::string issued;
        std::string issuedTo;

        while (std::getline(file, id, '|') &&
               std::getline(file, title, '|') &&
               std::getline(file, author, '|') &&
               std::getline(file, issued, '|') &&
               std::getline(file, issuedTo)) {

            books.emplace_back(
                id,
                title,
                author,
                issued == "1",
                issuedTo
            );
        }

        file.close();
    }

    void loadMembers() {
        std::ifstream file("members.txt");

        if (!file) {
            return;
        }

        std::string id;
        std::string name;

        while (std::getline(file, id, '|') &&
               std::getline(file, name)) {

            members.emplace_back(id, name);
        }

        file.close();
    }

    void saveBooks() {
        std::ofstream file("books.txt");

        if (!file) {
            std::cout << "Error saving book data.\n";
            return;
        }

        for (const auto& book : books) {
            book.saveData(file);
        }

        file.close();
    }

    void saveMembers() {
        std::ofstream file("members.txt");

        if (!file) {
            std::cout << "Error saving member data.\n";
            return;
        }

        for (const auto& member : members) {
            member.saveData(file);
        }

        file.close();
    }

    int findBook(const std::string& bookId) const {
        for (int i = 0; i < static_cast<int>(books.size()); i++) {
            if (books[i].getBookId() == bookId) {
                return i;
            }
        }

        return -1;
    }

    int findMember(const std::string& memberId) const {
        for (int i = 0; i < static_cast<int>(members.size()); i++) {
            if (members[i].getMemberId() == memberId) {
                return i;
            }
        }

        return -1;
    }

    void addBook() {
        Book book;
        book.addBook();

        if (findBook(book.getBookId()) != -1) {
            std::cout << "Book ID already exists.\n";
            return;
        }

        books.push_back(book);
        saveBooks();

        std::cout << "Book saved successfully.\n";
    }

    void addMember() {
        Member member;
        member.addMember();

        if (findMember(member.getMemberId()) != -1) {
            std::cout << "Member ID already exists.\n";
            return;
        }

        members.push_back(member);
        saveMembers();

        std::cout << "Member saved successfully.\n";
    }

    void showAllBooks() const {
        if (books.empty()) {
            std::cout << "\nNo books found.\n";
            return;
        }

        std::cout << "\n========== ALL BOOKS ==========\n";

        for (const auto& book : books) {
            book.display();
        }
    }

    void showAllMembers() const {
        if (members.empty()) {
            std::cout << "\nNo members found.\n";
            return;
        }

        std::cout << "\n========== ALL MEMBERS ==========\n";

        for (const auto& member : members) {
            member.display();
        }
    }

    void searchBook() const {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int choice;

        std::cout << "\nSearch Book By:\n";
        std::cout << "1. Title\n";
        std::cout << "2. Author\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string searchText;

        std::cout << "Enter search text: ";
        std::getline(std::cin, searchText);

        searchText = toLower(searchText);

        bool found = false;

        for (const auto& book : books) {
            std::string value;

            if (choice == 1) {
                value = toLower(book.getTitle());
            }
            else if (choice == 2) {
                value = toLower(book.getAuthor());
            }
            else {
                std::cout << "Invalid search option.\n";
                return;
            }

            if (value.find(searchText) != std::string::npos) {
                book.display();
                found = true;
            }
        }

        if (!found) {
            std::cout << "\nNo matching book found.\n";
        }
    }

    void issueBook() {
        std::string bookId;
        std::string memberId;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "\nEnter book ID: ";
        std::getline(std::cin, bookId);

        int bookIndex = findBook(bookId);

        if (bookIndex == -1) {
            std::cout << "Book not found.\n";
            return;
        }

        if (books[bookIndex].isIssued()) {
            std::cout << "This book is already issued.\n";
            return;
        }

        std::cout << "Enter member ID: ";
        std::getline(std::cin, memberId);

        int memberIndex = findMember(memberId);

        if (memberIndex == -1) {
            std::cout << "Member not found.\n";
            return;
        }

        books[bookIndex].issueBook(memberId);
        saveBooks();

        std::cout << "\nBook issued successfully to "
                  << members[memberIndex].getName()
                  << ".\n";
    }

    void returnBook() {
        std::string bookId;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "\nEnter book ID: ";
        std::getline(std::cin, bookId);

        int bookIndex = findBook(bookId);

        if (bookIndex == -1) {
            std::cout << "Book not found.\n";
            return;
        }

        if (!books[bookIndex].isIssued()) {
            std::cout << "This book is already available.\n";
            return;
        }

        books[bookIndex].returnBook();
        saveBooks();

        std::cout << "Book returned successfully.\n";
    }

    void run() {
        loadBooks();
        loadMembers();

        int choice;

        do {
            std::cout << "\n============================================\n";
            std::cout << "          LIBRARY MANAGEMENT SYSTEM\n";
            std::cout << "============================================\n";
            std::cout << "1. Add New Book\n";
            std::cout << "2. Register New Member\n";
            std::cout << "3. Show All Books\n";
            std::cout << "4. Show All Members\n";
            std::cout << "5. Search Book\n";
            std::cout << "6. Issue Book\n";
            std::cout << "7. Return Book\n";
            std::cout << "8. Exit\n";
            std::cout << "============================================\n";
            std::cout << "Enter your choice: ";

            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );

                std::cout << "Invalid choice. Please try again.\n";
                continue;
            }

            switch (choice) {
            case 1:
                addBook();
                break;

            case 2:
                addMember();
                break;

            case 3:
                showAllBooks();
                break;

            case 4:
                showAllMembers();
                break;

            case 5:
                searchBook();
                break;

            case 6:
                issueBook();
                break;

            case 7:
                returnBook();
                break;

            case 8:
                std::cout << "\nThank you for using the Library Management System!\n";
                break;

            default:
                std::cout << "Enter a valid choice.\n";
            }

        } while (choice != 8);
    }
};

int main() {
    LibrarySystem library;
    library.run();

    return 0;
}