#ifndef GRADE_H
#define GRADE_H

struct GradeRecord {
    int studentId;
    char courseCode[10];
    float grade;
};
// Function Prototypes
void enterGrades();
void modifyGrades();
void generateGradeReport();
void manageGrading();
#endif 
