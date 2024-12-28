#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For tolower()

typedef struct {
    char name[50];
    int age;
    float grade;
} Student;

// Custom function for case-insensitive string comparison
int caseInsensitiveCompare(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
        }
        str1++;
        str2++;
    }
    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

void addStudent(Student **students, int *count) {
    printf("Enter student name: ");
    scanf(" %[^\n]", (*students)[*count].name);

    printf("Enter student age: ");
    scanf("%d", &(*students)[*count].age);

    printf("Enter student grade: ");
    scanf("%f", &(*students)[*count].grade);

    (*count)++;
    *students = realloc(*students, (*count + 1) * sizeof(Student));
    if (*students == NULL) {
        printf("Memory reallocation failed.\n");
        exit(1);
    }

    printf("Student added successfully.\n\n");
}

void displayStudents(Student *students, int count) {
    if (count == 0) {
        printf("No students to display.\n\n");
        return;
    }

    printf("\nStudent Records:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Name: %s, Age: %d, Grade: %.2f\n", i + 1, students[i].name, students[i].age, students[i].grade);
    }
    printf("\n");
}

void searchStudent(Student *students, int count) {
    char searchName[50];
    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < count; i++) {
        if (caseInsensitiveCompare(students[i].name, searchName) == 0) { // Case-insensitive comparison
            printf("Student found: Name: %s, Age: %d, Grade: %.2f\n\n", students[i].name, students[i].age, students[i].grade);
            return;
        }
    }
    printf("Student not found.\n\n");
}

void sortStudents(Student *students, int count) {
    if (count < 2) {
        printf("Not enough students to sort.\n\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].grade < students[j + 1].grade) { // Sorting by grade (descending)
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted by grades in descending order.\n\n");
}

void updateStudent(Student *students, int count) {
    char updateName[50];
    printf("Enter name of student to update: ");
    scanf(" %[^\n]", updateName);

    for (int i = 0; i < count; i++) {
        if (caseInsensitiveCompare(students[i].name, updateName) == 0) { // Case-insensitive comparison
            printf("Enter new age: ");
            scanf("%d", &students[i].age);

            printf("Enter new grade: ");
            scanf("%f", &students[i].grade);

            printf("Student record updated successfully.\n\n");
            return;
        }
    }
    printf("Student not found.\n\n");
}

int main() {
    Student *students = calloc(1, sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int count = 0;
    int choice;

    do {
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Sort Students\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                sortStudents(students, count);
                break;
            case 5:
                updateStudent(students, count);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
        }
    } while (choice != 6);

    free(students);
    return 0;
}
