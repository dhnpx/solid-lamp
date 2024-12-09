#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define printStack(s)                                                          \
    cout << "Stack: ";                                                         \
    for (auto &x : s)                                                          \
        cout << x << " ";                                                      \
    cout << "\n";

using namespace std;

// Predictive parsing table
unordered_map<string, unordered_map<string, string>> table = {
    {"<prog>",
     {{"program",
       "program <identifier> ; var <dec-list> begin <stat-list> end"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "blank"},
      {"b", "blank"},
      {"c", "blank"},
      {"d", "blank"},
      {"l", "blank"},
      {"f", "blank"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<identifier>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<letter> <identifier'>"},
      {"b", "<letter> <identifier'>"},
      {"c", "<letter> <identifier'>"},
      {"d", "<letter> <identifier'>"},
      {"l", "<letter> <identifier'>"},
      {"f", "<letter> <identifier'>"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<identifier'>",
     {{"program", ""},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<letter> <identifier'>"},
      {"b", "<letter> <identifier'>"},
      {"c", "<letter> <identifier'>"},
      {"d", "<letter> <identifier'>"},
      {"l", "<letter> <identifier'>"},
      {"f", "<letter> <identifier'>"},
      {"0", "<digit> <identifier'>"},
      {"1", "<digit> <identifier'>"},
      {"2", "<digit> <identifier'>"},
      {"3", "<digit> <identifier'>"},
      {"4", "<digit> <identifier'>"},
      {"5", "<digit> <identifier'>"},
      {"6", "<digit> <identifier'>"},
      {"7", "<digit> <identifier'>"},
      {"8", "<digit> <identifier'>"},
      {"9", "<digit> <identifier'>"},
      {"+", "lambda"},
      {"-", "lambda"},
      {"*", "lambda"},
      {"/", "lambda"},
      {"(", "blank"},
      {")", "lambda"},
      {"=", "lambda"},
      {":", "lambda"},
      {";", "lambda"},
      {",", "lambda"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<dec-list>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<dec> : <type> ;"},
      {"b", "<dec> : <type> ;"},
      {"c", "<dec> : <type> ;"},
      {"d", "<dec> : <type> ;"},
      {"l", "<dec> : <type> ;"},
      {"f", "<dec> : <type> ;"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<dec>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<identifier> <dec'>"},
      {"b", "<identifier> <dec'>"},
      {"c", "<identifier> <dec'>"},
      {"d", "<identifier> <dec'>"},
      {"l", "<identifier> <dec'>"},
      {"f", "<identifier> <dec'>"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<dec'>", {{"program", "blank"}, {"var", "blank"},
                {"begin", "blank"},   {"end", "blank"},
                {"integer", "blank"}, {"print", "blank"},
                {"a", "blank"},       {"b", "blank"},
                {"c", "blank"},       {"d", "blank"},
                {"l", "blank"},       {"f", "blank"},
                {"0", "blank"},       {"1", "blank"},
                {"2", "blank"},       {"3", "blank"},
                {"4", "blank"},       {"5", "blank"},
                {"6", "blank"},       {"7", "blank"},
                {"8", "blank"},       {"9", "blank"},
                {"+", "blank"},       {"-", "blank"},
                {"*", "blank"},       {"/", "blank"},
                {"(", "blank"},       {")", "blank"},
                {"=", "blank"},       {":", "lambda"},
                {";", "blank"},       {",", ", <identifier> <dec'>"},
                {"\"", "blank"},      {"$", "blank"}}},
    {"<type>",
     {{"program", "blank"}, {"var", "blank"},       {"begin", "blank"},
      {"end", "blank"},     {"integer", "integer"}, {"print", "blank"},
      {"a", "blank"},       {"b", "blank"},         {"c", "blank"},
      {"d", "blank"},       {"l", "blank"},         {"f", "blank"},
      {"0", "blank"},       {"1", "blank"},         {"2", "blank"},
      {"3", "blank"},       {"4", "blank"},         {"5", "blank"},
      {"6", "blank"},       {"7", "blank"},         {"8", "blank"},
      {"9", "blank"},       {"+", "blank"},         {"-", "blank"},
      {"*", "blank"},       {"/", "blank"},         {"(", "blank"},
      {")", "blank"},       {"=", "blank"},         {":", "blank"},
      {";", "blank"},       {",", "blank"},         {"\"", "blank"},
      {"$", "blank"}}},
    {"<stat-list>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "<stat> <stat-list'>"},
      {"a", "<stat> <stat-list'>"},
      {"b", "<stat> <stat-list'>"},
      {"c", "<stat> <stat-list'>"},
      {"d", "<stat> <stat-list'>"},
      {"l", "<stat> <stat-list'>"},
      {"f", "<stat> <stat-list'>"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<stat-list'>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "lambda"},
      {"integer", "blank"},
      {"print", "<stat> <stat-list'>"},
      {"a", "<stat> <stat-list'>"},
      {"b", "<stat> <stat-list'>"},
      {"c", "<stat> <stat-list'>"},
      {"d", "<stat> <stat-list'>"},
      {"l", "<stat> <stat-list'>"},
      {"f", "<stat> <stat-list'>"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<stat>",
     {{"program", "blank"}, {"var", "blank"},     {"begin", "blank"},
      {"end", "blank"},     {"integer", "blank"}, {"print", "<write>"},
      {"a", "<assign>"},    {"b", "<assign>"},    {"c", "<assign>"},
      {"d", "<assign>"},    {"l", "<assign>"},    {"f", "<assign>"},
      {"0", "blank"},       {"1", "blank"},       {"2", "blank"},
      {"3", "blank"},       {"4", "blank"},       {"5", "blank"},
      {"6", "blank"},       {"7", "blank"},       {"8", "blank"},
      {"9", "blank"},       {"+", "blank"},       {"-", "blank"},
      {"*", "blank"},       {"/", "blank"},       {"(", "blank"},
      {")", "blank"},       {"=", "blank"},       {":", "blank"},
      {";", "blank"},       {",", "blank"},       {"\"", "blank"},
      {"$", "blank"}}},
    {"<write>", {{"program", "blank"}, {"var", "blank"},
                 {"begin", "blank"},   {"end", "blank"},
                 {"integer", "blank"}, {"print", "print ( <write'> ) ;"},
                 {"a", "blank"},       {"b", "blank"},
                 {"c", "blank"},       {"d", "blank"},
                 {"l", "blank"},       {"f", "blank"},
                 {"0", "blank"},       {"1", "blank"},
                 {"2", "blank"},       {"3", "blank"},
                 {"4", "blank"},       {"5", "blank"},
                 {"6", "blank"},       {"7", "blank"},
                 {"8", "blank"},       {"9", "blank"},
                 {"+", "blank"},       {"-", "blank"},
                 {"*", "blank"},       {"/", "blank"},
                 {"(", "blank"},       {")", "lambda"},
                 {"=", "blank"},       {":", "blank"},
                 {";", "blank"},       {",", "blank"},
                 {"\"", "blank"},      {"$", "blank"}}},
    {"<write'>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<str> <identifier>"},
      {"b", "<str> <identifier>"},
      {"c", "<str> <identifier>"},
      {"d", "<str> <identifier>"},
      {"l", "<str> <identifier>"},
      {"f", "<str> <identifier>"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "<str> <identifier>"},
      {"$", "blank"}}},
    {"<str>",
     {{"program", "blank"}, {"var", "blank"},     {"begin", "blank"},
      {"end", "blank"},     {"integer", "blank"}, {"print", "blank"},
      {"a", "lambda"},      {"b", "lambda"},      {"c", "lambda"},
      {"d", "lambda"},      {"l", "lambda"},      {"f", "lambda"},
      {"0", "blank"},       {"1", "blank"},       {"2", "blank"},
      {"3", "blank"},       {"4", "blank"},       {"5", "blank"},
      {"6", "blank"},       {"7", "blank"},       {"8", "blank"},
      {"9", "blank"},       {"+", "blank"},       {"-", "blank"},
      {"*", "blank"},       {"/", "blank"},       {"(", "blank"},
      {")", "blank"},       {"=", "blank"},       {":", "blank"},
      {";", "blank"},       {",", "blank"},       {"\"", "\" value= \" ,"},
      {"$", "blank"}}},
    {"<assign>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<identifier> = <expr> ;"},
      {"b", "<identifier> = <expr> ;"},
      {"c", "<identifier> = <expr> ;"},
      {"d", "<identifier> = <expr> ;"},
      {"l", "<identifier> = <expr> ;"},
      {"f", "<identifier> = <expr> ;"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "blank"},
      {"-", "blank"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "blank"},
      {"=", "blank"},
      {":", "blank"},
      {";", "blank"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<expr>",
     {{"program", "blank"},    {"var", "blank"},        {"begin", "blank"},
      {"end", "blank"},        {"integer", "blank"},    {"print", "blank"},
      {"a", "<term> <expr'>"}, {"b", "<term> <expr'>"}, {"c", "<term> <expr'>"},
      {"d", "<term> <expr'>"}, {"l", "<term> <expr'>"}, {"f", "<term> <expr'>"},
      {"0", "<term> <expr'>"}, {"1", "<term> <expr'>"}, {"2", "<term> <expr'>"},
      {"3", "<term> <expr'>"}, {"4", "<term> <expr'>"}, {"5", "<term> <expr'>"},
      {"6", "<term> <expr'>"}, {"7", "<term> <expr'>"}, {"8", "<term> <expr'>"},
      {"9", "<term> <expr'>"}, {"+", "<term> <expr'>"}, {"-", "<term> <expr'>"},
      {"*", "blank"},          {"/", "blank"},          {"(", "<term> <expr'>"},
      {")", "lambda"},         {"=", "blank"},          {":", "blank"},
      {";", "lambda"},         {",", "blank"},          {"\"", "blank"},
      {"$", "blank"}}},
    {"<expr'>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "blank"},
      {"b", "blank"},
      {"c", "blank"},
      {"d", "blank"},
      {"l", "blank"},
      {"f", "blank"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "+ <term> <expr'>"},
      {"-", "- <term> <expr'>"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "blank"},
      {")", "lambda"},
      {"=", "blank"},
      {":", "blank"},
      {";", "lambda"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<term>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "<factor> <term'>"},
      {"b", "<factor> <term'>"},
      {"c", "<factor> <term'>"},
      {"d", "<factor> <term'>"},
      {"l", "<factor> <term'>"},
      {"f", "<factor> <term'>"},
      {"0", "<factor> <term'>"},
      {"1", "<factor> <term'>"},
      {"2", "<factor> <term'>"},
      {"3", "<factor> <term'>"},
      {"4", "<factor> <term'>"},
      {"5", "<factor> <term'>"},
      {"6", "<factor> <term'>"},
      {"7", "<factor> <term'>"},
      {"8", "<factor> <term'>"},
      {"9", "<factor> <term'>"},
      {"+", "<factor> <term'>"},
      {"-", "<factor> <term'>"},
      {"*", "blank"},
      {"/", "blank"},
      {"(", "<factor> <term'>"},
      {")", "lambda"},
      {"=", "blank"},
      {":", "blank"},
      {";", "lambda"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<term'>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "blank"},
      {"b", "blank"},
      {"c", "blank"},
      {"d", "blank"},
      {"l", "blank"},
      {"f", "blank"},
      {"0", "blank"},
      {"1", "blank"},
      {"2", "blank"},
      {"3", "blank"},
      {"4", "blank"},
      {"5", "blank"},
      {"6", "blank"},
      {"7", "blank"},
      {"8", "blank"},
      {"9", "blank"},
      {"+", "lambda"},
      {"-", "lambda"},
      {"*", "* <factor> <term'>"},
      {"/", "/ <factor> <term'>"},
      {"(", "blank"},
      {")", "lambda"},
      {"=", "blank"},
      {":", "blank"},
      {";", "lambda"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<factor>",
     {{"program", "blank"},  {"var", "blank"},      {"begin", "blank"},
      {"end", "blank"},      {"integer", "blank"},  {"print", "blank"},
      {"a", "<identifier>"}, {"b", "<identifier>"}, {"c", "<identifier>"},
      {"d", "<identifier>"}, {"l", "<identifier>"}, {"f", "<identifier>"},
      {"0", "<number>"},     {"1", "<number>"},     {"2", "<number>"},
      {"3", "<number>"},     {"4", "<number>"},     {"5", "<number>"},
      {"6", "<number>"},     {"7", "<number>"},     {"8", "<number>"},
      {"9", "<number>"},     {"+", "lambda"},       {"-", "lambda"},
      {"*", "blank"},        {"/", "blank"},        {"(", "( <expr> )"},
      {")", "lambda"},       {"=", "blank"},        {":", "blank"},
      {";", "lambda"},       {",", "blank"},        {"\"", "blank"},
      {"$", "blank"}}},
    {"<number>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "blank"},
      {"b", "blank"},
      {"c", "blank"},
      {"d", "blank"},
      {"l", "blank"},
      {"f", "blank"},
      {"0", "<sign> <digit> <number'>"},
      {"1", "<sign> <digit> <number'>"},
      {"2", "<sign> <digit> <number'>"},
      {"3", "<sign> <digit> <number'>"},
      {"4", "<sign> <digit> <number'>"},
      {"5", "<sign> <digit> <number'>"},
      {"6", "<sign> <digit> <number'>"},
      {"7", "<sign> <digit> <number'>"},
      {"8", "<sign> <digit> <number'>"},
      {"9", "<sign> <digit> <number'>"},
      {"+", "<sign> <digit> <number'>"},
      {"-", "<sign> <digit> <number'>"},
      {"*", "lambda"},
      {"/", "lambda"},
      {"(", "blank"},
      {")", "lambda"},
      {"=", "blank"},
      {":", "blank"},
      {";", "lambda"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<number'>",
     {{"program", "blank"},
      {"var", "blank"},
      {"begin", "blank"},
      {"end", "blank"},
      {"integer", "blank"},
      {"print", "blank"},
      {"a", "blank"},
      {"b", "blank"},
      {"c", "blank"},
      {"d", "blank"},
      {"l", "blank"},
      {"f", "blank"},
      {"0", "<digit> <number'>"},
      {"1", "<digit> <number'>"},
      {"2", "<digit> <number'>"},
      {"3", "<digit> <number'>"},
      {"4", "<digit> <number'>"},
      {"5", "<digit> <number'>"},
      {"6", "<digit> <number'>"},
      {"7", "<digit> <number'>"},
      {"8", "<digit> <number'>"},
      {"9", "<digit> <number'>"},
      {"+", "lambda"},
      {"-", "lambda"},
      {"*", "lambda"},
      {"/", "lambda"},
      {"(", "blank"},
      {")", "lambda"},
      {"=", "blank"},
      {":", "blank"},
      {";", "lambda"},
      {",", "blank"},
      {"\"", "blank"},
      {"$", "blank"}}},
    {"<sign>", {{"program", "blank"}, {"var", "blank"},     {"begin", "blank"},
                {"end", "blank"},     {"integer", "blank"}, {"print", "blank"},
                {"a", "blank"},       {"b", "blank"},       {"c", "blank"},
                {"d", "blank"},       {"l", "blank"},       {"f", "blank"},
                {"0", "lambda"},      {"1", "lambda"},      {"2", "lambda"},
                {"3", "lambda"},      {"4", "lambda"},      {"5", "lambda"},
                {"6", "lambda"},      {"7", "lambda"},      {"8", "lambda"},
                {"9", "lambda"},      {"+", "+"},           {"-", "-"},
                {"*", "blank"},       {"/", "blank"},       {"(", "blank"},
                {")", "blank"},       {"=", "blank"},       {":", "blank"},
                {";", "blank"},       {",", "blank"},       {"\"", "blank"},
                {"$", "blank"}}},
    {"<digit>", {{"program", "blank"}, {"var", "blank"},     {"begin", "blank"},
                 {"end", "blank"},     {"integer", "blank"}, {"print", "blank"},
                 {"a", "blank"},       {"b", "blank"},       {"c", "blank"},
                 {"d", "blank"},       {"l", "blank"},       {"f", "blank"},
                 {"0", "0"},           {"1", "1"},           {"2", "2"},
                 {"3", "3"},           {"4", "4"},           {"5", "5"},
                 {"6", "6"},           {"7", "7"},           {"8", "8"},
                 {"9", "9"},           {"+", "blank"},       {"-", "blank"},
                 {"*", "blank"},       {"/", "blank"},       {"(", "blank"},
                 {")", "blank"},       {"=", "blank"},       {":", "blank"},
                 {";", "blank"},       {",", "blank"},       {"\"", "blank"},
                 {"$", "blank"}}},
    {"<letter>",
     {{"program", "blank"}, {"var", "blank"},     {"begin", "blank"},
      {"end", "blank"},     {"integer", "blank"}, {"print", "blank"},
      {"a", "a"},           {"b", "b"},           {"c", "c"},
      {"d", "d"},           {"l", "l"},           {"f", "f"},
      {"0", "blank"},       {"1", "blank"},       {"2", "blank"},
      {"3", "blank"},       {"4", "blank"},       {"5", "blank"},
      {"6", "blank"},       {"7", "blank"},       {"8", "blank"},
      {"9", "blank"},       {"+", "blank"},       {"-", "blank"},
      {"*", "blank"},       {"/", "blank"},       {"(", "blank"},
      {")", "blank"},       {"=", "blank"},       {":", "blank"},
      {";", "blank"},       {",", "blank"},       {"\"", "blank"},
      {"$", "blank"}}}};

// All reserved words and identifiers
unordered_set<string> reservedWords = {"program", "var",     "begin",
                                       "end",     "integer", "print"};
unordered_set<string> string_pool = {
    "\"value=\""
};

unordered_set<char> identifiers = {';', ',', ':', '.', '(', ')'};
unordered_map<string, bool> declaredVariables;

vector<string> tokenize(ifstream &file) {
    vector<string> tokens;
    string token;

    while (file >> token) {
        if (reservedWords.find(token) != reservedWords.end()) {
            tokens.push_back(token);
        } else if (string_pool.find(token) != string_pool.end()) {
            tokens.push_back("\"");
            tokens.push_back(token.substr(1,token.size() - 2));
            tokens.push_back("\"");
        } else {

            for (auto c : token) {
                string tmp;
                tmp += c;
                tokens.push_back(tmp);
            }
        }

    }

    return tokens;
}

vector<string> split(string s, char delim) {
    vector<string> split_str;
    string tmp;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] != delim) {
            tmp += s[i];
        } else {
            split_str.push_back(tmp);
            tmp.clear();
        }
    }
    split_str.push_back(tmp);
    return split_str;
};
bool isIdentifier(string &token) {

    if (!isalpha(token[0]))
        return false;

    // Remaining characters must be letters or digits
    for (int i = 1; i < token.length(); i++) {
        if (!isalnum(token[i]))
            return false;
    }

    return true;
}

int main() {

    ifstream file;
    file.open("finalf24.txt");
    if (file.fail()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    vector<string> tokens = tokenize(file);
    vector<string> stack = {"<prog>"};
    int i = 0;


    while (!stack.empty() && i < tokens.size()) {
        printStack(stack);
        string read = tokens[i];
        string top = stack.back();
        stack.pop_back();

        cout << "Read: " << read << ", Top: " << top << endl;

        /* if (top == "<identifier>") {
            if (isIdentifier(read)) {
                i++;
            } else {
                // for debugging only i will delete this later
                cerr << "Syntax error: Invalid identifier '" << read << "'" <<
        endl; return 1;
            }
            continue;
        }

        if (table.find(top) != table.end()) {
            if (table[top].find(read) != table[top].end()) {
                string production = table[top][read];

                // for debugging only i will delete this later
                cout << "Expanding production: " << production << endl;

                if (production == "lambda") {
                    continue;
                }

                vector<string> prodTokens = split(production, ' ');
                for (auto g = prodTokens.rbegin(); g != prodTokens.rend();++g) {
                    stack.push_back(*g);
                }
            } else {

                cerr << "Syntax error: Unexpected token '" << read
                     << "' for non-terminal '" << top << "'" << endl;
                return 1;
            }
        } */

        if (top == "end" && read == "end") {
            cout << "Input is ACCEPTED" << endl;
            return 0;
        }

        if (top == read) {
            // for debugging only i will delete this later
            cout << "Matched terminal: " << read << endl;
            i++;
            continue;
        }
    
        string prod = table[top][read];
        
        if (prod == "lambda") {
            continue;
        }
        if (prod == "blank") {
            cout << "Rejected" << endl;
            exit(1);
        }
        vector<string> prod_split = split(prod, ' ');
        for (int j = prod_split.size() - 1; j >= 0; j--) {
            stack.push_back(prod_split[j]);
            
        }
    }

    if (stack.empty() && i == tokens.size()) {
        cout << "Input is ACCEPTED" << endl;
    } else {
        cout << "Input is REJECTED: stack or tokens remaining" << endl;
    }

    return 0;
}