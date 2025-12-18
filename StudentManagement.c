#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_NAME_LEN 100
#define MAX_PHONE_LEN 20
#define MAX_EMAIL_LEN 100
#define MAX_ADDRESS_LEN 200
#define MAX_SUBJECT_LEN 50
#define MAX_CLASS_LEN 20
#define MAX_DATE_LEN 12
#define MAX_SUBJECTS 10
#define MAX_GRADES 50

// Data structures
typedef struct {
    int student_id;
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    int age;
    char date_of_birth[MAX_DATE_LEN];
    char gender;
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
    char address[MAX_ADDRESS_LEN];
    char emergency_contact[MAX_PHONE_LEN];
    char class_section[MAX_CLASS_LEN];
    char enrollment_date[MAX_DATE_LEN];
    int is_active;
} Student;

typedef struct {
    int teacher_id;
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    char subject[MAX_SUBJECT_LEN];
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
    char hire_date[MAX_DATE_LEN];
    int is_active;
} Teacher;

typedef struct {
    int grade_id;
    int student_id;
    char subject[MAX_SUBJECT_LEN];
    char assignment_type[50]; // "Assignment", "Quiz", "Exam", "Project"
    char assignment_name[100];
    float score;
    float max_score;
    char date[MAX_DATE_LEN];
} Grade;

typedef struct {
    int attendance_id;
    int student_id;
    char date[MAX_DATE_LEN];
    char status; // 'P' = Present, 'A' = Absent, 'T' = Tardy, 'E' = Excused
    char reason[100];
} Attendance;

typedef struct {
    char name[MAX_CLASS_LEN];
    char teacher_name[MAX_NAME_LEN];
    int student_count;
    char schedule[100];
} ClassSection;

// Global variables
static int next_student_id = 1001;
static int next_teacher_id = 2001;
static int next_grade_id = 3001;
static int next_attendance_id = 4001;

// Utility functions
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%02d/%02d/%04d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validate_email(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return (at != NULL && dot != NULL && at < dot && at > email && dot < email + strlen(email) - 1);
}

int validate_phone(const char *phone) {
    for (int i = 0; phone[i]; i++) {
        if (!isdigit(phone[i]) && phone[i] != '-' && phone[i] != '(' && phone[i] != ')' && phone[i] != ' ') {
            return 0;
        }
    }
    return strlen(phone) >= 10;
}

// File I/O functions
void load_next_ids() {
    FILE *file = fopen("system_config.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d %d %d %d", &next_student_id, &next_teacher_id, &next_grade_id, &next_attendance_id);
        fclose(file);
    }
}

void save_next_ids() {
    FILE *file = fopen("system_config.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d %d %d %d", next_student_id, next_teacher_id, next_grade_id, next_attendance_id);
        fclose(file);
    }
}

