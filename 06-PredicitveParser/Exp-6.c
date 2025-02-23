#include <stdio.h>
#include <string.h>

char input[20];
int len, ln = 0, err = 0;

void match(char);
void E();
void E1();
void T();
void T1();
void F();

void E() {
    T();
    E1();
}

void E1() {
    if (*input == '+') {
        match('+');
        T();
        E1();
    }
}

void T() {
    F();
    T1();
}

void T1() {
    if (*input == '*') {
        match('*');
        F();
        T1();
    }
}

void F() {
    if (*input == '(') {
        match('(');
        E();
        match(')');
    }
    else 
        match('i');
}

void match(char expected) {
    if (*input == expected) {
        printf("\n%s        popped:  %c", input, expected);
        ln++;
        strcpy(input, &input[1]);  // Move input forward
    }
    else {
        printf("\nSyntax Error: Expected '%c' but found '%c'", expected, *input);
        err++;
    }
}
int main() {
    printf("Enter the Input: ");
    gets(input);
    len = strlen(input);
    input[len] = '$';
    input[len + 1] = '\0';
    E();
    if (err == 0 && ln == len)
        printf("\n\nString parsed successfully!!!\n");
    else
        printf("\n\nString not parsed successfully. Errors encountered or invalid input.\n\n");
    return 0;
}
