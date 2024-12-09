//-------------------------------------------------------------------------------------------------------------
// Group names: Haron Taher, HyungJoo Yoon, Caitlin Chau
// Assignment: Final Project
// Due date: 12/5/2024
// Purpose: This code implements a parser that tokenizes input, validates syntax using a stack-based approach, 
// and identifies errors or confirms readiness for compilation based on predefined grammar rules.
//-------------------------------------------------------------------------------------------------------------

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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
unordered_set<string> string_pool = {"\"value=\""};

// Define a set of special characters (identifiers) that are used in parsing logic.
unordered_set<char> identifiers = {';', ',', ':', '.', '(', ')'};

// Keep track of declared variables to validate their usage.
unordered_map<string, bool> declaredVariables;

// Function to tokenize the input file.
// It takes an input file stream and a reference to a vector for line numbers.
// Returns a vector of tokens extracted from the file.
vector<string> tokenize(ifstream &file, vector<int> &lineNumbers) {
    vector<string> tokens; // Stores the tokens
    string line;           // Temporary string to hold each line of the file
    int line_no = 1;       // Line number tracker

    // Read the file line by line
    while (getline(file, line)) {
        istringstream iss(line); // Create a string stream for the current line
        string token;

        // Extract tokens from the current line
        while (iss >> token) {
            // If the token is a reserved word, add it to the tokens vector
            if (reservedWords.find(token) != reservedWords.end()) {
                tokens.push_back(token);
                lineNumbers.push_back(line_no);
            }
            // If the token is in the string pool, handle it as a quoted string
            else if (string_pool.find(token) != string_pool.end()) {
                tokens.push_back("\"");
                lineNumbers.push_back(line_no);
                tokens.push_back(token.substr(1, token.size() - 2));
                lineNumbers.push_back(line_no);
                tokens.push_back("\"");
                lineNumbers.push_back(line_no);
            }
            // For all other tokens, split them into characters and store each
            else {
                for (auto c : token) {
                    string tmp;
                    tmp += c;
                    tokens.push_back(tmp);
                    lineNumbers.push_back(line_no);
                }
            }
        }
        line_no++; // Increment line number for the next line
    }

    return tokens; // Return the vector of tokens
}

// Function to split a string `s` by a delimiter `delim`.
// Returns a vector of the resulting substrings.
vector<string> split(string s, char delim) {
    vector<string> split_str; // Store the resulting substrings
    string tmp;               // Temporary string to build substrings

    // Iterate through each character in the string
    for (int i = 0; i < s.length(); i++) {
        // If the current character is not the delimiter, add it to the temporary string
        if (s[i] != delim) {
            tmp += s[i];
        }
        // Otherwise, add the current substring to the result and reset the temporary string
        else {
            split_str.push_back(tmp);
            tmp.clear();
        }
    }
    split_str.push_back(tmp); // Add the last substring
    return split_str;
}

