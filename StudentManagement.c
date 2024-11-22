#include <stdio.h>
#include <string.h>

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

static int delete_student() {
    FILE *pf = fopen("student.txt", "r+");
    if (pf == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    char name[50];
    printf("Enter name to delete:\n");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        fclose(pf);
        return 1;
    }
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    char line[100];
    long pos = 0;
    int found = 0;

    while (fgets(line, sizeof(line), pf) != NULL) {
        if (strstr(line, name) != NULL) {
            found = 1;
            break;
        }
        pos = ftell(pf);
    }

    if (found) {
        fseek(pf, pos, SEEK_SET);
        fprintf(pf, "\n");
        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found!\n");
    }

    fclose(pf);
    return 0;
}

static int add_grade() {
    FILE *pf = fopen("student.txt", "r+");
    if (pf == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    char name[50];
    printf("Enter student name:\n");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        fclose(pf);
        return 1;
    }
    name[strcspn(name, "\n")] = '\0';

    char line[100];
    while (fgets(line, sizeof(line), pf) != NULL) {
        if (strstr(line, name) != NULL) {
            int age;
            sscanf(line, "%[^,], %d", name, &age);
            printf("Enter grade (0-100):\n");
            int grade;
            if (scanf("%d", &grade) != 1) {
                fprintf(stderr, "Invalid input for grade\n");
                fclose(pf);
                return 1;
            }
            fprintf(pf, "%s, %d, Grade: %d\n", name, age, grade);
            break;
        }
    }
    fclose(pf);
    return 0;
}

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
    name[strcspn(name, "\n")] = '\0';

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
    return 0;
}

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
    name[strcspn(name, "\n")] = '\0';

    char line[100];
    while (fgets(line, sizeof(line), pF) != NULL) {
        if (strstr(line, name) != NULL) {
            printf("%s", line);
            fclose(pF);
            return 0;
        }
    }
    printf("Student not found!\n");
    fclose(pF);
    return 0;
}

int main(void) {
    int choice;

    while (1) {
        printf("\nMenu:\n"
               "1. Add Student\n"
               "2. Show All Students\n"
               "3. Search Student\n"
               "4. Delete Student\n"
	       "5. Delete All Students\n"
	       "6. Exit\n");
        	
	printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            break;
        }

        getchar(); // Flush leftover newline

        switch (choice) {
            case 1: add_student(); break;
            case 2: show_all_students(); break;
            case 3: search_student(); break;
            case 4: delete_student(); break;
            case 5: delete_all_students(); break;
	    case 6: return 0;
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}
