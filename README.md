# Student Management Program

A simple command-line student management system written in C that allows you to manage student records with basic CRUD (Create, Read, Update, Delete) operations.

## Features

- **Add Student**: Add new student records with name, age, and grade
- **View All Students**: Display all stored student records
- **Search Student**: Find a specific student by name
- **Delete Student**: Remove a specific student record
- **Delete All Students**: Clear all student records
- **Interactive Menu**: Easy-to-use command-line interface

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

The program will display an interactive menu with the following options:

```
Menu:
1. Add Student
2. Show all Students
3. Search a Student
4. Delete a Student
5. Delete all Students
6. Exit
```

#### Adding a Student

1. Select option `1` from the menu
2. Enter the student's name when prompted
3. Enter the student's age (numeric value)
4. Enter the student's grade (0-100)

#### Viewing All Students

Select option `2` to display all stored student records in the format:
```
Name, Age, Grade: XX
```

#### Searching for a Student

1. Select option `3` from the menu
2. Enter the name of the student you want to search for
3. The program will display matching records

#### Deleting a Student

1. Select option `4` from the menu
2. Enter the name of the student you want to delete
3. The program will remove the matching record

#### Deleting All Students

Select option `5` to clear all student records from the database.

## File Structure

```
Student-Management-Program/
├── StudentManagement.c    # Main source code
├── StudentManagement      # Compiled executable
├── LICENSE               # GNU AGPL v3 License
└── README.md            # This file
```

## Data Storage

Student records are stored in a plain text file called `student.txt` in the same directory as the executable. Each student record is stored in the format:
```
Name, Age, Grade: XX
```

## Technical Details

- **Language**: C
- **File I/O**: Uses standard C file operations (`fopen`, `fgets`, `fprintf`, etc.)
- **Memory Management**: Uses stack-allocated arrays for string handling
- **Error Handling**: Includes basic error checking for file operations and user input

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