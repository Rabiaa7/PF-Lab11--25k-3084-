#include <stdio.h>

struct Employee {
    int id;
    char name[50];
    char dept[20];
    char desig[20];
    int salary;
    int joinYear;
    int currentYear;
};

int main() {
    struct Employee e[50];
    int n, i, choice;

    printf("Enter no. of employees: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter ID: ");
        scanf("%d", &e[i].id);
        printf("Enter Name: ");
        scanf("%s", e[i].name);
        printf("Enter Department: ");
        scanf("%s", e[i].dept);
        printf("Enter Designation: ");
        scanf("%s", e[i].desig);
        printf("Enter Salary: ");
        scanf("%d", &e[i].salary);
        printf("Enter Joining Year: ");
        scanf("%d", &e[i].joinYear);
        printf("Enter Current Year: ");
        scanf("%d", &e[i].currentYear);
    }

    while (1) {
        printf("\n1. Display all\n2. Search by Department\n3. Search by Designation\n4. Experience>3 years\n5. Salary Stats by Dept\n0. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 1)
            for (i = 0; i < n; i++)
                printf("%d %s %s %s %d Exp:%d\n",
                       e[i].id, e[i].name, e[i].dept, e[i].desig, e[i].salary,
                       e[i].currentYear - e[i].joinYear);

        else if (choice == 2) {
            char d[20];
            printf("Enter Department: ");
            scanf("%s", d);

            for (i = 0; i < n; i++) {
                int same = 1, k = 0;
                while (d[k] != '\0' && e[i].dept[k] != '\0') {
                    if (d[k] != e[i].dept[k]) { same = 0; break; }
                    k++;
                }
                if (same)
                    printf("%s %s %d\n", e[i].name, e[i].desig, e[i].salary);
            }
        }

        else if (choice == 3) {
            char d[20];
            printf("Enter Designation: ");
            scanf("%s", d);

            for (i = 0; i < n; i++) {
                int same = 1, k = 0;
                while (d[k] != '\0' && e[i].desig[k] != '\0') {
                    if (d[k] != e[i].desig[k]) { same = 0; break; }
                    k++;
                }
                if (same)
                    printf("%s %s %d\n", e[i].name, e[i].dept, e[i].salary);
            }
        }

        else if (choice == 4)
            for (i = 0; i < n; i++)
                if (e[i].currentYear - e[i].joinYear > 3)
                    printf("%s Eligible for promotion.\n", e[i].name);

        else if (choice == 5) {
            char d[20];
            printf("Enter Department: ");
            scanf("%s", d);
            int total = 0, count = 0;

            for (i = 0; i < n; i++) {
                int same = 1, k = 0;
                while (d[k] != '\0' && e[i].dept[k] != '\0') {
                    if (d[k] != e[i].dept[k]) { same = 0; break; }
                    k++;
                }
                if (same) {
                    total += e[i].salary;
                    count++;
                }
            }
            if (count > 0)
                printf("Average Salary = %d\n", total / count);
        }
    }
    return 0;
}
