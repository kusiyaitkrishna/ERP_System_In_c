#ifndef FINANCE_H
#define FINANCE_H

struct FinancialRecord {
    int studentId;
    float tuitionFees;
    float scholarshipAmount;
};
// Function Prototypes
void processTuitionFee();
void awardScholarship();
void generateFinancialReport();
void manageFinances();

#endif 
