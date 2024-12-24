#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function Prototypes
int convertRomanToDecimal(const char *roman);
void decimalToWords(int num, char *words);
void readFile(const char *filename, char expressions[][100], int *count);
void writeFile(const char *filename, char results[][100], int count);
int performOperation(int operand1, int operand2, char operation);

// Main Function
int main() {
    char expressions[100][100];  // Store expressions like "M + MM"
    char results[100][100];
    int count = 0;

    // Step 1: Read expressions from input file
    readFile("input.txt", expressions, &count);

    // Step 2: Process each expression
    for (int i = 0; i < count; i++) {
        char roman1[20], roman2[20], operation;
        int operand1, operand2, result;

        // Parse the expression (e.g., "M + MM")
        sscanf(expressions[i], "%s %c %s", roman1, &operation, roman2);

        // Convert Roman numerals to decimals
        operand1 = convertRomanToDecimal(roman1);
        operand2 = convertRomanToDecimal(roman2);

        // Perform the operation
        result = performOperation(operand1, operand2, operation);

        // Convert result to words
        char words[100];
        decimalToWords(result, words);

        // Store result
        sprintf(results[i], "%s %c %s = %d = %s", roman1, operation, roman2, result, words);
    }

    // Step 3: Write results to output file
    writeFile("output.txt", results, count);

    printf("Calculation completed! Check output.txt for results.\n");
    return 0;
}

// Function to Convert Roman Numeral to Decimal
int convertRomanToDecimal(const char *roman) {
    int total = 0, current, next;
    int length = strlen(roman);

    for (int i = 0; i < length; i++) {
        switch (roman[i]) {
            case 'I': current = 1; break;
            case 'V': current = 5; break;
            case 'X': current = 10; break;
            case 'L': current = 50; break;
            case 'C': current = 100; break;
            case 'D': current = 500; break;
            case 'M': current = 1000; break;
            default: current = 0; // Invalid character
        }

        if (i + 1 < length) {
            switch (roman[i + 1]) {
                case 'I': next = 1; break;
                case 'V': next = 5; break;
                case 'X': next = 10; break;
                case 'L': next = 50; break;
                case 'C': next = 100; break;
                case 'D': next = 500; break;
                case 'M': next = 1000; break;
                default: next = 0;
            }
            if (current < next) {
                total -= current;
            } else {
                total += current;
            }
        } else {
            total += current;
        }
    }

    return total;
}

// Function to Convert Decimal to Words
void decimalToWords(int num, char *words) {
    char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *hundred = "Hundred";
    char *thousand = "Thousand";

    if (num == 0) {
        strcpy(words, "Zero");
        return;
    }

    char temp[100] = "";

    // Handle thousands
    if (num >= 1000) {
        strcat(temp, units[num / 1000]);
        strcat(temp, " ");
        strcat(temp, thousand);
        num %= 1000;
    }

    // Handle hundreds
    if (num >= 100) {
        strcat(temp, " ");
        strcat(temp, units[num / 100]);
        strcat(temp, " ");
        strcat(temp, hundred);
        num %= 100;
    }

    // Handle tens and ones
    if (num >= 20) {
        strcat(temp, " ");
        strcat(temp, tens[num / 10]);
        num %= 10;
    } else if (num >= 10) {
        strcat(temp, " ");
        strcat(temp, teens[num - 10]);
        num = 0;
    }

    // Handle units
    if (num > 0) {
        strcat(temp, " ");
        strcat(temp, units[num]);
    }

    strcpy(words, temp);
}

// Function to Read Expressions from File
void readFile(const char *filename, char expressions[][100], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^\n]\n", expressions[*count]) != EOF) {
        (*count)++;
    }
    fclose(file);
}

// Function to Write Results to File
void writeFile(const char *filename, char results[][100], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", results[i]);
    }
    fclose(file);
}

// Function to Perform Operation on Two Operands
int performOperation(int operand1, int operand2, char operation) {
    switch (operation) {
        case '+': return operand1 + operand2; // Addition
        case '-': return operand1 - operand2; // Subtraction
        case '*': return operand1 * operand2; // Multiplication
        default:
            printf("Unknown operation: %c\n", operation);
            return 0; // Invalid operation
    }
}
