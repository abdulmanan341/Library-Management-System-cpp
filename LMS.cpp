#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

class Book {
public:
    string title;
    string author;
    int quantity;

    Book() : title(""), author(""), quantity(0) {}

    Book(string t, string a, int q) : title(t), author(a), quantity(q) {}

    void displayBook() const {
        cout << setw(30) << left << title
            << setw(30) << left << author
            << setw(5) << right << quantity << endl;
    }

    void decreaseQuantity() {
        if (quantity > 0)
            quantity--;
    }

    void increaseQuantity() {
        quantity++;
    }

    bool isAvailable() const {
        return quantity > 0;
    }
};

class User {
protected:
    string username;
    string password;

public:
    virtual void registerUser() = 0;
    virtual bool login(const string& username, const string& password) = 0;
    virtual void displayBooks(Book books[], int numBooks) = 0;
    virtual void issueBook(Book books[], int numBooks) = 0;
    virtual void returnBook(Book books[], int numBooks) = 0;
};

class Student : public User {
public:
    void registerUser() override {
        cout << "Enter username: "; 
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Student registration successful!\n";
    }

    bool login(const string& u, const string& p) override {
        return (username == u && password == p);
    }

    void displayBooks(Book books[], int numBooks) override {
        cout << "\n--- Books Available ---\n";
        cout << setw(30) << left << "Title" << setw(30) << left << "Author" << setw(5) << right << "Qty" << endl;
        for (int i = 0; i < numBooks; i++) {
            books[i].displayBook();
        }
        cout << endl;
    }

    void issueBook(Book books[], int numBooks) override {
        string bookName;
        cout << "Enter the title of the book you want to issue: ";
        cin.ignore();
        getline(cin, bookName);

        for (int i = 0; i < numBooks; i++) {
            if (books[i].title == bookName && books[i].isAvailable()) {
                books[i].decreaseQuantity();
                cout << "Book issued successfully!\n";
                return;
            }
        }
        cout << "Sorry, the book is not available or doesn't exist.\n";
    }

    void returnBook(Book books[], int numBooks) override {
        string bookName;
        cout << "Enter the title of the book you want to return: ";
        cin.ignore();
        getline(cin, bookName);

        for (int i = 0; i < numBooks; i++) {
            if (books[i].title == bookName) {
                books[i].increaseQuantity();
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "Invalid book name.\n";
    }
};

class Teacher : public User {
public:
    void registerUser() override {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Teacher registration successful!\n";
    }

    bool login(const string& u, const string& p) override {
        return (username == u && password == p);
    }

    void displayBooks(Book books[], int numBooks) override {
        cout << "\n--- Books Available ---\n";
        cout << setw(30) << left << "Title" << setw(30) << left << "Author" << setw(5) << right << "Qty" << endl;
        for (int i = 0; i < numBooks; i++) {
            books[i].displayBook();
        }
        cout << endl;
    }

    void issueBook(Book books[], int numBooks) override {
        string bookName;
        cout << "Enter the title of the book you want to issue: ";
        cin.ignore();
        getline(cin, bookName);

        for (int i = 0; i < numBooks; i++) {
            if (books[i].title == bookName && books[i].isAvailable()) {
                books[i].decreaseQuantity();
                cout << "Book issued successfully!\n";
                return;
            }
        }
        cout << "Sorry, the book is not available or doesn't exist.\n";
    }

    void returnBook(Book books[], int numBooks) override {
        string bookName;
        cout << "Enter the title of the book you want to return: ";
        cin.ignore();
        getline(cin, bookName);

        for (int i = 0; i < numBooks; i++) {
            if (books[i].title == bookName) {
                books[i].increaseQuantity();
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "Invalid book name.\n";
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    User* users[MAX_USERS];
    int numBooks;
    int numUsers;
    User* currentUser; 

public:
    Library() : numBooks(0), numUsers(0), currentUser(nullptr) {}

    void addBook(const string& title, const string& author, int quantity) {
        if (numBooks < MAX_BOOKS) {
            books[numBooks++] = Book(title, author, quantity);
        }
        else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    void addUser(User* user) {
        if (numUsers < MAX_USERS) {
            users[numUsers++] = user;
        }
        else {
            cout << "User limit reached.\n";
        }
    }

    void registerUser() {
        cout << "\n( Registration Process )";
        cout << endl;
        int choice;
        cout << "\nAre you a:\n1. Student\n2. Teacher\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            User* user = new Student();
            user->registerUser();
            addUser(user);
        }
        else if (choice == 2) {
            User* user = new Teacher();
            user->registerUser();
            addUser(user);
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    bool loginUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (int i = 0; i < numUsers; i++) {
            if (users[i]->login(username, password)) {
                currentUser = users[i];
                cout << "Login successful!\n";
                return true;
            }
        }
        cout << "Invalid username or password.\n";
        return false;
    }

    void displayBooks() {
        if (numBooks == 0) {
            cout << "No books available in the library.\n";
        }
        else {
            cout << "\n--- Library Books ---\n";
            cout << setw(30) << left << "Title" << setw(30) << left << "Author" << setw(5) << right << "Qty" << endl;
            for (int i = 0; i < numBooks; i++) {
                books[i].displayBook();
            }
            cout << endl;
        }
    }

    void manageLibrary() {
        if (!currentUser) {
            cout << "No user logged in.\n";
            return;
        }

        int choice;
        while (true) {
            cout << "\n1. Display Books\n";
            cout << "2. Issue Book\n";
            cout << "3. Return Book\n";
            cout << "4. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                currentUser->displayBooks(books, numBooks);
                break;
            case 2:
                currentUser->issueBook(books, numBooks);
                break;
            case 3:
                currentUser->returnBook(books, numBooks);
                break;
            case 4:
                cout << "Logging out...\n";
                currentUser = nullptr;
                return;
            default:
                cout << "Invalid choice.\n";
            }
        }
    }
};

int main() {
    Library library;

    library.addBook("C++ Programming", "Bjarne Stroustrup", 5);
    library.addBook("Data Structures", "Mark Allen Weiss", 3);
    library.addBook("Object Oriented Programming", "Eckel", 4);

    int choice;

    while (true) {
        cout << "\n1. Register User\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.registerUser();
            break;
        case 2:
            if (library.loginUser()) {
                library.manageLibrary();
            }
            break;
        case 3:
            cout << "Exiting system...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
