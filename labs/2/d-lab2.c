// Nelson Earle (nwewnh)
// LAB_2


#include <stdio.h>  // printf, sprintf, puts, fgets, stdin
#include <stdlib.h>  // strtol
#include <ctype.h>  // isspace
#include <stdbool.h>  // true, false
#include <math.h>  // sqrt


// Remove all space characters from a char*
// https://stackoverflow.com/a/48472976/5673922
void trim(char *str) {
    int count = 0;
    for (int i=0; str[i]; i++)
        if (!isspace(str[i]))
            str[count++] = str[i];
    str[count] = '\0';
}


// Get a positive integer from the user,
// return -1 if it is negative
int getPosInt(void) {
    char input[100], *end, num_str[100];
    long num;

    // Get user input
    fgets(input, sizeof(input), stdin);

    // Convert the input to a long
    // Non-digit characters are ignored
    num = strtol(input, &end, 10);
    // Convert the long back to a string
    sprintf(num_str, "%ld", num);
    // Trim the whitespace from both
    trim(num_str);
    trim(input);
    // Make sure they are equal and num is positive
    if (*num_str != *input || num < 0)
        num = -1;

    return num;
}


// Get a positive integer from the user with a prompt,
// indefinitely re-prompt if invalid input is given
int getPosIntPrompt(char *prompt1, char *prompt2) {
    int num;
    bool use_p2 = false;

    do {
        if (!use_p2) {
            // Print the primary prompt
            printf("%s", prompt1);
            use_p2 = true;
        } else {
            // Print the secondary prompt
            printf("%s", prompt2);
        }

        // Get user input
        num = getPosInt();

        if (num > -1)
            break;
    } while (1);

    return num;
}


int main(void) {
    char *prompt2 = "Enter a non-negative number: ";
    int num1, num2, num_sqrt;
    char *p;

    num1 = getPosIntPrompt("Enter the first number: ", prompt2);
    puts("");
    num2 = getPosIntPrompt("Enter the second number: ", prompt2);

    puts("");

    puts("ADDITION");
    printf("The sum of %d and %d is %d.\n", num1, num2, num1+num2);

    puts("");

    puts("SUBTRACTION");
    printf("The difference between %d and %d is %d.\n", num1, num2, num1-num2);

    puts("");

    puts("MULTIPLICATION");
    printf("The product of %d and %d is %d.\n", num1, num2, num1*num2);

    puts("");

    puts("DIVISION");
    p = "Cannot divide by zero!\nEnter a new number: ";
    while (num2 == 0)
        num2 = getPosIntPrompt(p, p);
    printf("%d divided by %d is %.2f.\n", num1, num2, (float)num1/num2);

    puts("");

    printf("%d is the bigger number.\n", num1 >= num2 ? num1 : num2);

    puts("");

    puts("SQUARE ROOT");
    printf("Enter a number for the square root operation: ");
    num_sqrt = getPosInt();
    p = "Cannot take the square root of a negative number.\nTry again: ";
    while (num_sqrt < 0)
        num_sqrt = getPosIntPrompt(p, p);
    printf("The square root of %d is %.2f.\n", num_sqrt, sqrt(num_sqrt));

    return 0;
}
