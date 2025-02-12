#include <stdio.h>
#include <string.h>
#include <ctype.h>

 int isKeyword(char *word) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
        "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
        "while"
    };
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0) // Compare the word with keywords
            return 1; // Return true if it matches any keyword
    }
    return 0; // Not a keyword
}

// Function to check if a string is a predefined function
int isPredefinedFunction(char *word) {
    return (strcmp(word, "main") == 0 || strcmp(word, "printf") == 0 || strcmp(word, "scanf") == 0);
}

int main() {
    char fileName[50]; // To store the input file name
    char currentChar, tokenBuffer[50]; // Current character and buffer for tokens
    int bufferIndex, lineNumber = 1, serialNumber = 0; // Index, line count, and serial count
    FILE *filePointer; // File pointer for reading the input file

    // Prompt user for file name and open the file
    printf("Enter the file name: ");
    scanf("%s", fileName);

    filePointer = fopen(fileName, "r");
    if (filePointer == NULL) { // Error handling if file cannot be opened
        printf("Error: Cannot open file %s\n", fileName);
        return 1;
    }

    // Display header for tokenized output
    printf("\n\n%-5s %-15s %-20s %-10s\n", "S.No", "Token", "Lexeme", "Line No");
    printf("------------------------------------------------------------\n");

    // Read file character by character
    while ((currentChar = fgetc(filePointer)) != EOF) {
        // Handle identifiers and keywords
        if (isalpha(currentChar)) {
            bufferIndex = 0;
            tokenBuffer[bufferIndex++] = currentChar;

            // Read subsequent alphanumeric characters
            while (isalnum(currentChar = fgetc(filePointer))) {
                tokenBuffer[bufferIndex++] = currentChar;
            }
            tokenBuffer[bufferIndex] = '\0'; // Null-terminate the string
            ungetc(currentChar, filePointer); // Push back the last read character

            // Determine if the token is a keyword, function, or identifier
            if (isKeyword(tokenBuffer)) {
                printf("%-5d %-15s %-20s %-10d\n", ++serialNumber, "keyword", tokenBuffer, lineNumber);
            } else if (isPredefinedFunction(tokenBuffer)) {
                printf("%-5d %-15s %-20s %-10d\n", ++serialNumber, "function", tokenBuffer, lineNumber);
            } else {
                printf("%-5d %-15s %-20s %-10d\n", ++serialNumber, "identifier", tokenBuffer, lineNumber);
            }
        }
        // Handle numbers
        else if (isdigit(currentChar)) {
            bufferIndex = 0;
            tokenBuffer[bufferIndex++] = currentChar;

            // Read subsequent digits
            while (isdigit(currentChar = fgetc(filePointer))) {
                tokenBuffer[bufferIndex++] = currentChar;
            }
            tokenBuffer[bufferIndex] = '\0'; // Null-terminate the string
           ungetc(currentChar, filePointer); // Push back the last read character

            printf("%-5d %-15s %-20s %-10d\n", ++serialNumber, "number", tokenBuffer, lineNumber);
        }
        // Handle parentheses
        else if (currentChar == '(' || currentChar == ')') {
            printf("%-5d %-15s %-20c %-10d\n", ++serialNumber, "parenthesis", currentChar, lineNumber);
        }
        // Handle braces
        else if (currentChar == '{' || currentChar == '}') {
            printf("%-5d %-15s %-20c %-10d\n", ++serialNumber, "brace", currentChar, lineNumber);
        }
        // Handle array index brackets
        else if (currentChar == '[' || currentChar == ']') {
            printf("%-5d %-15s %-20c %-10d\n", ++serialNumber, "array index", currentChar, lineNumber);
        }
        // Handle punctuation like commas and semicolons
        else if (currentChar == ',' || currentChar == ';') {
            printf("%-5d %-15s %-20c %-10d\n", ++serialNumber, "punctuation", currentChar, lineNumber);
        }
        // Handle string literals
        else if (currentChar == '"') {
            bufferIndex = 0;
            while ((currentChar = fgetc(filePointer)) != '"' && currentChar != EOF) {
                tokenBuffer[bufferIndex++] = currentChar;
            }
            tokenBuffer[bufferIndex] = '\0'; // Null-terminate the string
            printf("%-5d %-15s %-20s %-10d\n", ++serialNumber, "string", tokenBuffer, lineNumber);
        }
        // Ignore spaces and tabs
        else if (currentChar == ' ' || currentChar == '\t') {
            continue;
        }
        // Increment line number on newline
        else if (currentChar == '\n') {
            ++lineNumber;
        }
        // Handle operators
        else if (strchr("+-*/=%", currentChar)) {
            printf("%-5d %-15s %-20c %-10d\n", ++serialNumber, "operator", currentChar, lineNumber);
        }
    }

    fclose(filePointer); // Close the file
    return 0;
}
