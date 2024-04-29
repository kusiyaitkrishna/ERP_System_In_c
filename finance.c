#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "finance.h"
const char *FINANCIAL_FILE = "financials.dat";
// Main Financial Management Function
void manageFinances() {
    int choice;
    do {
        printf("Financial Management System\n");
        printf("1. Process Tuition Fee\n");
        printf("2. Award Scholarship\n");
        printf("3. Generate Financial Report\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                processTuitionFee();
                break;
            case 2:
                awardScholarship();
                break;
            case 3:
                generateFinancialReport();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

void processTuitionFee() {
    struct FinancialRecord record;
    FILE *file = fopen(FINANCIAL_FILE, "ab+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &record.studentId);
    printf("Enter tuition fees: ");
    scanf("%f", &record.tuitionFees);
    record.scholarshipAmount = 0;  // Default no scholarship

    fwrite(&record, sizeof(struct FinancialRecord), 1, file);
    fclose(file);
    printf("Tuition fee processed successfully!\n");
}

void awardScholarship() {
    int id;
    float amount;
    int found = 0;
    FILE *file = fopen(FINANCIAL_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter student ID for scholarship: ");
    scanf("%d", &id);
    printf("Enter scholarship amount: ");
    scanf("%f", &amount);

    struct FinancialRecord record;
    long int size = sizeof(struct FinancialRecord);
    while (fread(&record, size, 1, file)) {
        if (record.studentId == id) {
            found = 1;
            record.scholarshipAmount += amount;  // Add scholarship
            fseek(file, -size, SEEK_CUR);
            fwrite(&record, size, 1, file);
            printf("Scholarship awarded successfully!\n");
            break;
        }
    }

    fclose(file);
    if (!found)
        printf("Student not found!\n");
}

void generateFinancialReport() {
    FILE *file = fopen(FINANCIAL_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    struct FinancialRecord record;
    printf("Financial Records:\n");
    printf("Student ID\tTuition Fees\tScholarship Amount\n");
    while (fread(&record, sizeof(struct FinancialRecord), 1, file)) {
        printf("%d\t\t$%.2f\t\t$%.2f\n", record.studentId, record.tuitionFees, record.scholarshipAmount);
    }

    fclose(file);
}