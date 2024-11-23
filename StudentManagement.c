#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to delete all students
static int delete_all_students() {
    FILE *pF = fopen("student.txt", "w");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    fclose(pF);
    printf("All students deleted successfully!\n");
    return 0;
}

// Function to delete a specific student
static int delete_student() {
    FILE *pF = fopen("student.txt", "r");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    FILE *tempF = fopen("temp.txt", "w");
    if (tempF == NULL) {
        fprintf(stderr, "Error opening temporary file\n");
        fclose(pF);
        return 1;
    }

    char name[50];
    printf("Enter name to delete:\n");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        fclose(pF);
        fclose(tempF);
        return 1;
    }
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), pF) != NULL) {
        if (strstr(line, name) != NULL) {
            found = 1;
        } else {
            fputs(line, tempF);
        }
    }

    fclose(pF);
    fclose(tempF);

    if (found) {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        printf("Student deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("Student not found!\n");
    }

    return 0;
}

// Function to add a student
static int add_student() {
    FILE *pF = fopen("student.txt", "a");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    char name[50];
    int age, grade;

    printf("Enter name:\n");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        fclose(pF);
        return 1;
    }
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter age:\n");
    if (scanf("%d", &age) != 1) {
        fprintf(stderr, "Invalid input for age\n");
        fclose(pF);
        return 1;
    }

    printf("Enter grade (0-100):\n");
    if (scanf("%d", &grade) != 1) {
        fprintf(stderr, "Invalid input for grade\n");
        fclose(pF);
        return 1;
    }

    fprintf(pF, "%s, %d, Grade: %d\n", name, age, grade);
    fclose(pF);

    getchar(); // Flush leftover newline
    printf("Student added successfully!\n");
    return 0;
}

// Function to show all students
static int show_all_students() {
    FILE *pF = fopen("student.txt", "r");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), pF) != NULL) {
        printf("%s", line);
    }
    fclose(pF);
    return 0;
}

// Function to search for a student
static int search_student() {
    FILE *pF = fopen("student.txt", "r");
    if (pF == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }

    char name[50];
    printf("Enter name to search:\n");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        fclose(pF);
        return 1;
    }
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), pF) != NULL) {
        if (strstr(line, name) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    fclose(pF);
    return 0;
}

// Main function
int main(void) {
    int choice;

    while (1) {
        printf("\nMenu:\n"
               "1. Add Student\n"
               "2. Show all Students\n"
               "3. Search a Student\n"
               "4. Delete a Student\n"
               "5. Delete all Students\n"
               "6. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            break;
        }

        getchar(); // Flush leftover newline

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                show_all_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                delete_all_students();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
