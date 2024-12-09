//-------------------------------------------------------------------------------------------------------------
// Group names: Haron Taher, HyungJoo Yoon, Caitlin Chau
// Assignment: Final Project
// Due date: 12/1/2024
// Purpose: This is the preprocessor for our compiler project. The purpose of this program is to preprocess a
// source file by formatting it consistently for a compiler to parse. It removes unnecessary whitespace,
// special characters, and ignores comments, making the code cleaner and ready for further processing.
//-------------------------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // Declare input and output file streams
    ifstream infile;
    ofstream outfile;

    // Open the input file
    infile.open("final.txt");
    if (infile.bad()) { // Check if there was an error opening the input file
        cerr << "Error opening input file\n";
        exit(1);
    }

    // Open the output file
    outfile.open("finalf24.txt");
    if (outfile.bad()) { // Check if there was an error opening the output file
        cerr << "Error opening output file\n";
        exit(1);
    }

    // Initialize variables
    char prev = '\n';  // Keeps track of the previous character to handle whitespace and newlines
    int line_no = 1;   // Tracks the current line number (not used explicitly in output but can be useful for debugging)
    char c = infile.get(); // Read the first character

    // Process the input file character by character
    while (infile.get(c)) {
        switch (c) {

        case ',': // Handle commas
            // Add a space before the comma if it does not follow a space
            if (prev != ' ') {
                outfile << " " << c;
                prev = c;
            } else {
                outfile << c;
                prev = c;
            }
            break;

        case '\"': // Handle double-quoted strings
            outfile << c; // Output the opening quotation mark
            prev = c;
            c = '\0'; // Reset the character
            // Read until the closing quotation mark is found
            while (!infile.eof() && c != '\"') {
                c = infile.get();
                outfile << c; // Output the character inside the string
            }
            break;

        case ' ': // Handle spaces
            // Ignore consecutive spaces or spaces at the beginning of a line
            if (prev == ' ' || prev == '\n') {
                continue;
            } else {
                prev = c; // Keep track of the current character
                outfile << c; // Output the space
            }
            break;

        case '\n': // Handle newlines
            // Ignore consecutive newlines
            if (prev == '\n') {
                continue;
            } else {
                line_no++; // Increment line number
                outfile << c; // Output the newline
                prev = c; // Update the previous character
            }
            break;

        case '(': { // Handle parentheses
            // Check if this is the start of a comment "(*)"
            if (infile.peek() == '*') {
                infile.get(); // Consume the '*'
                // Ignore everything until the closing "*)"
                while (infile.get(c)) {
                    if (c == '*' && infile.peek() == ')') {
                        infile.get(); // Consume the ')'
                        break;
                    }
                }
            } else if (infile.peek() != ' ') {
                // If not a comment, add a space before the parenthesis if needed
                outfile << " " << c;
                prev = c;
            } else {
                outfile << c; // Output the parenthesis
                prev = c;
            }
            break;
        }

        case ')': {
            if (prev != ' ')    // If not a comment, add a space before the parenthesis if needed
            {
                outfile << " " << c;
                prev = c;
            }else
            {
                outfile << c;   // Output the parenthesis
                prev = c;
            }
            
            break;
        }

        case ';': // Handle semicolons
            // Add a space before the semicolon if it does not follow a space
            if (prev != ' ') {
                outfile << " " << c;
            } else {
                outfile << c; // Output the semicolon
            }
            break;

        default: // Handle all other characters
            outfile << c; // Output the character
            prev = c; // Update the previous character
            break;
        }
    }
    // Close the input and output files
    infile.close();
    outfile.close();

    return 0;
}
