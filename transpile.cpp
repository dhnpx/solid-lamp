//-------------------------------------------------------------------------------------------------------------
// Group names: Haron Taher, HyungJoo Yoon, Caitlin Chau
// Assignment: Final Project
// Due date: 12/3/2024
// Purpose: Transpiles a source file into C++ code by mapping keywords and
// generating valid C++ syntax.
//-------------------------------------------------------------------------------------------------------------

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Enum representing the supported keywords
enum keywords {
    program,   // 'program' keyword
    begin,     // 'begin' keyword
    var,       // 'var' keyword
    print,     // 'print' keyword
    end,       // 'end' keyword
    semicolon, // Semicolon symbol (';')
};

// Map for quick keyword lookup and mapping to enum values
unordered_map<string, keywords> keywords_map = {
    {"program", program}, {"begin", keywords::begin}, {"var", var},
    {"print", print},     {"end", keywords::end},     {";", semicolon}};

int main() {
    // Declare file streams for input and output
    ifstream in;
    ofstream out;
    string token = "";  // Stores the current token being processed
    vector<string> buf; // Temporary buffer for holding tokens
    int line_no = 1;    // Line number tracker for debugging or error handling

    // Open the input file for reading
    in.open("finalf24.txt");
    if (in.bad()) { // Check if the input file could not be opened
        cerr << "Error opening input file\n";
        exit(1);
    }

    // Open the output file for writing
    out.open("finalf24.cpp");
    if (out.bad()) { // Check if the output file could not be opened
        cerr << "Error opening output file\n";
        exit(1);
    }

    // Write the initial setup for the C++ output file
    out << "#include <iostream>\n";
    out << "using namespace std;\n";
    out << "int main()\n";
    out << "{\n\t";

    // Process the input file token by token
    while (!in.eof()) {
        in >> token;  // Read the next token
        in.ignore(1); // Ignore the next character (whitespace)
        auto it = keywords_map.find(token); // Check if the token is a keyword

        if (it == keywords_map.end()) {
            // If the token is not a keyword, write it directly to the output
            // file
            out << token << " ";
            token.clear();
            continue;
        }

        // Handle recognized keywords
        switch (it->second) {
        case program:
            // Skip tokens until a semicolon is encountered
            while (token != ";") {
                in >> token;
                in.ignore();
            }
            token.clear();
            buf.clear(); // Clear buffer
            break;

        case keywords::begin:
            // 'begin' does not generate any output for C++ syntax
            continue;
            break;

        case var:
            // Process variable declarations
            while (token != ";") {
                in >> token;
                in.ignore();
                buf.push_back(token); // Add tokens to the buffer
            }

            // Handle integer type declarations
            if (buf[buf.size() - 2] == "integer") {
                out << "int "; // Map 'integer' to C++ 'int'
            }

            // Transpile variables and declarations into valid C++ syntax
            for (int i = 0; i < buf.size(); i++) {
                if (buf[i] == ":") {
                    // End the variable declaration when ':' is encountered
                    out << ";\n\t";
                    buf.clear();
                    break;
                }
                out << buf[i] << " "; // Write variable names and symbols
            }
            buf.clear(); // Clear the buffer after processing
            break;

        case print:
            // Process print statements
            while (token != ";") {
                in >> token;
                buf.push_back(token); // Add tokens to the buffer
            }

            // Convert 'print' to C++'s 'cout' statement
            out << "cout << ";
            for (int i = 1; i < buf.size() - 2; i++) {
                if (buf[i] == ",") {
                    out << "<< "; // Handle multiple outputs with commas
                } else {
                    out << buf[i] << " "; // Write the output value
                }
            }
            out << "<< endl;\n\t"; // End the 'cout' statement
            buf.clear();           // Clear buffer after processing
            token.clear();         // Clear token
            break;

        case keywords::end:
            // Add C++ termination logic

            out << "system (\"pause\");\n\t"; // Pause the program execution
            out << "return 0;\n"; // Return 0 to indicate successful execution

            // Finalize the C++ program with a closing brace
            out << "}";
            in.close(); // Close the input and output file streams
            out.close();
            return 0;
        case semicolon:
            // Write semicolon and move to the next line
            out << ";\n\t";
            break;

        default:
            // Write any unrecognized tokens directly to the output
            out << token << " ";
            break;
        }
    }
}
