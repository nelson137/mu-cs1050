// Nelson Earle (nwewnh)
// LAB_2

#include <stdio.h>  // printf, sprintf, puts, fgets, stdin
#include <stdlib.h>  // strtol
#include <ctype.h>  // isspace


// https://stackoverflow.com/a/48472976/5673922
void trim(char *str) {
    int count = 0;
    for (int i=0; str[i]; i++)
        if (!isspace(str[i]))
            str[count++] = str[i];
    str[count] = '\0';
}


int getPosInt(char *prompt1, char *prompt2) {
    char input[100], *end, num_str[100];
    long num;

    // Print the primary prompt
    printf("%s", prompt1);
    // Get user input
    fgets(input, sizeof(input), stdin);
    while (1) {
        // Convert the input to a long
        // Non-digit characters are ignored
        num = strtol(input, &end, 10);
        // Convert the long back to a string
        sprintf(num_str, "%ld", num);
        // Trim the whitespace from both
        trim(num_str);
        trim(input);
        // Make sure they are equal and num is positive
        if (*num_str == *input && num >= 0)
            break;
        // Print secondary prompt
        printf("%s", prompt2);
        // Get user input
        fgets(input, sizeof(input), stdin);
    }

    return num;
}


int main(void) {
    char *prompt2 = "Enter a non-negative number: ";
    int num1, num2;

    num1 = getPosInt("Enter the first number: ", prompt2);
    puts("");
    num2 = getPosInt("Enter the second number: ", prompt2);

    puts("");

    puts("ADDITION");
    printf("%d + %d = %d\n", num1, num2, num1+num2);

    puts("");

    puts("MULTIPLICATION");
    printf("%d * %d = %d\n", num1, num2, num1*num2);

    return 0;
}
