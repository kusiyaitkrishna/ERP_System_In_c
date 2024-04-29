#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_ADDRESS_LEN 100
#define MAX_FACULTY_LEN 20 

struct Student {
    int rollNo;
    char name[MAX_NAME_LEN];
    char phone[15];
    char email[50];
    char address[MAX_ADDRESS_LEN];
    char parentName[MAX_NAME_LEN];
    char faculty[MAX_FACULTY_LEN];
    int batch;
    float gpa;
    char gender;
    float tuitionFee;
    char shift[10]; // "morning" or "evening"
};

// Function prototypes
int addStudent(const struct Student *student);
struct Student *searchStudent(int rollNo); 
int modifyStudent(int rollNo, const struct Student *newInfo);
int deleteStudent(int rollNo);
void displayAllStudents();
struct Student getInput();
void displayStudentReport(const struct Student *student);

#endif 
