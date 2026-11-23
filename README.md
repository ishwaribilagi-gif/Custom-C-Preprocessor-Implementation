# Custom C Preprocessor Implementation in C

## 📌 Project Overview

This project implements a simplified C preprocessor using the C programming language.

The program accepts a C source file as command-line input, performs preprocessing operations, and generates an output file with the `.i` extension.

The main objective of this project is to understand the internal working of a C preprocessor through file handling, string manipulation, header file inclusion, and macro expansion.

## ✨ Features

- **Single-Line Comment Removal:** Removes `//` comments.
- **Multi-Line Comment Removal:** Removes `/* ... */` comments.
- **Header File Inclusion:** Supports user-defined header files using `#include "filename"`.
- **Nested Header Inclusion:** Supports nested user-defined header files.
- **Object-Like Macro Expansion:** Supports macros such as `#define PI 3.14`.
- **Function-Like Macro Expansion:** Supports single-parameter macros such as `#define SQUARE(x) ((x) * (x))`.
- **String and Character Protection:** Prevents macro replacement inside string and character literals.
- **Output File Generation:** Generates a preprocessed `.i` file.
- **Error Handling:** Handles invalid input files and missing header files.
- **Modular Programming:** Implements different preprocessing operations using separate source files.

## 🛠️ Technologies Used

- Programming Language: C
- Compiler: GCC
- Operating System: Ubuntu Linux
- Build Tool: GNU Make

## 📂 Project Structure

```text
Custom-C-Preprocessor-Implementation/
│
├── main.c
├── preprocessor.c
├── preprocessor.h
├── comment_removal.c
├── file_inclusion.c
├── macro_handler.c
│
├── makefile
├── README.md
│
├── inputfile.c
├── myheader.h
├── second.h
└── third.h
```

## ⚙️ Compilation

Clone the repository:

```bash
git clone YOUR_REPOSITORY_URL
```

Navigate to the project directory:

```bash
cd Custom-C-Preprocessor-Implementation
```

Compile the project using Makefile:

```bash
make
```

To clean generated files:

```bash
make clean
```

## ▶️ Execution

Run the executable by providing a C source filename as a command-line argument:

```bash
./mypreprocessor inputfile.c
```

The program generates an output file:

```text
inputfile.i
```

## 💻 Example

### Input File (inputfile.c)

```c
#include <stdio.h>
#include "myheader.h"

#define PI 3.14
#define MAX 100
#define SQUARE(x) ((x) * (x))

int main()
{
    // Variable declarations

    float radius = 5;
    float area = PI * radius * radius;

    int value = MAX;
    int result = SQUARE(5);

    printf("Area = %f\n", area);
    printf("Maximum = %d\n", value);
    printf("Square = %d\n", result);

    return 0;
}
```

### Generated Output (inputfile.i)

```c
#include <stdio.h>

void display()
{
    printf("Hello from header file!\n");
}

int main()
{
    float radius = 5;
    float area = 3.14 * radius * radius;

    int value = 100;
    int result = ((5) * (5));

    printf("Area = %f\n", area);
    printf("Maximum = %d\n", value);
    printf("Square = %d\n", result);

    return 0;
}
```

## 🧪 Testing

The project was tested with the following cases:

- Single-line and multi-line comment removal.
- User-defined header file inclusion.
- Nested header file inclusion.
- Object-like macro expansion.
- Function-like macro expansion.
- String and character literal protection.
- Invalid input filename handling.
- Missing header file handling.
- Output file generation.
- Compilation and execution of generated C code.

To compile the generated output:

```bash
gcc -x c inputfile.i -o test
```

Execute:

```bash
./test
```

### Expected Output

```text
Area = 78.500000
Maximum = 100
Square = 25
```

## 📚 Learning Outcomes

Through this project, I gained practical experience in:

- C file handling.
- Command-line argument handling.
- String manipulation.
- Modular programming.
- Header file processing.
- Macro processing and expansion.
- Error handling.
- Compilation using GCC.
- Build automation using Makefile.

## 👩‍💻 Author

**Ishwari Sampatakumar Bilagi**

GitHub: `ishwaribilagi-gif`

LinkedIn: `ishwari-bilagi-61b762277`



**Project:** Custom C Preprocessor Implementation  
**Language:** C  
**Environment:** Ubuntu Linux
