#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNo;
    int marks[3];
    float percentage;
    char grade[3]; 
};

struct Student calculate(struct Student s) {
    int total = s.marks[0] + s.marks[1] + s.marks[2];
    s.percentage = total / 3.0;

    if (s.percentage >= 90 && s.percentage <= 100)
        strcpy(s.grade, "A+");
    else if (s.percentage >= 80)
        strcpy(s.grade, "A");
    else if (s.percentage >= 70)
        strcpy(s.grade, "B+");
    else if (s.percentage >= 60)
        strcpy(s.grade, "B");
    else if (s.percentage >= 50)
        strcpy(s.grade, "C");
    else
        strcpy(s.grade, "F");

    return s;
}

int validateMark(int mark) {
    return (mark >= 0 && mark <= 100);
}

void displayStudent(struct Student s) {
    printf("Name: %s\n", s.name);
    printf("Roll No: %d\n", s.rollNo);
    printf("Marks: %d %d %d\n", s.marks[0], s.marks[1], s.marks[2]);
    printf("Percentage: %.2f\n", s.percentage);
    printf("Grade: %s\n", s.grade);
    printf("-------------------------\n");
}

void searchByGrade(struct Student students[], int n, char grade[]) {
    printf("Students with grade %s:\n", grade);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].grade, grade) == 0) {
            displayStudent(students[i]);
            found = 1;
        }
    }
    if (!found) printf("No students found with grade %s\n", grade);
}

void searchByRoll(struct Student students[], int n, int rollNo) {
    for (int i = 0; i < n; i++) {
        if (students[i].rollNo == rollNo) {
            displayStudent(students[i]);
            return;
        }
    }
    printf("No student found with Roll No %d\n", rollNo);
}

void searchByName(struct Student students[], int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].name, name) == 0) {
            displayStudent(students[i]);
            return;
        }
    }
    printf("No student found with name %s\n", name);
}

float classAverage(struct Student students[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++)
        total += students[i].percentage;
    return total / n;
}

void displayAboveBelowAverage(struct Student students[], int n) {
    float avg = classAverage(students, n);
    printf("Class Average: %.2f\n", avg);

    printf("\nStudents above average:\n");
    for (int i = 0; i < n; i++)
        if (students[i].percentage > avg)
            displayStudent(students[i]);

    printf("\nStudents below average:\n");
    for (int i = 0; i < n; i++)
        if (students[i].percentage < avg)
            displayStudent(students[i]);
}

void sortByPercentage(struct Student students[], int n) {
    struct Student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].percentage < students[j].percentage) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void displayWithRank(struct Student students[], int n) {
    sortByPercentage(students, n);
    printf("\nStudents Ranked by Percentage:\n");
    for (int i = 0; i < n; i++) {
        printf("Rank %d:\n", i + 1);
        displayStudent(students[i]);
    }
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Student students[n];  

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);
        printf("Roll No: ");
        scanf("%d", &students[i].rollNo);

        for (int j = 0; j < 3; j++) {
            do {
                printf("Enter marks for subject %d: ", j + 1);
                scanf("%d", &students[i].marks[j]);
                if (!validateMark(students[i].marks[j]))
                    printf("Invalid marks! Please enter between 0-100.\n");
            } while (!validateMark(students[i].marks[j]));
        }

        students[i] = calculate(students[i]);  
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Search by Grade\n");
        printf("2. Search by Roll Number\n");
        printf("3. Search by Name\n");
        printf("4. Display Students Above/Below Average\n");
        printf("5. Display Students with Rank\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char grade[3];
            printf("Enter grade to search: ");
            scanf(" %2s", grade);
            searchByGrade(students, n, grade);
        } else if (choice == 2) {
            int roll;
            printf("Enter Roll Number to search: ");
            scanf("%d", &roll);
            searchByRoll(students, n, roll);
        } else if (choice == 3) {
            char name[50];
            printf("Enter Name to search: ");
            scanf(" %[^\n]", name);
            searchByName(students, n, name);
        } else if (choice == 4) {
            displayAboveBelowAverage(students, n);
        } else if (choice == 5) {
            displayWithRank(students, n);
        }
    } while (choice != 6);

    return 0;
}

