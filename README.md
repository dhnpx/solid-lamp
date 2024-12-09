### README: Compiler Final Project

#### **Overview**
This project demonstrates the implementation of a basic compiler using C++ for a simplified programming language. The compiler includes a preprocessor, transpiler, and parser that transform a source file into C++ code, check its grammar against predefined rules, and generate appropriate outputs or error messages.

---

#### **Project Structure**
1. **Input Files:**
   - `final.txt`: Original source file containing a program written in the custom language.
   - `finalf24.txt`: Preprocessed version of `final.txt` with comments and excess spaces removed, and formatted for easier tokenization.

2. **Source Files:**
   - `preprocessor.cpp`: Cleans the input file by removing comments, extra spaces, and blank lines, and outputs `finalf24.txt`.
   - `parse.cpp`: Implements a parser to validate the grammar of the program using a predictive parsing approach and checks for errors.
   - `transpile.cpp`: Converts the preprocessed file into valid C++ code.
   - `finalf24.cpp`: Generated C++ code from the transpiler, ready to run.

3. **Output:**
   - Console messages indicating success (`Ready to compile`) or errors encountered during parsing.
   - A fully functional C++ program (`finalf24.cpp`) that can be compiled and executed.

---

### **How to Run the Compiler**

Follow these steps to run the compiler project and test its functionality:

---

#### **1. Preprocess the Input File**
- **Purpose:** Clean the input file (`final.txt`) by removing comments, extra spaces, and blank lines to produce `finalf24.txt`.
- **Steps:**
  1. Compile `preprocessor.cpp`:
     ```bash
     g++ preprocessor.cpp -o preprocessor
     ```
  2. Run the preprocessor:
     ```bash
     ./preprocessor
     ```
  3. Output:
     - The preprocessed file `finalf24.txt` will be generated in the current directory.

---

#### **2. Parse and Validate the Grammar**
- **Purpose:** Validate the syntax of the preprocessed file (`finalf24.txt`) using a predictive parser and check for grammar errors.
- **Steps:**
  1. Compile `parse.cpp`:
     ```bash
     g++ parse.cpp -o parser
     ```
  2. Run the parser:
     ```bash
     ./parser
     ```
  3. Output:
     - If the syntax is valid: `Ready to compile`.
     - If errors are found: A detailed error message will be displayed.

---

#### **3. Transpile to C++**
- **Purpose:** Convert the preprocessed program (`finalf24.txt`) into a valid C++ file (`finalf24.cpp`).
- **Steps:**
  1. Compile `transpile.cpp`:
     ```bash
     g++ transpile.cpp -o transpile
     ```
  2. Run the transpiler:
     ```bash
     ./transpile
     ```
  3. Output:
     - A C++ source file `finalf24.cpp` will be generated in the current directory.

---

#### **4. Run the Generated C++ Code**
- **Purpose:** Execute the transpiled C++ program to observe the output.
- **Steps:**
  1. Compile the C++ file:
     ```bash
     g++ finalf24.cpp -o finalf24
     ```
  2. Run the compiled program:
     ```bash
     ./finalf24
     ```
  3. Output:
     - The program will display variable values and computed results in the terminal.
     - Example:
       ```plaintext
       5
       value=72
       ```

---

#### **Summary of Commands**
```bash
# Step 1: Preprocess
g++ preprocessor.cpp -o preprocessor
./preprocessor

# Step 2: Parse
g++ parse.cpp -o parser
./parser

# Step 3: Transpile
g++ transpile.cpp -o transpile
./transpile

# Step 4: Compile and Run the Transpiled Code
g++ finalf24.cpp -o finalf24
./finalf24
```

This process ensures the program moves through all stages of compilation, validation, and execution.
---

#### **Features**
- **Preprocessor:**
  - Removes comments, blank lines, and excess spaces for easier tokenization and parsing.
  - Example: Converts `final.txt` into `finalf24.txt`.

- **Parser:**
  - Validates the program's syntax based on a defined grammar.
  - Detects and reports errors such as:
    - Missing keywords (`program`, `var`, `begin`, `end`).
    - Undefined variables or incorrect identifiers.
    - Missing punctuation (e.g., semicolons, parentheses).

- **Transpiler:**
  - Converts the validated program into a runnable C++ program.
  - Maps custom language keywords (`program`, `print`, etc.) to equivalent C++ syntax.

---

#### **Input and Output Example**
**Input File (`final.txt`):**
```plaintext
program f2024;
(* This program computes and prints the value of an expression *)
var
    a , b2a , c, bba : integer ;
begin
    a = 3 ;
    b2a = 14 ;
    c = 5 ;
    print ( c ); (* display c *)
    bba = ( b2a + 2 * c) * a ;
    print ( "value=", bba ) ; (* print the value of bba*)
end
```

**Preprocessed File (`finalf24.txt`):**
```plaintext
program f2024;
var
a , b2a , c , bba : integer ;
begin
a = 3 ;
b2a = 14 ;
c = 5 ;
print ( c ) ;
bba = ( b2a + 2 * c ) * a ;
print ( "value=" , bba ) ;
end
```

**Generated C++ Code (`finalf24.cpp`):**
```cpp
#include <iostream>
using namespace std;
int main()
{
    int a, b2a, c, bba;
    a = 3;
    b2a = 14;
    c = 5;
    cout << c << endl;
    bba = (b2a + 2 * c) * a;
    cout << "value=" << bba << endl;
    system("pause");
    return 0;
}
```

**Output:**
```plaintext
5
value=72
```

---

#### **Error Detection Examples**
- **Input Error:**
  ```plaintext
  progrm f2024;
  ```
  **Output:** `Error: program was expected, check if it is misspelled or missing! Line: 1`

- **Missing Semicolon:**
  ```plaintext
  b2a = 14
  ```
  **Output:** `Error: Missing semicolon at the end of line 2 after '14'`

---

#### **Contributors**
- Haron Taher
- HyungJoo Yoon
- Caitlin Chau

#### **Submission Requirements**
Include:
1. `final.txt`, `finalf24.txt`, `finalf24.cpp`.
2. Source code for all components (`preprocessor.cpp`, `parse.cpp`, `transpile.cpp`).
3. Project report with grammar definitions, parsing table, and error handling logic.

--- 

#### **Acknowledgments**
This project was completed as part of the Compiler Design course (CS 323, Fall 2024).
