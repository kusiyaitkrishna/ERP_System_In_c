#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "grade.h"
// File constants
const char *GRADES_FILE = "grades.dat";
// Main Grading and Assessment Function
void manageGrading() {
    int choice;
    do {
        printf("Grading and Assessment System\n");
        printf("1. Enter Grades\n");
        printf("2. Modify Grades\n");
        printf("3. Generate Grade Report\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterGrades();
                break;
            case 2:
                modifyGrades();
                break;
            case 3:
                generateGradeReport();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void enterGrades() {
    struct GradeRecord record;
    FILE *file = fopen(GRADES_FILE, "ab+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &record.studentId);
    printf("Enter course code: ");
    scanf("%s", record.courseCode);
    printf("Enter grade: ");
    scanf("%f", &record.grade);

    fwrite(&record, sizeof(struct GradeRecord), 1, file);
    fclose(file);
    printf("Grade entered successfully!\n");
}

void modifyGrades() {
    int id;
    char course[10];
    float newGrade;
    int found = 0;
    FILE *file = fopen(GRADES_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &id);
    printf("Enter course code: ");
    scanf("%s", course);
    printf("Enter new grade: ");
    scanf("%f", &newGrade);

    struct GradeRecord record;
    long int size = sizeof(struct GradeRecord);
    while (fread(&record, size, 1, file)) {
        if (record.studentId == id && strcmp(record.courseCode, course) == 0) {
            found = 1;
            record.grade = newGrade;  // Update grade
            fseek(file, -size, SEEK_CUR);
            fwrite(&record, size, 1, file);
            printf("Grade modified successfully!\n");
            break;
        }
    }

    fclose(file);
    if (!found)
        printf("Grade record not found!\n");
}

void generateGradeReport() {
    FILE *file = fopen(GRADES_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    struct GradeRecord record;
    printf("Grade Reports:\n");
    printf("Student ID\tCourse Code\tGrade\n");
    while (fread(&record, sizeof(struct GradeRecord), 1, file)) {
        printf("%d\t\t%s\t\t%.2f\n", record.studentId, record.courseCode, record.grade);
    }

    fclose(file);
}
