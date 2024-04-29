#include <stdio.h>
#include <string.h>
#include "user.h"
#include "student.h"
#include "library.h"
#include "finance.h"
#include "grade.h"


// For main menu
void mainMenu()
{
    printf("+-----------------------------------+\n");
    printf("|          Main Menu                |\n");
    printf("+-----------------------------------+\n");
    printf("| Option |        System            |\n");
    printf("+-----------------------------------+\n");
    printf("|   1    | Student Information      |\n");
    printf("|   2    | Library Management       |\n");
    printf("|   3    | Financial Management     |\n");
    printf("|   4    | Grading And Assessment   |\n");
    printf("|   5    | Logout From System       |\n");
    printf("+-----------------------------------+\n");
}

// Main function

int main()
{
    int choice, loggedIn = 0;

    while (1)
    {
        printf("\nStudent Management System\n");

        if (loggedIn)
        {
            mainMenu();
        }
        else
        {
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (loggedIn)
        {
            switch (choice)
            {
            // Case for student information system goes here
            case 1:
                while (1)
                {
                    int mchoice;
                    printf("Student Information System\n");
                    printf("1. Add Student\n");
                    printf("2. Search Student\n");
                    printf("3. Modify Student\n");
                    printf("4. Delete Student\n");
                    printf("5. Display All Students\n");
                    printf("6. Go Back\n");
                    printf("Enter your choice: ");
                    scanf("%d", &mchoice);

                    // implement switch case
                    switch (mchoice)
                    {
                    case 1:
                        printf("Add Student\n");
                        // call addStudent and pass the student object returned by getInput
                        struct Student student = getInput();
                        if (addStudent(&student))
                        {
                            printf("Student added successfully!\n");
                        }
                        else
                        {
                            printf("Error adding student.\n");
                        }
                        break;
                        getInput();
                        break;
                    case 2:
                        printf("Search Student\n");
                        int rollNoToFind;
                        printf("Enter roll number of the student to search: ");
                        scanf("%d", &rollNoToFind);

                        struct Student *foundStudent = searchStudent(rollNoToFind);
                        if (foundStudent != NULL)
                        {
                         displayStudentReport(foundStudent);
                        }
                        else
                        {
                            printf("Student not found.\n");
                        }
                        break;
                    case 3:
                        int rollNoToModify;
                        printf("Enter roll number of the student to modify: ");
                        scanf("%d", &rollNoToModify);

                        struct Student newInfo = getInput();

                        if (modifyStudent(rollNoToModify, &newInfo))
                        {
                            printf("Student information modified successfully!\n");
                        }
                        else
                        {
                            printf("Error modifying student or student not found.\n");
                        }
                        break;
                        printf("Modify Student\n");
                        break;
                    case 4:
                        printf("Delete Student\n");
                        break;
                    case 5:
                        printf("Display All Students\n");
                        displayAllStudents();
                        break;
                    case 6:
                        printf("Going back...\n");
                        break;
                    default:
                        printf("Invalid choice.\n");
                    }

                    if (mchoice == 6)
                    {
                        break;
                    }
                }
                break;
          
            // Case for library management goes here
            case 2:
                manageLibrary();
                break;
            // Case for financial management goes here
            case 3:
                manageFinances();
                break;
            // Case for grading and assessment goes here
            case 4:
                manageGrading();
                break;
            // Case for logout goes here
            case 5:
                printf("Logging out...\n");
                loggedIn = 0;
                break;
            default:
                printf("Invalid choice.\n");
            }
        }
        else
        { // Not logged in
            switch (choice)
            {
                char username[20];
                char password[20];
            case 1:
                printf("Enter username: ");
                scanf("%s", username);

                printf("Enter password: ");
                scanf("%s", password);

                if (registerUser(username, password))
                {
                    printf("Registration successful!\n");
                }
                else
                {
                    printf("Registration failed.\n");
                }
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);

                printf("Enter password: ");
                scanf("%s", password);

                if (loginUser(username, password))
                {
                    printf("Login successful!\n");
                    loggedIn = 1;
                }
                else
                {
                    printf("Invalid username or password.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
            }
        }
    }
    return 0;
}
