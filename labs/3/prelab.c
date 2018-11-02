// Nelson Earle (nwewnh)
// LAB_3

#include <ctype.h>   // isspace
#include <math.h>    // pow
#include <stdio.h>   // printf, sprintf, puts, getchar, fgets, stdin
#include <stdlib.h>  // exit, strtol
#include <string.h>  // strcmp


#define ARRAY_LENGTH(x) sizeof(x)/sizeof(x[0])

#ifndef M_PI
#define M_PI 3.141593
#endif


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
int getNum(void) {
    char input[100], *end, num_str[100];
    long num;

    // Get user input
    if (fgets(input, sizeof(input), stdin) == NULL) {
        puts("Error while reading user input");
        exit(1);
    }

    // Convert the input to a long
    // Non-digit characters are ignored
    num = strtol(input, &end, 10);
    // Convert the long back to a string
    sprintf(num_str, "%ld", num);
    // Trim the whitespace from both
    trim(num_str);
    trim(input);
    // Make sure they are equal and num is positive
    if (strcmp(num_str, input) != 0 || num < 0)
        num = -1;

    return num;
}


// Get a positive integer from the user with a prompt,
// indefinitely re-prompt if invalid input is given
int getPosInt(void) {
    int num;

    do {
        // Print the prompt
        printf("Enter a positive number: ");

        // Get user input
        num = getNum();

        if (num > 0)
            break;
        else
            puts("Number can't be negative or zero");
    } while (1);

    return num;
}


int main(void) { 
    // Get the user's choice
    puts("Area calculation");
    puts("(1) Square");
    puts("(2) Cube");
    puts("(3) Circle");
    printf("Please make a selection: ");
    int choice = getNum();

    while (choice < 1 || choice > 3) {
        puts("Incorrect choice");
        puts("");

        puts("Area calculation");
        puts("(1) Square");
        puts("(2) Cube");
        puts("(3) Circle");
        printf("Please make a selection: ");
        choice = getNum();
    }

    puts("");

    // Get the side length of the shape from the user
    int length = getPosInt();
    puts("");

    // Calculate the area
    if (choice == 1) {
        printf("The length of the side of the square is %d.\n", length);
        printf("The area of the square is %d.\n", (int)pow(length, 2));
    } else if (choice == 2) {
        printf("The length of the side of the cube is %d.\n", length);
        printf("The surface are of the cube is %d.\n", (int)(6*pow(length, 2)));
    } else if (choice == 3) {
        printf("The radius of the circle is %d.\n", length);
        printf("The area of the circle is %.2f.\n", M_PI*pow(length, 2));
    }

    return 0;
}
