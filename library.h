#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOK_TITLE 100
#define MAX_BOOK_AUTHOR 50

struct Book {
    int bookId;
    char title[MAX_BOOK_TITLE];
    char author[MAX_BOOK_AUTHOR];
    int totalCopies;
    int copiesAvailable;
};
// Function Prototypes
void addBook();
void removeBook();
void checkOutBook();
void returnBook();
void listBooks();

// Main Library Management Function
void manageLibrary();

#endif 
