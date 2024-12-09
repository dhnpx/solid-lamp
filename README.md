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

#### **Steps to Run**
1. **Preprocessing the Input:**
   - Compile and run `preprocessor.cpp` with `final.txt` as input.
   - The preprocessed output is saved as `finalf24.txt`.

2. **Parsing for Grammar Validation:**
   - Compile and run `parse.cpp` with `finalf24.txt` as input.
   - The parser checks the program against the grammar rules and displays:
     - `Ready to compile` if no errors are found.
     - Specific error messages if issues are detected (e.g., missing semicolons, undefined identifiers).

3. **Transpilation to C++:**
   - Compile and run `transpile.cpp` with `finalf24.txt` as input.
   - The transpiler generates a C++ program and saves it as `finalf24.cpp`.

4. **Running the Generated Program:**
   - Compile and run `finalf24.cpp` using a C++ compiler.
   - Observe the program's output, which should display variable values and results of computations.

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
