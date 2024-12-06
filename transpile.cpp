#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum keywords {
    program,
    begin,
    var,
    print,
    end,
    semicolon,
};

unordered_map<string, keywords> keywords_map = {
    {"program", program}, {"begin", keywords::begin}, {"var", var},
    {"print", print},     {"end", keywords::end},     {";", semicolon}};

int main() {
    ifstream in;
    ofstream out;
    string token = "";
    vector<string> buf;
    int line_no = 1;

    in.open("finalf24.txt");
    if (in.bad()) {
        cerr << "Error opening input file\n";
        exit(1);
    }
    out.open("finalf24.cpp");
    if (out.bad()) {
        cerr << "Error opening output file\n";
        exit(1);
    }

    out << "#include <iostream>\n";
    out << "using namespace std;\n";
    out << "int main()\n";
    out << "{\n\t";

    while (!in.eof()) {
        in >> token;
        in.ignore(1);
        auto it = keywords_map.find(token);

        if (it == keywords_map.end()) {
            out << token << " ";
            token.clear();
            continue;
        }
        switch (it->second) {
        case program:
            while (token != ";") {
                in >> token;
                in.ignore();
            }
            break;
            token.clear();
            buf.clear();
        case keywords::begin:
            continue;
            break;
        case var:
            while (token != ";") {
                in >> token;
                in.ignore();
                buf.push_back(token);
            }
            for (auto i : buf) {
                cout << i << endl;
            }
            if (buf[buf.size() - 2] == "integer") {
                out << "int ";
            };
            for (int i = 0; i < buf.size(); i++) {
                if (buf[i] == ":") {
                    out << ";\n\t";
                    buf.clear();
                    break;
                }
                out << buf[i] << " ";
            }
            buf.clear();
            break;
        case print:
            while (token != ";") {
                in >> token;
                cout << token << endl;
                buf.push_back(token);
            }
            out << "cout << ";
            for (int i = 1; i < buf.size() - 2; i++) {
                if (buf[i] == ",") {
                    out << "<< ";
                } else {
                    out << buf[i] << " ";
                }
            }
            out << "<< endl;\n\t";
            buf.clear();
            token.clear();
            break;
        case keywords::end:
            out << "system (\"pause\");\n\t";
            out << "return 0;\n";
            break;
        case semicolon:
            out << ";\n\t";
            break;
        default:
            out << token << " ";
        }
    }
    out << "}";

    in.close();
    out.close();

    return 0;
}