// Student Management Functions
int add_student() {
    Student student;
    char input[100];
    
    printf("\n=== Add New Student ===\n");
    
    // Auto-generate student ID
    student.student_id = next_student_id++;
    printf("Student ID: %d\n", student.student_id);
    
    // Get student information
    printf("Enter first name: ");
    if (fgets(student.first_name, sizeof(student.first_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.first_name[strcspn(student.first_name, "\n")] = '\0';
    
    printf("Enter last name: ");
    if (fgets(student.last_name, sizeof(student.last_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.last_name[strcspn(student.last_name, "\n")] = '\0';
    
    printf("Enter age: ");
    if (scanf("%d", &student.age) != 1 || student.age < 5 || student.age > 100) {
        fprintf(stderr, "Invalid age\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    printf("Enter date of birth (MM/DD/YYYY): ");
    if (fgets(student.date_of_birth, sizeof(student.date_of_birth), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.date_of_birth[strcspn(student.date_of_birth, "\n")] = '\0';
    
    printf("Enter gender (M/F): ");
    scanf(" %c", &student.gender);
    student.gender = toupper(student.gender);
    if (student.gender != 'M' && student.gender != 'F') {
        fprintf(stderr, "Invalid gender\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    printf("Enter phone number: ");
    if (fgets(student.phone, sizeof(student.phone), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.phone[strcspn(student.phone, "\n")] = '\0';
    if (!validate_phone(student.phone)) {
        fprintf(stderr, "Invalid phone number\n");
        return 1;
    }
    
    printf("Enter email: ");
    if (fgets(student.email, sizeof(student.email), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.email[strcspn(student.email, "\n")] = '\0';
    if (!validate_email(student.email)) {
        fprintf(stderr, "Invalid email address\n");
        return 1;
    }
    
    printf("Enter address: ");
    if (fgets(student.address, sizeof(student.address), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.address[strcspn(student.address, "\n")] = '\0';
    
    printf("Enter emergency contact: ");
    if (fgets(student.emergency_contact, sizeof(student.emergency_contact), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.emergency_contact[strcspn(student.emergency_contact, "\n")] = '\0';
    
    printf("Enter class/section: ");
    if (fgets(student.class_section, sizeof(student.class_section), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    student.class_section[strcspn(student.class_section, "\n")] = '\0';
    
    // Set enrollment date to current date
    get_current_date(student.enrollment_date);
    student.is_active = 1;
    
    // Save to file
    FILE *file = fopen("students.dat", "ab");
    if (file == NULL) {
        fprintf(stderr, "Error opening students file\n");
        return 1;
    }
    
    if (fwrite(&student, sizeof(Student), 1, file) != 1) {
        fprintf(stderr, "Error writing student data\n");
        fclose(file);
        return 1;
    }
    
    fclose(file);
    save_next_ids();
    
    printf("Student added successfully! ID: %d\n", student.student_id);
    return 0;
}

int show_all_students() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No student records found.\n");
        return 1;
    }
    
    Student student;
    int count = 0;
    
    printf("\n=== All Students ===\n");
    printf("%-6s %-15s %-15s %-4s %-12s %-15s %-15s\n", 
           "ID", "First Name", "Last Name", "Age", "Class", "Phone", "Email");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.is_active) {
            printf("%-6d %-15s %-15s %-4d %-12s %-15s %-15s\n",
                   student.student_id, student.first_name, student.last_name,
                   student.age, student.class_section, student.phone, student.email);
            count++;
        }
    }
    
    fclose(file);
    printf("\nTotal active students: %d\n", count);
    return 0;
}

int search_student() {
    int choice, student_id;
    char search_term[100];
    
    printf("\n=== Search Student ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Class\n");
    printf("Enter choice: ");
    
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No student records found.\n");
        return 1;
    }
    
    Student student;
    int found = 0;
    
    switch (choice) {
        case 1:
            printf("Enter student ID: ");
            if (scanf("%d", &student_id) != 1) {
                fprintf(stderr, "Invalid ID\n");
                clear_input_buffer();
                fclose(file);
                return 1;
            }
            clear_input_buffer();
            
            while (fread(&student, sizeof(Student), 1, file) == 1) {
                if (student.is_active && student.student_id == student_id) {
                    printf("\n=== Student Found ===\n");
                    printf("ID: %d\n", student.student_id);
                    printf("Name: %s %s\n", student.first_name, student.last_name);
                    printf("Age: %d\n", student.age);
                    printf("DOB: %s\n", student.date_of_birth);
                    printf("Gender: %c\n", student.gender);
                    printf("Phone: %s\n", student.phone);
                    printf("Email: %s\n", student.email);
                    printf("Address: %s\n", student.address);
                    printf("Emergency Contact: %s\n", student.emergency_contact);
                    printf("Class: %s\n", student.class_section);
                    printf("Enrollment Date: %s\n", student.enrollment_date);
                    found = 1;
                    break;
                }
            }
            break;
            
        case 2:
            printf("Enter name to search: ");
            if (fgets(search_term, sizeof(search_term), stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                fclose(file);
                return 1;
            }
            search_term[strcspn(search_term, "\n")] = '\0';
            
            printf("\n=== Search Results ===\n");
            while (fread(&student, sizeof(Student), 1, file) == 1) {
                if (student.is_active && 
                    (strstr(student.first_name, search_term) != NULL || 
                     strstr(student.last_name, search_term) != NULL)) {
                    printf("ID: %d, Name: %s %s, Class: %s, Phone: %s\n",
                           student.student_id, student.first_name, student.last_name,
                           student.class_section, student.phone);
                    found = 1;
                }
            }
            break;
            
        case 3:
            printf("Enter class to search: ");
            if (fgets(search_term, sizeof(search_term), stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                fclose(file);
                return 1;
            }
            search_term[strcspn(search_term, "\n")] = '\0';
            
            printf("\n=== Students in Class %s ===\n", search_term);
            while (fread(&student, sizeof(Student), 1, file) == 1) {
                if (student.is_active && strcmp(student.class_section, search_term) == 0) {
                    printf("ID: %d, Name: %s %s, Age: %d, Phone: %s\n",
                           student.student_id, student.first_name, student.last_name,
                           student.age, student.phone);
                    found = 1;
                }
            }
            break;
            
        default:
            printf("Invalid choice\n");
            fclose(file);
            return 1;
    }
    
    if (!found) {
        printf("No matching students found.\n");
    }
    
    fclose(file);
    return 0;
}

int delete_student() {
    int student_id;
    printf("Enter student ID to delete: ");
    if (scanf("%d", &student_id) != 1) {
        fprintf(stderr, "Invalid ID\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    FILE *file = fopen("students.dat", "r+b");
    if (file == NULL) {
        printf("No student records found.\n");
        return 1;
    }
    
    Student student;
    int found = 0;
    long pos;
    
    while ((pos = ftell(file)) != -1 && fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.is_active && student.student_id == student_id) {
            printf("Found student: %s %s\n", student.first_name, student.last_name);
            printf("Are you sure you want to delete this student? (y/n): ");
            
            char confirm;
            scanf(" %c", &confirm);
            clear_input_buffer();
            
            if (confirm == 'y' || confirm == 'Y') {
                student.is_active = 0; // Mark as inactive instead of deleting
                fseek(file, pos, SEEK_SET);
                fwrite(&student, sizeof(Student), 1, file);
                printf("Student deleted successfully!\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", student_id);
    }
    
    fclose(file);
    return 0;
}

int delete_all_students() {
    printf("Are you sure you want to delete ALL students? This cannot be undone! (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("Operation cancelled.\n");
        return 0;
    }
    
    FILE *file = fopen("students.dat", "w");
    if (file == NULL) {
        fprintf(stderr, "Error accessing student file\n");
        return 1;
    }
    
    fclose(file);
    printf("All students deleted successfully!\n");
    return 0;
}

// Teacher Management Functions
int add_teacher() {
    Teacher teacher;
    
    printf("\n=== Add New Teacher ===\n");
    
    teacher.teacher_id = next_teacher_id++;
    printf("Teacher ID: %d\n", teacher.teacher_id);
    
    printf("Enter first name: ");
    if (fgets(teacher.first_name, sizeof(teacher.first_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    teacher.first_name[strcspn(teacher.first_name, "\n")] = '\0';
    
    printf("Enter last name: ");
    if (fgets(teacher.last_name, sizeof(teacher.last_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    teacher.last_name[strcspn(teacher.last_name, "\n")] = '\0';
    
    printf("Enter subject: ");
    if (fgets(teacher.subject, sizeof(teacher.subject), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    teacher.subject[strcspn(teacher.subject, "\n")] = '\0';
    
    printf("Enter phone: ");
    if (fgets(teacher.phone, sizeof(teacher.phone), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    teacher.phone[strcspn(teacher.phone, "\n")] = '\0';
    
    printf("Enter email: ");
    if (fgets(teacher.email, sizeof(teacher.email), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    teacher.email[strcspn(teacher.email, "\n")] = '\0';
    
    get_current_date(teacher.hire_date);
    teacher.is_active = 1;
    
    FILE *file = fopen("teachers.dat", "ab");
    if (file == NULL) {
        fprintf(stderr, "Error opening teachers file\n");
        return 1;
    }
    
    fwrite(&teacher, sizeof(Teacher), 1, file);
    fclose(file);
    save_next_ids();
    
    printf("Teacher added successfully! ID: %d\n", teacher.teacher_id);
    return 0;
}

int show_all_teachers() {
    FILE *file = fopen("teachers.dat", "rb");
    if (file == NULL) {
        printf("No teacher records found.\n");
        return 1;
    }
    
    Teacher teacher;
    int count = 0;
    
    printf("\n=== All Teachers ===\n");
    printf("%-6s %-15s %-15s %-20s %-15s %-20s\n", 
           "ID", "First Name", "Last Name", "Subject", "Phone", "Email");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fread(&teacher, sizeof(Teacher), 1, file) == 1) {
        if (teacher.is_active) {
            printf("%-6d %-15s %-15s %-20s %-15s %-20s\n",
                   teacher.teacher_id, teacher.first_name, teacher.last_name,
                   teacher.subject, teacher.phone, teacher.email);
            count++;
        }
    }
    
    fclose(file);
    printf("\nTotal active teachers: %d\n", count);
    return 0;
}

// Grade Management Functions
int add_grade() {
    Grade grade;
    int student_id;
    
    printf("\n=== Add Grade ===\n");
    printf("Enter student ID: ");
    if (scanf("%d", &student_id) != 1) {
        fprintf(stderr, "Invalid student ID\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    // Verify student exists
    FILE *student_file = fopen("students.dat", "rb");
    if (student_file == NULL) {
        printf("No student records found.\n");
        return 1;
    }
    
    Student student;
    int student_found = 0;
    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if (student.is_active && student.student_id == student_id) {
            student_found = 1;
            printf("Student: %s %s\n", student.first_name, student.last_name);
            break;
        }
    }
    fclose(student_file);
    
    if (!student_found) {
        printf("Student with ID %d not found.\n", student_id);
        return 1;
    }
    
    grade.grade_id = next_grade_id++;
    grade.student_id = student_id;
    
    printf("Enter subject: ");
    if (fgets(grade.subject, sizeof(grade.subject), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    grade.subject[strcspn(grade.subject, "\n")] = '\0';
    
    printf("Enter assignment type (Assignment/Quiz/Exam/Project): ");
    if (fgets(grade.assignment_type, sizeof(grade.assignment_type), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    grade.assignment_type[strcspn(grade.assignment_type, "\n")] = '\0';
    
    printf("Enter assignment name: ");
    if (fgets(grade.assignment_name, sizeof(grade.assignment_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    grade.assignment_name[strcspn(grade.assignment_name, "\n")] = '\0';
    
    printf("Enter score: ");
    if (scanf("%f", &grade.score) != 1) {
        fprintf(stderr, "Invalid score\n");
        clear_input_buffer();
        return 1;
    }
    
    printf("Enter maximum score: ");
    if (scanf("%f", &grade.max_score) != 1 || grade.max_score <= 0) {
        fprintf(stderr, "Invalid maximum score\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    get_current_date(grade.date);
    
    FILE *file = fopen("grades.dat", "ab");
    if (file == NULL) {
        fprintf(stderr, "Error opening grades file\n");
        return 1;
    }
    
    fwrite(&grade, sizeof(Grade), 1, file);
    fclose(file);
    save_next_ids();
    
    printf("Grade added successfully! Score: %.2f/%.2f (%.1f%%)\n", 
           grade.score, grade.max_score, (grade.score/grade.max_score)*100);
    return 0;
}

int view_student_grades() {
    int student_id;
    printf("Enter student ID: ");
    if (scanf("%d", &student_id) != 1) {
        fprintf(stderr, "Invalid student ID\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    FILE *file = fopen("grades.dat", "rb");
    if (file == NULL) {
        printf("No grade records found.\n");
        return 1;
    }
    
    Grade grade;
    int found = 0;
    float total_percentage = 0;
    int count = 0;
    
    printf("\n=== Grades for Student ID %d ===\n", student_id);
    printf("%-15s %-15s %-25s %-10s %-10s %-12s\n", 
           "Subject", "Type", "Assignment", "Score", "Max", "Percentage");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fread(&grade, sizeof(Grade), 1, file) == 1) {
        if (grade.student_id == student_id) {
            float percentage = (grade.score / grade.max_score) * 100;
            printf("%-15s %-15s %-25s %-10.2f %-10.2f %-12.1f%%\n",
                   grade.subject, grade.assignment_type, grade.assignment_name,
                   grade.score, grade.max_score, percentage);
            total_percentage += percentage;
            count++;
            found = 1;
        }
    }
    
    if (found) {
        printf("\nOverall Average: %.1f%%\n", total_percentage / count);
    } else {
        printf("No grades found for this student.\n");
    }
    
    fclose(file);
    return 0;
}

// Attendance Management Functions
int mark_attendance() {
    Attendance attendance;
    int student_id;
    
    printf("\n=== Mark Attendance ===\n");
    printf("Enter student ID: ");
    if (scanf("%d", &student_id) != 1) {
        fprintf(stderr, "Invalid student ID\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    attendance.attendance_id = next_attendance_id++;
    attendance.student_id = student_id;
    
    get_current_date(attendance.date);
    printf("Date: %s\n", attendance.date);
    
    printf("Enter status (P=Present, A=Absent, T=Tardy, E=Excused): ");
    scanf(" %c", &attendance.status);
    attendance.status = toupper(attendance.status);
    clear_input_buffer();
    
    if (attendance.status != 'P' && attendance.status != 'A' && 
        attendance.status != 'T' && attendance.status != 'E') {
        fprintf(stderr, "Invalid status\n");
        return 1;
    }
    
    printf("Enter reason (optional): ");
    if (fgets(attendance.reason, sizeof(attendance.reason), stdin) == NULL) {
        strcpy(attendance.reason, "");
    } else {
        attendance.reason[strcspn(attendance.reason, "\n")] = '\0';
    }
    
    FILE *file = fopen("attendance.dat", "ab");
    if (file == NULL) {
        fprintf(stderr, "Error opening attendance file\n");
        return 1;
    }
    
    fwrite(&attendance, sizeof(Attendance), 1, file);
    fclose(file);
    save_next_ids();
    
    printf("Attendance marked successfully!\n");
    return 0;
}

int view_attendance_report() {
    int student_id;
    printf("Enter student ID (0 for all students): ");
    if (scanf("%d", &student_id) != 1) {
        fprintf(stderr, "Invalid input\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();
    
    FILE *file = fopen("attendance.dat", "rb");
    if (file == NULL) {
        printf("No attendance records found.\n");
        return 1;
    }
    
    Attendance attendance;
    int found = 0;
    
    printf("\n=== Attendance Report ===\n");
    if (student_id == 0) {
        printf("%-10s %-12s %-8s %-20s\n", "Student ID", "Date", "Status", "Reason");
    } else {
        printf("%-12s %-8s %-20s\n", "Date", "Status", "Reason");
    }
    printf("--------------------------------------------------------\n");
    
    while (fread(&attendance, sizeof(Attendance), 1, file) == 1) {
        if (student_id == 0 || attendance.student_id == student_id) {
            if (student_id == 0) {
                printf("%-10d %-12s %-8c %-20s\n",
                       attendance.student_id, attendance.date, 
                       attendance.status, attendance.reason);
            } else {
                printf("%-12s %-8c %-20s\n",
                       attendance.date, attendance.status, attendance.reason);
            }
            found = 1;
        }
    }
    
    if (!found) {
        printf("No attendance records found.\n");
    }
    
    fclose(file);
    return 0;
}

// Reporting Functions
int generate_class_report() {
    char class_name[MAX_CLASS_LEN];
    printf("Enter class name: ");
    if (fgets(class_name, sizeof(class_name), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    class_name[strcspn(class_name, "\n")] = '\0';
    
    FILE *student_file = fopen("students.dat", "rb");
    if (student_file == NULL) {
        printf("No student records found.\n");
        return 1;
    }
    
    Student student;
    int student_count = 0;
    
    printf("\n=== Class Report for %s ===\n", class_name);
    printf("%-6s %-20s %-4s %-15s %-20s\n", "ID", "Name", "Age", "Phone", "Email");
    printf("------------------------------------------------------------------------\n");
    
    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if (student.is_active && strcmp(student.class_section, class_name) == 0) {
            char full_name[100];
            sprintf(full_name, "%s %s", student.first_name, student.last_name);
            printf("%-6d %-20s %-4d %-15s %-20s\n",
                   student.student_id, full_name, student.age, student.phone, student.email);
            student_count++;
        }
    }
    
    fclose(student_file);
    printf("\nTotal students in class: %d\n", student_count);
    return 0;
}

int generate_grade_report() {
    char subject[MAX_SUBJECT_LEN];
    printf("Enter subject name (or press Enter for all subjects): ");
    if (fgets(subject, sizeof(subject), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    subject[strcspn(subject, "\n")] = '\0';
    
    FILE *grade_file = fopen("grades.dat", "rb");
    if (grade_file == NULL) {
        printf("No grade records found.\n");
        return 1;
    }
    
    Grade grade;
    float total_percentage = 0;
    int count = 0;
    
    printf("\n=== Grade Report ===\n");
    if (strlen(subject) > 0) {
        printf("Subject: %s\n", subject);
    }
    printf("%-10s %-15s %-15s %-25s %-10s %-12s\n", 
           "Student ID", "Subject", "Type", "Assignment", "Score", "Percentage");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fread(&grade, sizeof(Grade), 1, grade_file) == 1) {
        if (strlen(subject) == 0 || strcmp(grade.subject, subject) == 0) {
            float percentage = (grade.score / grade.max_score) * 100;
            printf("%-10d %-15s %-15s %-25s %-10.2f %-12.1f%%\n",
                   grade.student_id, grade.subject, grade.assignment_type,
                   grade.assignment_name, grade.score, percentage);
            total_percentage += percentage;
            count++;
        }
    }
    
    if (count > 0) {
        printf("\nOverall Average: %.1f%%\n", total_percentage / count);
    } else {
        printf("No grades found.\n");
    }
    
    fclose(grade_file);
    return 0;
}

// Main function
int main(void) {
    int choice, sub_choice;
    
    // Load system configuration
    load_next_ids();
    
    printf("=== Welcome to Comprehensive Student Management System ===\n");
    
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Student Management\n");
        printf("2. Teacher Management\n");
        printf("3. Grade Management\n");
        printf("4. Attendance Management\n");
        printf("5. Reports\n");
        printf("6. System Settings\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please try again.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch (choice) {
            case 1: // Student Management
                printf("\n=== STUDENT MANAGEMENT ===\n");
                printf("1. Add Student\n");
                printf("2. View All Students\n");
                printf("3. Search Student\n");
                printf("4. Delete Student\n");
                printf("5. Delete All Students\n");
                printf("6. Back to Main Menu\n");
                printf("Enter choice: ");
                
                if (scanf("%d", &sub_choice) != 1) {
                    fprintf(stderr, "Invalid input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                switch (sub_choice) {
                    case 1: add_student(); break;
                    case 2: show_all_students(); break;
                    case 3: search_student(); break;
                    case 4: delete_student(); break;
                    case 5: delete_all_students(); break;
                    case 6: break;
                    default: printf("Invalid choice\n");
                }
                break;
                
            case 2: // Teacher Management
                printf("\n=== TEACHER MANAGEMENT ===\n");
                printf("1. Add Teacher\n");
                printf("2. View All Teachers\n");
                printf("3. Back to Main Menu\n");
                printf("Enter choice: ");
                
                if (scanf("%d", &sub_choice) != 1) {
                    fprintf(stderr, "Invalid input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                switch (sub_choice) {
                    case 1: add_teacher(); break;
                    case 2: show_all_teachers(); break;
                    case 3: break;
                    default: printf("Invalid choice\n");
                }
                break;
                
            case 3: // Grade Management
                printf("\n=== GRADE MANAGEMENT ===\n");
                printf("1. Add Grade\n");
                printf("2. View Student Grades\n");
                printf("3. Back to Main Menu\n");
                printf("Enter choice: ");
                
                if (scanf("%d", &sub_choice) != 1) {
                    fprintf(stderr, "Invalid input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                switch (sub_choice) {
                    case 1: add_grade(); break;
                    case 2: view_student_grades(); break;
                    case 3: break;
                    default: printf("Invalid choice\n");
                }
                break;
                
            case 4: // Attendance Management
                printf("\n=== ATTENDANCE MANAGEMENT ===\n");
                printf("1. Mark Attendance\n");
                printf("2. View Attendance Report\n");
                printf("3. Back to Main Menu\n");
                printf("Enter choice: ");
                
                if (scanf("%d", &sub_choice) != 1) {
                    fprintf(stderr, "Invalid input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                switch (sub_choice) {
                    case 1: mark_attendance(); break;
                    case 2: view_attendance_report(); break;
                    case 3: break;
                    default: printf("Invalid choice\n");
                }
                break;
                
            case 5: // Reports
                printf("\n=== REPORTS ===\n");
                printf("1. Class Report\n");
                printf("2. Grade Report\n");
                printf("3. Back to Main Menu\n");
                printf("Enter choice: ");
                
                if (scanf("%d", &sub_choice) != 1) {
                    fprintf(stderr, "Invalid input\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                switch (sub_choice) {
                    case 1: generate_class_report(); break;
                    case 2: generate_grade_report(); break;
                    case 3: break;
                    default: printf("Invalid choice\n");
                }
                break;
                
            case 6: // System Settings
                printf("\n=== SYSTEM SETTINGS ===\n");
                printf("Current ID counters:\n");
                printf("Next Student ID: %d\n", next_student_id);
                printf("Next Teacher ID: %d\n", next_teacher_id);
                printf("Next Grade ID: %d\n", next_grade_id);
                printf("Next Attendance ID: %d\n", next_attendance_id);
                printf("Press Enter to continue...");
                getchar();
                break;
                
            case 7: // Exit
                printf("Thank you for using the Student Management System!\n");
                printf("Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
