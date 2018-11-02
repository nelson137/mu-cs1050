// Nelson Earle (nwewnh)
// LAB_3

#include <ctype.h>   // isspace
#include <math.h>    // sqrt, pow
#include <stdio.h>   // printf, sprintf, puts, fgets, stdin
#include <stdlib.h>  // exit, strtol, abs
#include <string.h>  // strcmp


// https://stackoverflow.com/a/48472976/5673922
void trim(char *str) {
    int count = 0;
    for (int i=0; str[i]; i++)
        if (!isspace(str[i]))
            str[count++] = str[i];
    str[count] = '\0';
}


// Get an integer from the user,
// set is_valid to 0 if parsing succeeds, else 1
int getNum(int *is_valid) {
    char input[100], *end, num_str[100];
    long num;
    *is_valid = 1;

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
    if (strcmp(num_str, input) == 0)
        *is_valid = 0;

    return num;
}


// Indefinitely prompt user for an integer while invalid input is given,
// print err_msg each time it fails
int getNumPrompt(char *prompt, char *err_msg) {
    int is_valid, num;
    do {
        printf(prompt);

        num = getNum(&is_valid);
        if (is_valid == 1) {
            return num;
        } else {
            puts(err_msg);
            puts("");
        }
    } while (1);
}


// Return an integer between min and max, inclusive, from the user
int getNumRange(char *prompt, char *err_msg, int min, int max) {
    int is_valid, num;
    do {
        printf(prompt);

        num = getNum(&is_valid);
        if (is_valid == 1 && min <= num && num <= max) {
            return num;
        } else {
            puts(err_msg);
            puts("");
        }
    } while (1);
}


// Menu for completeTriangle, return choice
int menu() {
    int choice;

    do {
        // Print the prompt
        puts("Type of right triangle:");
        puts("(1) Two legs");
        puts("(2) One leg, one hypotenuse");
        printf("Please make a selection: ");

        // Get user input
        int is_valid;
        choice = getNum(&is_valid);

        if (is_valid == 1 && choice >= 1 && choice <= 2)
            return choice;
        else
            puts("Invalid choice, please try again\n");
    } while (1);

    return choice;
}


void completeTriangle(void) {
    int t_type = menu();

    puts("");
    char *len_err = "Invalid value, length should be between 1 and 100";
    int side_min = 1;
    int side_max = 100;
    if (t_type == 1) {
        int leg1 = getNumRange("Length for the first leg: ", len_err, side_min, side_max);
        puts("");
        int leg2 = getNumRange("Length for the second leg: ", len_err, side_min, side_max);
        puts("");

        float hyp = sqrt( pow(leg1,2) + pow(leg2,2) );
        printf("Calculation: %d^2 + %d^2 = c^2\n", leg1, leg2);
        printf("Hypotenuse length (c) = %.2f\n", hyp);
    } else if (t_type == 2) {
        int leg = getNumRange("Length for the leg: ", len_err, side_min, side_max);
        puts("");
        int hyp = getNumRange("Length for the hypotenuse: ", len_err, side_min, side_max);
        puts("");

        float missing_leg = sqrt( pow(hyp,2) - pow(leg,2) );
        printf("Calculation: %d^2 + b^2 = %d^2\n", leg, hyp);
        printf("Missing leg length (b) = %.2f\n", missing_leg);
    }
}


// Calculate x^n where n is positive via recursion
float myPow(int num, int power) {
    if (power == 0)
        return 1;
    return num * myPow(num, power-1);
}


int main(void) {
    // Calculate the missing sides of a right triangle
    char *prompt = "\nDo you want to calculate again?\nPress 0 for yes, 1 for no: ";
    char *err_msg = "Invalid choice, try again";
    do {
        completeTriangle();
        if (getNumRange(prompt, err_msg, 0, 1) == 1)
            break;
        else
            puts("");
    } while (1);

    // Calculate an exponential using a custom implementation of pow
    puts("\n*** BONUS ***\n");

    char *bonus_err = "Invalid number, try again";
    int num = getNumPrompt("Enter a number: ", bonus_err);
    puts("");
    int power = getNumPrompt("Enter an exponent: ", bonus_err);

    puts("");

    if (num == 0 && power == 0) {
        printf("myPow(%d, %d) = undefined\n", num, power);
    } else {
        float answer;
        if (power < 0) {
            answer = (float)1/myPow(num, abs(power));
            printf("myPow(%d, %d) = %f\n", num, power, answer);
        } else {
            answer = myPow(num, power);
            printf("myPow(%d, %d) = %.2f\n", num, power, answer);
        }
    }

    return 0;
}
