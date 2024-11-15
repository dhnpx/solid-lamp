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
    while (!infile.eof()) {
        char c = infile.get();
        if (c == ')' && prev == ' ') {
            outfile.seekp((long)outfile.tellp() - 1);
            outfile.write(")", 1);
            prev = c;
        } else if (c == ',' && prev == ' ') {
            outfile.seekp((long)outfile.tellp() - 1);
            outfile.write(",", 1);
            prev = c;
        } else if (c == ';' && prev == ' ') {
            outfile.seekp((long)outfile.tellp() - 1);
            outfile.write(";", 1);
            prev = c;
        } else if (c == '\"') {
            outfile << c;
            prev = c;
            c = '\0';
            while (!infile.eof() && c != '\"') {
                c = infile.get();
                outfile << c;
            }
        } else if (c == ' ') {
            if (prev == ' ' || prev == '\n') {
                continue;
            } else {
                prev = c;
                outfile << c;
            }
        } else if (c == '\n') {
            if (prev == '\n') {
                continue;
            } else {
                line_no++;
                outfile << c;
                prev = c;
            }
        } else if (c == '(') {
            char next = infile.get();
            if (next == '*') {
                while (!infile.eof() && (next != ')' && c != '*')) {
                    next = infile.get();
                    c = next;
                }
                infile.get();
            } else if (next == ' ') {
                outfile << c;
                prev = c;
                c = next;
            } else {
                outfile << c << next;
                prev = c;
                c = next;
            }
        } else {
            outfile << c;
            prev = c;
        }
    }
    return 0;
}
