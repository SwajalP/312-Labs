#ifndef PROGRAM8_H
#define PROGRAM8_H

#include <string>
#include <map>

extern std::map<std::string, int> variables;

int eval_expr();
void pa8();
void process_statement();
void handle_text();

#endif