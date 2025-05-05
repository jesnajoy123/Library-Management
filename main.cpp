#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    int id;
    char title[100];
    char author[100];
    float mrp;
    int isIssued;
};

struct Book library[MAX_BOOKS];
int bookCount = 0;


void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    newBook.id = bookCount > 0 ? library[bookCount - 1].id + 1 : 1;

    printf("Enter title: ");
    getchar();  // to clear buffer
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter MRP: ");
    scanf("%f", &newBook.mrp);

    newBook.isIssued = 0;

    library[bookCount++] = newBook;

    printf("Book added successfully with ID %d\n", newBook.id);
}


void displayBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n%-5s %-30s %-30s %-10s %-10s\n", "ID", "Title", "Author", "MRP", "Status");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-5d %-30s %-30s %-10.2f %-10s\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].mrp,
               library[i].isIssued ? "Issued" : "Available");
    }
}


void buyBook() {
    int id;
    printf("Enter the ID of the book to buy: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (library[i].isIssued) {
                printf("Sorry, the book is already issued.\n");
                return;
            }

            float gst = library[i].mrp * 0.05f;
            float total = library[i].mrp + gst;

            printf("Book: %s by %s\n", library[i].title, library[i].author);
            printf("MRP: %.2f\n", library[i].mrp);
            printf("GST (5%%): %.2f\n", gst);
            printf("Total Price: %.2f\n", total);

            library[i].isIssued = 1;
            printf("Book purchased successfully!\n");
            return;
        }
    }

    printf("Book with ID %d not found.\n", id);
}


int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books\n");
        printf("3. Buy Book\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                buyBook();
                break;
            case 4:
                printf("Exiting the system.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
