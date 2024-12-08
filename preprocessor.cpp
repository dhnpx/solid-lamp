//-------------------------------------------------------------------------------------------------------------
// Group names: Haron Taher, HyungJoo Yoon, Caitlin Chau
// Assignment: Final Project
// Due date: 12/1/2024
// Purpose: This is the preproccessor for our compiler project preprocessor 
//-----------------------------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream infile;
    ofstream outfile;

    infile.open("final.txt");
    if (infile.bad()) {
        cerr << "Error opening input file\n";
        exit(1);
    }
    outfile.open("finalf24.txt");
    if (outfile.bad()) {
        cerr << "Error opening output file\n";
        exit(1);
    }

    char prev = '\n';
    int line_no = 1;
    char c = infile.get();
    while (infile.get(c)) {
        switch (c) {
        case ',':
            if (prev != ' ') {
                outfile << " " << c;
                prev = c;
            } else {
                outfile << c;
                prev = c;
            }
            break;
        case '\"':
            outfile << c;
            prev = c;
            c = '\0';
            while (!infile.eof() && c != '\"') {
                c = infile.get();
                outfile << c;
            }
            break;
        case ' ':
            if (prev == ' ' || prev == '\n') {
                continue;
            } else {
                prev = c;
                outfile << c;
            }
            break;
        case '\n':
            if (prev == '\n') {
                continue;
            } else {
                line_no++;
                outfile << c;
                prev = c;
            }
            break;
        case '(': {
            if (infile.peek() == '*') {
                infile.get();
                while (infile.get(c)) {
                    if (c == '*' && infile.peek() == ')') {
                        infile.get();
                        break;
                    }
                }
            } else if (infile.peek() != ' ') {
                outfile << " " << c;
                prev = c;
            } else {
                outfile << c;
                prev = c;
            }
            break;
        }
        case ';':
            if (prev != ' ') {
                outfile << " " << c;
            } else {
                outfile << c;
            }
            break;
        default:
            outfile << c;
            prev = c;
            break;
        }
    }
    infile.close();
    outfile.close();

    return 0;
}
