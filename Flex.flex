%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int INTEGER = 0;
int FLOAT = 0;
int IDENTIFIER = 0;
int OPERATOR = 0;
int Comparison = 0;
int YES = 0;
int ADDITION = 0;
int NO = 0;
int RETURN = 0;
int READ = 0;
int WRITE = 0;
int STOP = 0;
int CARRY_ON = 0;
int DURING = 0;
int OPEN = 0;
int CLOSE = 0;
int SEPARATOR = 0;

void printToken(const char* category, const char* value) {
    printf("Token: %-20s Value: %s\n", category, value);
}

%}

Integer     [0-9]+
Float       [0-9]+"."[0-9]+
Identifier  [a-zA-Z][a-zA-Z0-9]*
Operators   [-+*/]
Comparison  [<>]=
YES         "if"
ADDITION    "else-if"
NO          "else"
RETURN      "return"
READ        "print"
WRITE       "input"
STOP        "break"
CARRY_ON    "continue"
DURING      "while"

%%

{Operators}     { OPERATOR++; printToken("Operator", yytext); }
{Integer}       { INTEGER++; printToken("Integer", yytext); }
{Float}         { FLOAT++; printToken("Float", yytext); }
{Comparison}    { printToken("Comparison Operator", yytext); }
"int"           { IDENTIFIER++; printToken("Datatype", yytext); }
"float"         { IDENTIFIER++; printToken("Datatype", yytext); }
"if"            { YES++; printToken("Keyword", yytext); }
"else-if"       { ADDITION++; printToken("Keyword", yytext); }
"else"          { NO++; printToken("Keyword", yytext); }
"return"        { RETURN++; printToken("Keyword", yytext); }
"print"         { READ++; printToken("Keyword", yytext); }
"input"         { WRITE++; printToken("Keyword", yytext); }
"break"         { STOP++; printToken("Keyword", yytext); }
"continue"      { CARRY_ON++; printToken("Keyword", yytext); }
"while"         { DURING++; printToken("Keyword", yytext); }
.               { /* Ignore other characters */ }

%%

int yywrap() { return 1; }

int main() {
    yylex();
    printf("\nStatistics:\n");
    printf("OPERATORS: %d\n", OPERATOR);
    printf("INTEGERS: %d\n", INTEGER);
    printf("FLOATS: %d\n", FLOAT);
    printf("IDENTIFIERS: %d\n", IDENTIFIER);
    printf("DATATYPES: %d\n", IDENTIFIER);
    printf("KEYWORDS: %d\n", YES + ADDITION + NO + RETURN + READ + WRITE + STOP + CARRY_ON + DURING);
    printf("IF keyword: %d\n", YES);
    printf("ELSE IF keyword: %d\n", ADDITION);
    printf("ELSE keyword: %d\n", NO);
    printf("RETURN keyword: %d\n", RETURN);
    printf("READ keyword: %d\n", READ);
    printf("WRITE keyword: %d\n", WRITE);
    printf("STOP keyword: %d\n", STOP);
    printf("CARRY_ON keyword: %d\n", CARRY_ON);
    printf("DURING keyword: %d\n", DURING);
    printf("SPECIAL SYMBOLS: %d\n", OPEN + CLOSE + SEPARATOR);

    FILE *filePointer;
    filePointer = fopen("input.zen", "r");
    yyin = filePointer;
    yyin = fopen("input.zen", "r");
    yyout = freopen("Tokens.txt", "w", stdout);
    yylex();
    fclose(yyin);

    return 0;
}
