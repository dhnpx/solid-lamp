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
        } else if (c == ',' && prev == ' ') {
            outfile.seekp((long)outfile.tellp() - 1);
            outfile.write(",", 1);
        } else if (c == '\"') {
            outfile << c;
            prev = c;
            c = '\0';
            while (!infile.eof() && c != '\"') {
                c = infile.get();
                outfile << c;
            }
        } else if ((c == ' ' || c == '\n') && prev == '\n') {
            continue;
        } else if (c == ' ' && prev == ' ') {
            continue;
        } else if (c == '(') {
            prev = c;
            c = infile.get();
            if (c == '*') {
                while (!infile.eof() && (c != ')' && prev != '*')) {
                    c = infile.get();
                    prev = c;
                }
                infile.get();
            } else if (c == ' ') {
                outfile << prev;
            } else {
                outfile << prev << c;
            }
        } else if (c == '*' && prev == '(') {
        } else {
            if (c == '\n') {
                if (prev == '\n') {
                    continue;
                }
                line_no++;
            }
            outfile << c;
            prev = c;
        }
    }
    return 0;
}
