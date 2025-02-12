%{
#include<stdio.h>
int result = 0;
%}
%%
[\n] {
result == 1?printf("Valid string\n"):printf("Invalid string\n");
}
^a[a|b]*$ {result = 1;}
. result = 0;
%%
int main() {
printf("Enter string: ");
yylex();
return 0;
}
