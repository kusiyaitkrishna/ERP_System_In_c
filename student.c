#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addStudent(const struct Student *student) {
    FILE *fp = fopen("students.txt", "a");
    if (fp == NULL) {
        fprintf(stderr, "Error opening student database.\n");
        return 0;
    }

    fprintf(fp, "%d|%s|%s|%s|%s|%s|%s|%d|%.2f|%c|%.2f|%s\n", 
            student->rollNo, student->name, student->phone, student->email, student->address,
            student->parentName, student->faculty, student->batch, student->gpa, 
            student->gender, student->tuitionFee, student->shift);

    fclose(fp);
    return 1; 
}

struct Student *searchStudent(int rollNo) {
    static struct Student student;  // Using 'static' for returning results
    student.rollNo = 0; // Reset as not found

    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token = strtok(line, "|");
        if (atoi(token) == rollNo) {
            student.rollNo = rollNo;
            strcpy(student.name, strtok(NULL, "|"));
            strcpy(student.phone, strtok(NULL, "|"));
            strcpy(student.email, strtok(NULL, "|"));
            strcpy(student.address, strtok(NULL, "|"));
            strcpy(student.parentName, strtok(NULL, "|"));
            strcpy(student.faculty, strtok(NULL, "|"));
            strcpy(student.shift, strtok(NULL, "|"));
            student.gender= *strtok(NULL, "|");
            student.batch = atoi(strtok(NULL, "|"));
            student.gpa = atof(strtok(NULL, "|"));
            student.tuitionFee = atof(strtok(NULL, "|"));
            break;
        }
    }
    fclose(fp);
    return (student.rollNo == 0) ? NULL : &student;
}

int modifyStudent(int rollNo, const struct Student *newInfo) {
    FILE *fpOrig, *fpTemp;
    fpOrig = fopen("students.txt", "a");
    fpTemp = fopen("temp.txt", "a+");

    if (fpOrig == NULL || fpTemp == NULL) {
        fprintf(stderr, "Error opening student database files.\n");
        return 0; 
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fpOrig) != NULL) {
        int currentRollNo = atoi(strtok(line, "|"));
        if (currentRollNo == rollNo) {
            fprintf(fpTemp, "%d|%s|%s|%s|%s|%s|%s|%d|%.2f|%c|%.2f|%s\n", 
                    newInfo->rollNo, newInfo->name, newInfo->phone, newInfo->email, 
                    newInfo->address, newInfo->parentName, newInfo->faculty, 
                    newInfo->batch, newInfo->gpa, newInfo->gender,
                    newInfo->tuitionFee, newInfo->shift);
            found = 1;
        } else {
            fprintf(fpTemp, "%s", line); // Copy unmodified lines
        }
    }
    fclose(fpOrig);
    fclose(fpTemp);

    if (!found) {
        remove("temp.txt"); // Cleanup failed write temp file
        return 0; 
    }

    // Replace original with modified datafile
    remove("students.txt");
    rename("temp.txt", "students.txt");
    return 1; 
}
// This is function for displaying all students
void displayAllStudents() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening student database.\n");
        return;
    }

    printf("\nAll Student Records:\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n"); // Table Border 
    printf("%-4s %-20s %-10s %-20s %-20s %-20s %-15s %-8s %-4s %-5s %-7.2s %-7s\n", 
            "ID", "Name", "Phone", "Email", "Address", "Parent Name", "Faculty", "Batch", "GPA", "Gender", "Fee", "Shift"); // Table Header
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n"); // Table Border 

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token = strtok(line, "|");
        printf("%-4s ", token);  // Roll No
        token = strtok(NULL, "|");
        printf("%-20s ", token);  // Name
        token = strtok(NULL, "|");
        printf("%-10s ", token);  // Phone
        token = strtok(NULL, "|");
        printf("%-20s ", token);  // Email
        token = strtok(NULL, "|");
        printf("%-20s ", token);  // Address
        token = strtok(NULL, "|");
        printf("%-20s ", token);  // Parent Name
        token = strtok(NULL, "|");
        printf("%-15s ", token);  // Faculty
        token = strtok(NULL, "|");
        printf("%-8d ", atoi(token));  // Batch
        token = strtok(NULL, "|");
        printf("%-4.2f ", atof(token));  // GPA
        token = strtok(NULL, "|");
        printf("%-5c ", *token);  // Gender
        token = strtok(NULL, "|");
        printf("%-7.2f ", atof(token));  // Fee
        token = strtok(NULL, "|");
        printf("%-7s\n", token);  // Shift  
    }

    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n"); // Table Border 
    fclose(fp);
}


// Function for taking input from user
struct Student getInput()
{
    struct Student student;

    printf("Enter student roll number: ");
    scanf("%d", &student.rollNo);

    printf("Enter student name: ");
    scanf(" %[^\n]", student.name); // Read full name with spaces

    printf("Enter student phone number: ");
    scanf("%s", student.phone);

    printf("Enter student email: ");
    scanf("%s", student.email);

    printf("Enter student address: ");
    scanf(" %[^\n]", student.address); // Read full address

    printf("Enter student parent's name: ");
    scanf(" %[^\n]", student.parentName);

    printf("Enter student faculty: ");
    scanf("%s", student.faculty);

    printf("Enter student batch: ");
    scanf("%d", &student.batch);

    printf("Enter student GPA (e.g., 3.5): ");
    scanf("%f", &student.gpa);

    printf("Enter student gender (M/F): ");
    scanf(" %c", &student.gender);

    printf("Enter student tuition fee: ");
    scanf("%f", &student.tuitionFee);

    printf("Enter student shift (morning/evening): ");
    scanf("%s", student.shift);

    return student;
}
// Here is function for specific student information on serch by roll number
void displayStudentReport(const struct Student *student) {
    printf("\n+--------------------------------------------------------------------+\n");
    printf("|                             Student Report                           |\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("| Roll No:          %49d  |\n", student->rollNo);
    printf("| Name:             %-50s |\n", student->name);
    printf("| Phone:            %-50s |\n", student->phone);
    printf("| Email:            %-50s |\n", student->email);
    printf("| Address:          %-50s |\n", student->address);
    printf("| Parent Name:      %-50s |\n", student->parentName);
    printf("| Faculty:          %-50s |\n", student->faculty);
    printf("| Shift:            %-50s |\n", student->shift);
    // printf("| Batch:            %d                                             |\n", student->batch);
    // printf("| GPA:              %.2f                                           |\n", student->gpa);
    // printf("| Gender:           %c                                              |\n", student->gender);
    // printf("| Tuition Fee:      %.2f                                           |\n", student->tuitionFee);
    printf("+----------------------------------------------------------------------+\n");
}

