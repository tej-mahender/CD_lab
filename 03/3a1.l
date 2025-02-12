%{
#include <stdio.h>
#include <stdlib.h>
char* word[] = {
    "keyword", "identifier", "operator", "preprocessor", "comment","invalid literal", "reserved", "number", "string"
};
void display(int);
%}
keyword    "int"|"char"|"short"|"void"|"long"|"if"|"else"|"case"|"for"|"do"|"while"|"break"|"auto"|"static"|"const"|"enum"|"struct";
reserved   "main"|"FILE"|"printf"|"scanf"|"puts"|"putc"|"getc"|"pow";
comments   "//".*|"/\*".*"\*/";
operator   "\."|"\{"|"\}"|"\("|"\)"|\["|\]"|"->"|"\+"|"\-"|"\*"|"/"|"\+"|"\-"|"\*"|"/"|"%"|"&"|"!"|"="|"&&"|"||"|"-="|"+="|"/="|"*="|"%="|">>"|"<<";
preprocessor  "#".*;
string    "\"[^\"]*\"";
identifier  [a-zA-Z_][a-zA-Z0-9_]*;
number      [0-9]+(\.[0-9]*)?;

%%

{comments}       { display(4); }
{preprocessor}   { display(3); }
{reserved}       { display(6); }
{keyword}        { display(0); }
{operator}       { display(2); }
{string}         { display(8); }
{identifier}     { display(1); }
{number}         { display(7); }
[ \t\n]          { /* Ignore whitespace */ }
.                { display(5); }

%%

void display(int n) {
    printf("%s --> %s\n", yytext, word[n]);
}

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            printf("Could not open %s\n", argv[1]);
            exit(0);
        }
    }
    yylex();
    return 0;
}
