# Student Management Program

A comprehensive command-line school management system written in C that provides complete functionality for managing students, teachers, grades, attendance, and generating reports. This system is designed to handle all aspects of school administration efficiently.

## Features

### Student Management
- **Add Student**: Create comprehensive student profiles with auto-generated IDs
- **View All Students**: Display formatted list of all active students
- **Advanced Search**: Search students by ID, name, or class/section
- **Delete Student**: Safely remove student records (marks as inactive)
- **Comprehensive Data**: Stores first/last name, age, DOB, gender, contact info, emergency contacts, class/section, enrollment date

### Teacher Management
- **Add Teacher**: Register teachers with subject assignments and contact information
- **View All Teachers**: Display all active teachers with their subjects
- **Subject Assignment**: Link teachers to specific subjects they teach

### Grade Management
- **Add Grades**: Record grades for different assignment types (Assignment, Quiz, Exam, Project)
- **View Student Grades**: Display all grades for a student with calculated averages
- **Multiple Subjects**: Support for unlimited subjects per student
- **GPA Calculation**: Automatic percentage and average calculations
- **Assignment Tracking**: Track individual assignments with scores and maximum points

### Attendance Management
- **Mark Attendance**: Record daily attendance with multiple status options
- **Attendance Status**: Support for Present (P), Absent (A), Tardy (T), Excused (E)
- **Attendance Reports**: View attendance history for individual students or all students
- **Reason Tracking**: Optional reason field for absences or tardiness

### Reporting System
- **Class Reports**: Generate comprehensive reports for specific classes/sections
- **Grade Reports**: View grade summaries by subject or across all subjects
- **Attendance Reports**: Analyze attendance patterns and statistics
- **System Overview**: Monitor system status and ID counters

### Data Management
- **Auto-ID Generation**: Automatic unique ID assignment for all entities
- **Data Validation**: Email and phone number format validation
- **Binary File Storage**: Efficient binary file format for data integrity
- **Persistent Configuration**: System settings saved between sessions
- **Error Handling**: Comprehensive input validation and error recovery

## Getting Started

### Prerequisites

- GCC compiler or any C compiler
- Linux/Unix environment (or Windows with appropriate C compiler)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Ratkiller446/Student-Management-Program.git
   cd Student-Management-Program
   ```

2. Compile the program:
   ```bash
   gcc -o StudentManagement StudentManagement.c
   ```

### Usage

Run the compiled program:
```bash
./StudentManagement
```

The program will display a hierarchical menu system with the following main categories:

```
=== MAIN MENU ===
1. Student Management
2. Teacher Management
3. Grade Management
4. Attendance Management
5. Reports
6. System Settings
7. Exit
```

#### Student Management

Access comprehensive student management features:
- **Add Student**: Enter detailed student information including personal details, contact information, emergency contacts, and class assignment
- **View All Students**: Display formatted table of all active students with key information
- **Search Student**: Find students by ID, name, or class with detailed results
- **Delete Student**: Safely remove students (marks as inactive rather than permanent deletion)

#### Teacher Management

Manage teaching staff:
- **Add Teacher**: Register new teachers with subject assignments and contact details
- **View All Teachers**: Display all active teachers with their assigned subjects

#### Grade Management

Handle academic performance tracking:
- **Add Grade**: Record grades for specific assignments, quizzes, exams, or projects
- **View Student Grades**: Display comprehensive grade history with automatic average calculations

#### Attendance Management

Track student attendance:
- **Mark Attendance**: Record daily attendance with status codes (Present, Absent, Tardy, Excused)
- **View Attendance Report**: Generate attendance reports for individual students or entire school

#### Reports

Generate comprehensive reports:
- **Class Report**: View all students in a specific class/section
- **Grade Report**: Analyze academic performance by subject or across all subjects

#### System Settings

Monitor system status and view current ID counters for students, teachers, grades, and attendance records.

## File Structure

```
Student-Management-Program/
├── StudentManagement.c    # Main source code
├── StudentManagement      # Compiled executable
├── students.dat          # Binary student records
├── teachers.dat          # Binary teacher records
├── grades.dat            # Binary grade records
├── attendance.dat        # Binary attendance records
├── system_config.txt     # System configuration and ID counters
├── LICENSE               # GNU AGPL v3 License
└── README.md            # This file
```

## Data Storage

The system uses efficient binary file storage for optimal performance and data integrity:

- **students.dat**: Student records with comprehensive personal and academic information
- **teachers.dat**: Teacher records with subject assignments and contact details
- **grades.dat**: Grade records linking students to assignments with scores and percentages
- **attendance.dat**: Attendance records with dates, status codes, and reasons
- **system_config.txt**: System configuration including next available ID numbers

Each record type uses structured data formats with automatic ID generation and data validation.

## Technical Details

- **Language**: C (C99 standard)
- **Data Structures**: Custom structs for Student, Teacher, Grade, and Attendance entities
- **File I/O**: Binary file operations for efficient data storage and retrieval
- **Memory Management**: Stack-allocated structures with proper bounds checking
- **ID Management**: Auto-incrementing ID system with persistent storage
- **Data Validation**: Email format validation, phone number validation, input sanitization
- **Error Handling**: Comprehensive error checking with user-friendly messages
- **Menu System**: Hierarchical menu structure for intuitive navigation
- **Date Handling**: Automatic date generation and formatting using system time
- **Search Algorithms**: Multiple search criteria with efficient file scanning

### Key Improvements Over Original

1. **Enhanced Data Model**: Expanded from basic name/age/grade to comprehensive student profiles
2. **Multi-Entity Support**: Added teachers, grades, and attendance tracking
3. **Binary File Format**: Improved from plain text to structured binary storage
4. **ID System**: Auto-generated unique IDs for all entities
5. **Data Validation**: Added email, phone, and input validation
6. **Reporting System**: Comprehensive reporting capabilities
7. **Menu Organization**: Hierarchical menu system for better user experience
8. **Error Recovery**: Robust error handling with graceful recovery
9. **Data Integrity**: Soft deletion (marking inactive) instead of permanent removal
10. **Performance**: Binary file operations for faster data access

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the GNU Affero General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Author

- **Ratkiller446** - [GitHub Profile](https://github.com/Ratkiller446)

## Acknowledgments

- Thanks to the open-source community for inspiration and best practices
- Built as a learning project to demonstrate basic C programming concepts