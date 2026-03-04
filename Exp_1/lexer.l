%{
#include <stdio.h>
%}

/* Rules Section */
%%
[0-9]+                     { printf("NUMBER: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*     { printf("IDENTIFIER: %s\n", yytext); }
[ \t\n]+                   ;   /* Ignore whitespace */
.                          { printf("SYMBOL: %s\n", yytext); }
%%

/* User Code Section */
int main() {
    printf("Enter an expression:\n");
    yylex();
    return 0;
}