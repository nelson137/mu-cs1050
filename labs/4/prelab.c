// Nelson Earle (nwewnh)
// LAB_4

#include <ctype.h>   // isspace
#include <stdio.h>   // puts, fprintf, fgets, stdin, stderr
#include <stdlib.h>  // exit
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
    *is_valid = 0;

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
    // Make sure they are equal
    if (strcmp(num_str, input) == 0)
        *is_valid = 1;

    return num;
}


int courseNumCheck(int num) {
    return num > 1;
}


int scoreCheck(int score) {
    return 0 <= score && score <= 100;
}


float getScore(int *is_valid) {
    return getNum(is_valid);
}


float getScorePoint(int score) {
    switch (score) {
        case 95 ... 100:
            return 4.0;
        case 90 ... 94:
            return 3.5;
        case 85 ... 89:
            return 3.0;
        case 80 ... 84:
            return 2.5;
        case 75 ... 79:
            return 2.0;
        case 70 ... 74:
            return 1.0;
        default:  // 0 ... 69
            return 0.0;
    }
}


void printComment(float full_asp) {
    int asp = full_asp * 100;
    char *comment;

    switch (asp) {
        case 380 ... 400:
            comment = "Excellent";
            break;
        case 350 ... 379:
            comment = "Very Good";
            break;
        case 300 ... 349:
            comment = "Good";
            break;
        case 250 ... 299:
            comment = "Satisfactory";
            break;
        case 200 ... 249:
            comment = "Not Passed";
            break;
        default:  // 0 ... 199
            comment = "Unofficial Drop";
            break;
    }

    printf("COMMENT: %s\n", comment);
}


int getNumCourses(void) {
    int is_valid, n_courses;

    // Print the primary prompt
    printf("Enter the number of courses: ");

    do {
        // Get user input
        n_courses = getNum(&is_valid);
        // Validate input
        if (is_valid && courseNumCheck(n_courses))
            return n_courses;
        else
            printf("Error! Please enter a number of courses greater than 1: ");
    } while (1);
}


int main(void) {
    puts("STUDENT ASP CALCULATOR\n");

    int n_courses = getNumCourses();

    puts("");

    int score, is_valid;
    float point;
    float total_points = 0;
    for (int i=0; i<n_courses; i++) {
        do {
            printf("Enter the student score for course %d (percent): ", i+1);
            score = getScore(&is_valid);
            if (is_valid && scoreCheck(score))
                break;
            else
                puts("Error");
        } while(1);

        point = getScorePoint((float)score);
        printf("Point = %.2f\n", point);
        total_points += point;
    }

    puts("");

    float asp = total_points/(float)n_courses;
    printf("The student ASP: %.2f\n", asp);

    printComment(asp);

    return 0;
}