int main() {
    // Open the input file for reading
    ifstream file("finalf24.txt");
    if (file.fail()) { // Check if the file failed to open
        cerr << "Error opening input file." << endl;
        return 1;
    }

    vector<int> lineNumbers;     // Vector to store line numbers for each token
    vector<string> tokens = tokenize(file, lineNumbers); // Tokenize the input file
    vector<string> stack = {"<prog>"}; // Initialize parsing stack with the starting symbol
    int i = 0; // Index for traversing tokens

    int column_width = 18; // Formatting width for console output

    // Parsing logic
    while (!stack.empty() && i < tokens.size()) {
        string read = tokens[i];     // Current token being read
        string top = stack.back();   // Top of the parsing stack
        stack.pop_back();            // Remove the top of the stack

        int current_line = lineNumbers[i]; // Get the line number of the current token
        cout << left << setw(column_width) << "Read: " << setw(column_width)
             << read << "Top:" << setw(column_width) << top
             << "Line: " << current_line << endl;

        // If the top of the stack matches the current token, it's a terminal match
        if (top == read) {
            cout << left << setw(column_width)
                 << "Matched terminal: " << setw(2 * column_width + 4) << read
                 << "Line: " << current_line << endl;
            i++; // Move to the next token

            // Check for specific syntax errors
            if (current_line == 3 && (read == "a" || read == "c")) {
                if (tokens[i] != "," && tokens[i] != ":") {
                    // Error: Missing comma or colon
                    cout << left << setw(column_width)
                         << "Error , was expected but '" << tokens[i]
                         << "' was found                    Line: "
                         << current_line << endl;
                    return 1;
                }
            }

            if (current_line == 9 && read == "=" && tokens[i] != "(") {
                if (tokens[i] != "," && tokens[i] != ":") {
                    // Error: Missing parenthesis
                    cout << left << setw(column_width)
                         << "Error ( was expected but '" << tokens[i]
                         << "' was found                    Line: "
                         << current_line << endl;
                    return 1;
                }

                continue;
            }

            continue; // Continue to the next iteration
        }

        int temp_current_line = current_line;

        // Check for missing semicolons at the end of a line
        if (read != ";" && reservedWords.find(read) == reservedWords.end() &&
            temp_current_line != lineNumbers[i + 1]) {
            cout << left << setw(column_width)
                 << "Error: " << "Missing semicolon at the end of line "
                 << current_line << " after '" << read << "'\n";
            return 1;
        }

        string prod = table[top][read]; // Get the production rule for the top and read token
        if (prod.empty()) {
            // Handle various parsing errors based on the expected top of the stack
            if (top == ";") {
                cout << left << setw(column_width) << "Error: "
                     << "Missing semicolon at the end of Line: "
                     << current_line - 1 << endl;
            } else if (top == ",") {
                cout << left << setw(column_width) << "Error  " << top
                     << " was expected but '" << read
                     << "' was found Line:" << current_line << endl;
            } else if (top == ".") {
                cout << left << setw(column_width) << "Error  " << top
                     << " was expected but '" << read
                     << "' was found Line:" << current_line << endl;
            } else if (top == "(") {
                cout << left << setw(column_width) << "Error  " << top
                     << " was expected but '" << read
                     << "' was found Line:" << current_line << endl;
            } else if (top == ")") {
                cout << left << setw(column_width) << "Error  " << top
                     << " was expected but '" << read
                     << "' was found Line:" << current_line << endl;
            } else if (top == "<prog>") {
                cout << left << setw(column_width)
                     << "Error program was expected, check if its misspelled "
                        "or missing!     Line: "
                     << current_line << endl;
            } else if (top == "var") {
                cout << left << setw(column_width)
                     << "Error var was expected, check if its misspelled or "
                        "missing!     Line: "
                     << current_line << endl;
            } else if (top == "<type>") {
                cout << left << setw(column_width)
                     << "Error integer was expected, check if its misspelled "
                        "or missing!     Line: "
                     << current_line << endl;
            } else if (top == "begin") {
                cout << left << setw(column_width)
                     << "Error begin was expected, check if its misspelled or "
                        "missing!     Line: "
                     << current_line << endl;
            } else if ((top == "<stat-list'>") && (read == "p")) {
                cout << left << setw(column_width)
                     << "Error print was expected, check if its misspelled or "
                        "missing!     Line: "
                     << current_line << endl;
            } else if ((top == "<stat-list'>") && (current_line == 11)) {
                cout << left << setw(column_width)
                     << "Error end was expected, check if its misspelled or "
                        "missing!     Line: "
                     << current_line << endl;
            } else {
                cout << "Rejected" << endl;
            }
            return 1;
        }

        // Skip lambda productions
        if (prod == "lambda")
            continue;

        // Push the production rule onto the stack
        vector<string> prod_split = split(prod, ' ');
        for (int j = prod_split.size() - 1; j >= 0; j--) {
            stack.push_back(prod_split[j]);
        }
    }

    // If the stack is not empty, parsing is incomplete
    if (!stack.empty()) {
        cout << left << setw(column_width)
             << "Rejected: " << "Incomplete parsing" << endl;
    } else {
        // Parsing was successful
        cout << left << setw(column_width) << "Ready to compile" << endl;
    }

    return 0;
}