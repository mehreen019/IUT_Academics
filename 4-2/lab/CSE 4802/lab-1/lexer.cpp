#include<bits/stdc++.h>

using namespace std;

struct Token {
    string type;
    string lexeme;
    int line;
    int col;
};

vector<Token> tokens;

int kwCount = 0, idCount = 0, intCount = 0, floatCount = 0;
int arithCount = 0, relCount = 0, logCount = 0, bitCount = 0;
int assignCount = 0, incrCount = 0, delimCount = 0, strCount = 0, charCount = 0;

map<string, pair<int,int>> symTable;

set<string> keywords = {
    "int","float","double","char","bool","void",
    "if","else","while","for","do","return",
    "break","continue","switch","case","default",
    "struct","class","new","delete","true","false","string","cout","endl","cin"
};

bool isLetter(char c){ return isalpha(c) || c == '_'; }
bool isDigit(char c){ return isdigit(c); }

bool inBlockComment = false;

void tokenize(const string& src, int lineNum) {
    int i = 0;
    int n = src.size();

    if (n > 0 && src[0] == '#') return;

    while(i < n) {
        if(isspace(src[i])){ i++; continue; }

        if(inBlockComment) {
            if(i+1 < n && src[i] == '*' && src[i+1] == '/') {
                inBlockComment = false;
                i += 2;
            } else {
                i++;
            }
            continue;
        }

        if(i+1 < n && src[i] == '/' && src[i+1] == '*') {
            inBlockComment = true;
            i += 2;
            continue;
        }

        if(i+1 < n && src[i] == '/' && src[i+1] == '/') break;

        int col = i + 1;

        if(src[i] == '"') {
            string lex = "\"";
            i++;
            while (i < n && src[i] != '"') { lex += src[i]; i++; }
            lex += "\""; i++;
            tokens.push_back({"STRING_CONST", lex, lineNum, col});
            strCount++;
            continue;
        }

        if(src[i] == '\'') {
            string lex = "'";
            i++;
            while (i < n && src[i] != '\'') { lex += src[i]; i++; }
            lex += "'"; i++;
            tokens.push_back({"CHAR_CONST", lex, lineNum, col});
            charCount++;
            continue;
        }

        if(i+1 < n) {
            if (src[i] == '&' && src[i+1] == '&') { tokens.push_back({"LOGICAL_OP",    "&&", lineNum, col}); logCount++;    i+=2; continue; }
            if (src[i] == '|' && src[i+1] == '|') { tokens.push_back({"LOGICAL_OP",    "||", lineNum, col}); logCount++;    i+=2; continue; }
            if (src[i] == '=' && src[i+1] == '=') { tokens.push_back({"RELATIONAL_OP", "==", lineNum, col}); relCount++;    i+=2; continue; }
            if (src[i] == '!' && src[i+1] == '=') { tokens.push_back({"RELATIONAL_OP", "!=", lineNum, col}); relCount++;    i+=2; continue; }
            if (src[i] == '>' && src[i+1] == '=') { tokens.push_back({"RELATIONAL_OP", ">=", lineNum, col}); relCount++;    i+=2; continue; }
            if (src[i] == '<' && src[i+1] == '=') { tokens.push_back({"RELATIONAL_OP", "<=", lineNum, col}); relCount++;    i+=2; continue; }
            if (src[i] == '+' && src[i+1] == '+') { tokens.push_back({"INCREMENT_OP",  "++", lineNum, col}); incrCount++;   i+=2; continue; }
            if (src[i] == '-' && src[i+1] == '-') { tokens.push_back({"DECREMENT_OP",  "--", lineNum, col}); incrCount++;   i+=2; continue; }
            if (src[i] == '+' && src[i+1] == '=') { tokens.push_back({"ASSIGNMENT_OP", "+=", lineNum, col}); assignCount++; i+=2; continue; }
            if (src[i] == '-' && src[i+1] == '=') { tokens.push_back({"ASSIGNMENT_OP", "-=", lineNum, col}); assignCount++; i+=2; continue; }
            if (src[i] == '*' && src[i+1] == '=') { tokens.push_back({"ASSIGNMENT_OP", "*=", lineNum, col}); assignCount++; i+=2; continue; }
            if (src[i] == '/' && src[i+1] == '=') { tokens.push_back({"ASSIGNMENT_OP", "/=", lineNum, col}); assignCount++; i+=2; continue; }
            if (src[i] == '<' && src[i+1] == '<') { tokens.push_back({"BITWISE_OP",    "<<", lineNum, col}); bitCount++;    i+=2; continue; }
            if (src[i] == '>' && src[i+1] == '>') { tokens.push_back({"BITWISE_OP",    ">>", lineNum, col}); bitCount++;    i+=2; continue; }
        }

        if(src[i] == '+') { tokens.push_back({"ARITHMETIC_OP", "+", lineNum, col}); arithCount++; i++; continue; }
        if(src[i] == '-') { tokens.push_back({"ARITHMETIC_OP", "-", lineNum, col}); arithCount++; i++; continue; }
        if(src[i] == '*') { tokens.push_back({"ARITHMETIC_OP", "*", lineNum, col}); arithCount++; i++; continue; }
        if(src[i] == '/') { tokens.push_back({"ARITHMETIC_OP", "/", lineNum, col}); arithCount++; i++; continue; }
        if(src[i] == '%') { tokens.push_back({"ARITHMETIC_OP", "%", lineNum, col}); arithCount++; i++; continue; }
        if(src[i] == '>') { tokens.push_back({"RELATIONAL_OP", ">", lineNum, col}); relCount++;   i++; continue; }
        if(src[i] == '<') { tokens.push_back({"RELATIONAL_OP", "<", lineNum, col}); relCount++;   i++; continue; }
        if(src[i] == '!') { tokens.push_back({"LOGICAL_OP",    "!", lineNum, col}); logCount++;   i++; continue; }
        if(src[i] == '&') { tokens.push_back({"BITWISE_OP",    "&", lineNum, col}); bitCount++;   i++; continue; }
        if(src[i] == '|') { tokens.push_back({"BITWISE_OP",    "|", lineNum, col}); bitCount++;   i++; continue; }
        if(src[i] == '^') { tokens.push_back({"BITWISE_OP",    "^", lineNum, col}); bitCount++;   i++; continue; }
        if(src[i] == '~') { tokens.push_back({"BITWISE_OP",    "~", lineNum, col}); bitCount++;   i++; continue; }
        if(src[i] == '=') { tokens.push_back({"ASSIGNMENT_OP", "=", lineNum, col}); assignCount++;i++; continue; }

        string delims = ";,(){}[]";
        if(delims.find(src[i]) != string::npos) {
            tokens.push_back({"DELIMITER", string(1,src[i]), lineNum, col});
            delimCount++; i++; continue;
        }

        if(isLetter(src[i])) {
            string lex = "";
            while (i < n && (isLetter(src[i]) || isDigit(src[i]))) {
                lex += src[i]; i++;
            }
            if (keywords.count(lex)) {
                tokens.push_back({"KEYWORD", lex, lineNum, col});
                kwCount++;
            } else {
                tokens.push_back({"IDENTIFIER", lex, lineNum, col});
                idCount++;
                if (symTable.count(lex)) {
                    symTable[lex].first++;
                } else {
                    symTable[lex] = {1, lineNum};
                }
            }
            continue;
        }

        if(isDigit(src[i])) {
            string lex = "";
            bool isFloat = false;
            while(i < n && isDigit(src[i])) { lex += src[i]; i++; }
            if(i < n && src[i] == '.' && i+1 < n && isDigit(src[i+1])) {
                isFloat = true;
                lex += src[i]; i++;
                while (i < n && isDigit(src[i])) { lex += src[i]; i++; }
            }
            else if(i < n && src[i] == '.' && (i+1 >= n || !isDigit(src[i+1]))) {
                lex += src[i]; i++;
                cout << "LEXICAL ERROR at line " << lineNum << ", col " << col << ": invalid numerical format '" << lex << "'\n";
                continue;
            }

            if (i < n && isLetter(src[i])) {
                while (i < n && (isLetter(src[i]) || isDigit(src[i]))) { lex += src[i]; i++; }
                cout << "LEXICAL ERROR at line " << lineNum << ", col " << col << ": invalid identifier '" << lex << "'\n";
                continue;
            }

            if (isFloat) {
                tokens.push_back({"FLOAT_CONST", lex, lineNum, col});
                floatCount++;
            } else {
                tokens.push_back({"INTEGER_CONST", lex, lineNum, col});
                intCount++;
            }
            continue;
        }

        cout << "LEXICAL ERROR at line " << lineNum << ", col " << col << ": unknown character '" << src[i] << "'\n";
        i++;
    }
}


