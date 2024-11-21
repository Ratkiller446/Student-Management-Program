#include <stdio.h>
#include <string.h>

static int delete_all_students(void)
{
    FILE *pF = fopen("student.txt", "w");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    } else {
        fclose(pF);
    }
    return 0;
}

static int delete_student(void)
{
    FILE *pf = fopen("student.txt", "r+");
    if (pf == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    char name[50];
    printf("Enter name to delete:\n");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    char line[100];
    long pos = ftell(pf);
    char rest[1000];
    int found = 0;

    while (fgets(line, sizeof(line), pf) != NULL) {
        if (strstr(line, name) != NULL) {
            found = 1;
            break;
        }
        pos = ftell(pf);
    }

    if (found) {
        // Read the rest of the file
        fgets(rest, sizeof(rest), pf);
        // Go back to where we found the name
        fseek(pf, pos, SEEK_SET);
        // Write the rest of the file over it
        fputs(rest, pf);
        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found!\n");
    }
    fclose(pf);
    return 0;
}

static int add_grade(void)
{
    FILE *pf = fopen("student.txt", "r+");
    if (pf == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    char name[50];
    printf("Enter student name:\n");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    char line[100];
    while (fgets(line, sizeof(line), pf) != NULL) {
        if (strstr(line, name) != NULL) {
            fseek(pf, ftell(pf) - strlen(line), SEEK_SET);
            int age;
            sscanf(line, "%[^,], %d", name, &age);
            printf("Enter grade (0-100):\n");
            int grade;
            scanf("%d", &grade);
            fprintf(pf, "%s, %d, Grade: %d\n", name, age, grade);
            break;
        }
    }
    fclose(pf);
    return 0;
}

static int add_student(void)
{
    FILE *pF = fopen("student.txt", "a");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    printf("Add a Student:\n");
    char name[50];
    int age;
    printf("Enter name:\n");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    printf("Enter age:\n");
    scanf("%d", &age);
    printf("Enter grade (0-10):\n");
    int grade;
    scanf("%d", &grade);
    fprintf(pF, "%s, %d, Grade: %d\n", name, age, grade);
    fclose(pF);
    return 0;
}

static int show_all_students(void)
{
    FILE *pF = fopen("student.txt", "r");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    } else {
        char line[100];
        while (fgets(line, sizeof(line), pF) != NULL) {
            printf("%s", line);
        }
        fclose(pF);
    }
    return 0;
}

static int search_student(void)
{
    FILE *pF = fopen("student.txt", "r");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    } else {
        char name[50];
        printf("Enter name to search:\n");
        fgets(name, sizeof(name), stdin);
        name[strlen(name) - 1] = '\0';
        char line[10];
        while (fgets(line, sizeof(line), pF) != NULL) {
            if (strstr(line, name) != NULL) {
                printf("%s", line);
                break;
            }
        }
        fclose(pF);
    }
    return 0;
}

static int edit_student(void)
{
    FILE *pf = fopen("student.txt", "r+");
    if (pf == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    char name[50];
    printf("Enter name to edit:\n");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    char line[10];
    while (fgets(line, sizeof(line), pf) != NULL) {
        if (strstr(line, name) != NULL) {
            fseek(pf, ftell(pf) - strlen(line), SEEK_SET);
            printf("Enter new name:\n");
            fgets(name, sizeof(name), stdin);
            name[strlen(name) - 1] = '\0';
            printf("Enter new age:\n");
            int age;
            scanf("%d", &age);
            printf("Enter new grade (0-10):\n");
            int grade;
            scanf("%d", &grade);
            fprintf(pf, "%s, %d, Grade: %d\n", name, age, grade);
            break;
        }
    }
    fclose(pf);
    return 0;
}

int main(void)
{
    int choice = 0;

    printf("\n"
           "Student Management System  Copyright (C) 2024\n"
           "===========================================\n"
           "This program is free software: you can redistribute it and/or modify\n"
           "it under the terms of the GNU General Public License as published by\n"
           "the Free Software Foundation, either version 3 of the License, or\n"
           "(at your option) any later version.\n"
           "\n"
           "This program is distributed in the hope that it will be useful,\n"
           "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
           "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
           "GNU General Public License for more details.\n"
           "\n"
           "You should have received a copy of the GNU General Public License\n"
           "along with this program. If not, see <https://www.gnu.org/licenses/>.\n"
           "===========================================\n\n");

    printf("Q to quit\n"
           "============================================\n"
           "Welcome to the Student Management System\n"
           "=========================================\n"
           "[1] Add\n[2] Show all\n[3] Search\n[4] Edit\n[5] Delete\n"
           "[6] Delete All Students\n[7] Add Grade\n[8] Exit\n"
           "=========================================\n");

    if (choice == 8) {
        printf("Goodbye\n");
        return 0;
    }

    scanf("%d", &choice);
    while (choice != 8) {
        switch (choice) {
        case 1: add_student(); break;
        case 2: show_all_students(); break;
        case 3: search_student(); break;
        case 4: edit_student(); break;
        case 5: delete_student(); break;
        case 6: delete_all_students(); break;
        case 7: add_grade(); break;
        default: printf("Invalid choice\n");
        }
        printf("Enter choice (1-8): ");
        scanf("%d", &choice);
    }

    printf("Goodbye\n");
    return 0;