#include "Scanner.h"

FILE *errorsFile;

void match(TokenType t);

void parse_PROGRAM();
void parse_DECLARATIONS();
void parse_DECLARATIONS_A();
void parse_DECLARATION();
void parse_STATEMENTS();
void parse_STATEMENTS_A();
void parse_STATEMENT();
void parse_VARIABLES_LIST();
void parse_VARIABLES_LIST_A();
void parse_TYPE();
void parse_VARIABLE();
void parse_VARIABLE_A();
void parse_CONDITION();
void parse_RECEIVER();
void parse_RECEIVER_A();
void parse_EXPRESSION();
void parse_EXPRESSION_A();

bool follow_PROGRAM(TokenType type);
bool follow_DECLARATIONS_A(TokenType type);
bool follow_VARIABLES_LIST_A(TokenType type);
bool follow_VARIABLE(TokenType type);
bool follow_VARIABLE(TokenType type);
bool follow_TYPE(TokenType type);
bool follow_STATEMENTS_A(TokenType type);
bool follow_EXPRESSION(TokenType type);
bool follow_EXPRESSION_A(TokenType type);
bool follow_RECEIVER_A(TokenType type);

int getLineNumberAnyway();
printResult(const char* result, const char* rule, int line);
bool OpenFileOut(const char* path);
