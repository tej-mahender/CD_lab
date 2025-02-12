%{
#include<stdio.h>
int result = 0;
%}
%%
[\n] {
result == 1?printf("Valid string\n"):printf("Invalid string\n"); result = 0;
}
^[a|b]*abb[a|b]*$ {result = 1;}
. {}
%%
int main() {
printf("Enter string: ");
yylex();
return 0;
}
