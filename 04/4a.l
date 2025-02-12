%{
#include <stdio.h>
int vowel_count = 0, consonant_count = 0;
%}
%%
[aAeEiIoOuU] {vowel_count++;}
[a-zA-Z] {consonant_count++;}
. ;
%%
int yywrap() {return 1;}
int main() {
yylex();
consonant_count -= vowel_count;
printf("Number of vowels: %d\n Number of consonants: %d\n ", vowel_count, consonant_count);
return 0;
}
