#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
const char *BOOKS_FILE = "books.dat";
// Main Library Management Function
void manageLibrary()
{
    int choice;
    do
    {
        printf("Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Check Out Book\n");
        printf("4. Return Book\n");
        printf("5. List All Books\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            removeBook();
            break;
        case 3:
            checkOutBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            listBooks();
            break;
        case 6:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void addBook()
{
    struct Book book;
    FILE *file = fopen(BOOKS_FILE, "ab+");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &book.bookId);
    printf("Enter book title: ");
    scanf(" %[^\n]s", book.title);
    printf("Enter author name: ");
    scanf(" %[^\n]s", book.author);
    printf("Enter total copies: ");
    scanf("%d", &book.totalCopies);
    book.copiesAvailable = book.totalCopies;

    fwrite(&book, sizeof(struct Book), 1, file);
    fclose(file);
    printf("Book added successfully!\n");
}

void removeBook()
{
    int id, found = 0;
    FILE *file = fopen(BOOKS_FILE, "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    printf("Enter book ID to remove: ");
    scanf("%d", &id);

    struct Book book;
    while (fread(&book, sizeof(struct Book), 1, file))
    {
        if (book.bookId != id)
        {
            fwrite(&book, sizeof(struct Book), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(BOOKS_FILE);
    rename("temp.dat", BOOKS_FILE);

    if (found)
        printf("Book removed successfully!\n");
    else
        printf("Book not found!\n");
}

void checkOutBook()
{
    int id, found = 0;
    FILE *file = fopen(BOOKS_FILE, "rb+");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    printf("Enter book ID to check out: ");
    scanf("%d", &id);

    struct Book book;
    long int size = sizeof(struct Book);
    while (fread(&book, size, 1, file))
    {
        if (book.bookId == id && book.copiesAvailable > 0)
        {
            found = 1;
            book.copiesAvailable--;
            fseek(file, -size, SEEK_CUR);
            fwrite(&book, size, 1, file);
            printf("Book checked out successfully!\n");
            break;
        }
    }

    fclose(file);
    if (!found)
        printf("Book not available or not found!\n");
}

void returnBook()
{
    int id, found = 0;
    FILE *file = fopen(BOOKS_FILE, "rb+");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    struct Book book;
    long int size = sizeof(struct Book);
    while (fread(&book, size, 1, file))
    {
        if (book.bookId == id)
        {
            found = 1;
            book.copiesAvailable++;
            fseek(file, -size, SEEK_CUR);
            fwrite(&book, size, 1, file);
            printf("Book returned successfully!\n");
            break;
        }
    }

    fclose(file);
    if (!found)
        printf("Book not found!\n");
}

void listBooks()
{
    FILE *file = fopen(BOOKS_FILE, "rb");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    struct Book book;
    printf("Available Books:\n");
    printf("ID\tTitle\tAuthor\tTotal Copies\tAvailable Copies\n");
    while (fread(&book, sizeof(struct Book), 1, file))
    {
        printf("%d\t%s\t%s\t%d\t%d\n",
               book.bookId, book.title, book.author, book.totalCopies, book.copiesAvailable);
    }

    fclose(file);
}