int main() {
    ifstream file("input2.txt");
    if (!file.is_open()) {
        cout << "Error: cannot open input2.txt\n";
        return 1;
    }

    string line;
    int lineNum = 1;
    while (getline(file, line)) {
        tokenize(line, lineNum);
        lineNum++;
    }
    file.close();

    cout << "====== TOKEN STREAM ======\n";
    for (auto& t : tokens) {
        cout << "<" << t.type << ", " << t.lexeme << "> @ line " << t.line << ", col " << t.col << "\n";
    }

    int total = kwCount + idCount + intCount + floatCount + strCount + charCount
              + arithCount + relCount + logCount + bitCount
              + assignCount + incrCount + delimCount;

    cout << "\n====== STATISTICS ======\n";
    cout << "Total Tokens      : " << total        << "\n";
    cout << "Keywords          : " << kwCount       << "\n";
    cout << "Identifiers       : " << idCount       << "\n";
    cout << "Integer Constants : " << intCount      << "\n";
    cout << "Float Constants   : " << floatCount    << "\n";
    cout << "String Constants  : " << strCount      << "\n";
    cout << "Char Constants    : " << charCount     << "\n";
    cout << "Arithmetic Ops    : " << arithCount    << "\n";
    cout << "Relational Ops    : " << relCount      << "\n";
    cout << "Logical Ops       : " << logCount      << "\n";
    cout << "Bitwise Ops       : " << bitCount      << "\n";
    cout << "Assignment Ops    : " << assignCount   << "\n";
    cout << "Increment/Decr Ops: " << incrCount     << "\n";
    cout << "Delimiters        : " << delimCount    << "\n";

    cout << "\n====== SYMBOL TABLE ======\n";
    cout << "Identifier       | Count | First Line\n";
    cout << "-----------------+-------+-----------\n";
    for (auto& entry : symTable) {
        cout << entry.first;
        for (int s = entry.first.size(); s < 17; s++) cout << " ";
        cout << "| " << entry.second.first << "     | " << entry.second.second << "\n";
    }

    ofstream outFile("symbol_table.txt");
    if (outFile.is_open()) {
        outFile << "Identifier       | Count | First Line\n";
        outFile << "-----------------+-------+-----------\n";
        for (auto& entry : symTable) {
            outFile << entry.first;
            for (int s = entry.first.size(); s < 17; s++) outFile << " ";
            outFile << "| " << entry.second.first << "     | " << entry.second.second << "\n";
        }
        outFile.close();
        cout << "\nSymbol table exported to symbol_table.txt\n";
    } else {
        cout << "\nError: could not write symbol_table.txt\n";
    }

    return 0;
}
