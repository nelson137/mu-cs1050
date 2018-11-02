// Nelson Earle (nwewnh)
// LAB_6

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEN 20


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


// Check that len is between 1 and 20, inclusive
int check_error(int len) {
    return 1 <= len && len <= 20;
}


// Return an integer from the user
int getLength(void) {
    int is_valid, num;
    printf("Enter the size of the 2D array: ");
    do {
        num = getNum(&is_valid);
        if (is_valid && check_error(num))
            break;
        printf("Please enter a value between 1 and 20 only: ");
    } while (1);

    return num;
}


// Fill a len x len 2D array with random integers from 0 to 9, inclusive
void initialize_2Darray(int arr[][LEN], int len) {
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            arr[i][j] = rand() % 10;
}


// Print out a len x len 2D array
void print_2Darray(int arr[][LEN], int len) {
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}


// Return the number of zeros in a len x len array
int findZeros(int arr[][LEN], int len) {
    int zeros = 0;
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            if (arr[i][j] == 0)
                zeros++;

    return zeros;
}


int main(void) {
    int arr[LEN][LEN] = { {0} };
    int len = getLength();

    // Generate the random numbers
    srand(time(NULL));
    initialize_2Darray(arr, len);

    // Print out the array
    print_2Darray(arr, len);

    // Print out the number of zeros in the array
    printf("\n");
    printf("The number of zeros in 2D array: %d\n", findZeros(arr, len));

    return 0;
}
