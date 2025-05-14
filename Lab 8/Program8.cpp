#include <iostream>
#include <string>
#include <map>
#include "Parse.h"

using namespace std;

static map<string, int> symtab;

void handle_text() {
      read_next_token();


    string content = next_token();

    if (content.front() == '"' && content.back() == '"') {
         content = content.substr(1, content.size() - 2);

    }
  cout << content;
}

int eval_expr() {
    read_next_token();
      string tok = next_token();

    if (next_token_type == NUMBER) {
     return stoi(tok);
    }

    if (next_token_type == NAME) {
        if (symtab.count(tok)) {
            return symtab[tok];
        } else {
         cout << "variable " << tok << " not declared" << endl;
            return 0;
        }
    }




    if (tok == "+") return eval_expr() + eval_expr();
    if (tok == "-") return eval_expr() - eval_expr();
    if (tok == "*") return eval_expr() * eval_expr();
    if (tok == "/") {
         int left = eval_expr();    

            int right = eval_expr();

        if (right == 0) {
             cout << "division by zero" << endl;
                 return 0;
        }
         return left / right;
    }
    if (tok == "%") {
           int left = eval_expr();
        int right = eval_expr();
         if (right == 0) {
            cout << "modulus by zero" << endl;
             return 0;
        }
        return left % right;
    }
    if (tok == "&&") return (eval_expr() && eval_expr()) ? 1 : 0;
    if (tok == "||") return (eval_expr() || eval_expr()) ? 1 : 0;
    if (tok == "<") return (eval_expr() < eval_expr()) ? 1 : 0;
    if (tok == ">") return (eval_expr() > eval_expr()) ? 1 : 0;
    if (tok == "<=") return (eval_expr() <= eval_expr()) ? 1 : 0;
    if (tok == ">=") return (eval_expr() >= eval_expr()) ? 1 : 0;
    if (tok == "==") return (eval_expr() == eval_expr()) ? 1 : 0;
    if (tok == "!=") return (eval_expr() != eval_expr()) ? 1 : 0;
    if (tok == "~") return -eval_expr();
    if (tok == "!") return (eval_expr() == 0) ? 1 : 0;



    cout << "unknown token: " << tok << endl;
    return 0;

}

void process_statement() {
    if (next_token_type == END) return;

    string cmd = next_token();

    if (cmd == "//") {
        skip_line();
    } 
    else if (cmd == "text") {
        handle_text();
    } 
    else if (cmd == "output") {
        cout << eval_expr();  // no newline here, so output and text share the same line
    } 
    else if (cmd == "var") {
        read_next_token();
        string var = next_token();
        int val = eval_expr();
        if (symtab.count(var)) {
            cout << "variable " << var << " incorrectly re-initialized" << endl;
        }
        symtab[var] = val;
    }
    else if (cmd == "set") {
            read_next_token();
         string var = next_token();
          int val = eval_expr();
         if (!symtab.count(var)) {
             cout << "variable " << var << " not declared" << endl;
        }
        symtab[var] = val;
    }
}

void pa8() {
    symtab.clear();
    read_next_token();

    while (next_token_type != END) {
            process_statement();

        read_next_token();


    }
}
