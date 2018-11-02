// Nelson Earle (nwewnh)
// LAB_6

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEN 20

#define RESET     "\33[0m"
#define RED       "\33[91m"
#define YELLOW    "\33[93m"
#define GREEN(s)  "\33[92m" s RESET
#define BLUE(s)   "\33[94m" s RESET


/**
 * Trim the leading and trailing whitespace from a string.
 * https://stackoverflow.com/a/48472976/5673922
 */
void trim(char *str) {
    int count = 0;
    for (int i=0; str[i]; i++)
        if (!isspace(str[i]))
            str[count++] = str[i];
    str[count] = '\0';
}


/**
 * Get an integer from the user, set is_valid to 0 if parsing succeeds, else 1.
 */
int getNum(int *is_valid) {
    char input[100], *end, num_str[100];
    long num;
    *is_valid = 0;

    // Get user input
    printf(YELLOW);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        puts(RED "Error while reading user input" RESET);
        exit(1);
    }
    printf(RESET);

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


/**
 * Check that len is between 1 and 20, inclusive.
 */
int checkError(int len) {
    return 1 <= len && len <= 20;
}


/**
 * Return the size of the integer to create from the user.
 */
int getLength(void) {
    int is_valid, num;
    printf("Enter the size of the 2D array: ");
    do {
        num = getNum(&is_valid);
        if (is_valid && checkError(num))
            break;
        printf("Please enter a value between 1 and 20 only: ");
    } while (1);

    return num;
}


/**
 * Fill a square 2D array with random integers from 0 to 9, inclusive.
 */
void initialize2Darr(int arr[][LEN], int len) {
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            arr[i][j] = rand() % 10;
}


/**
 * Print a square 2D array.
 */
void print2Darr(int arr[][LEN], int len) {
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++)
            printf(BLUE("%3d"), arr[i][j]);
        printf("\n");
    }
}


/**
 * Return the number of zeros in a 2D array.
 */
int findZeros(int arr[][LEN], int len) {
    int zeros = 0;
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            if (arr[i][j] == 0)
                zeros++;

    return zeros;
}


/**
 * Return the number of even numbers in a 2D array.
 */
int findEvenOdd(int arr[][LEN], int len) {
    int evens = 0;
    for (int r=0; r<len; r++)
        for (int c=0; c<len; c++)
            if (arr[r][c] % 2 == 0)
                evens++;
    return evens;
}


/**
 * Flatten a 2D array into a 1D array then print it.
 */
void flattenArr(int arr[][LEN], int len) {
    // Flatten the 2D array
    int size = len * len;
    int flat[size];
    int cur = 0;
    for (int r=0; r<len; r++)
        for (int c=0; c<len; c++)
            flat[cur++] = arr[r][c];

    // Print the flattened array
    for (int i=0; i<size; i++)
        printf(BLUE("%2d"), flat[i]);
    printf("\n");
}


/**
 * Print a 2D array transposed.
 * A transposed 2D array has its rows and columns flipped. For example:
 *     {{1, 2, 3},      {{1, 4, 7},
 *      {4, 5, 6},  =>   {2, 5, 8},
 *      {7, 8, 9}}       {3, 6, 9}}
 */
void printTrans(int arr[][LEN], int len) {
    for (int c=0; c<len; c++) {
        for (int r=0; r<len; r++)
            printf(BLUE("%3d"), arr[r][c]);
        printf("\n");
    }
}


/**
 * Sort a 1D array and print it.
 */
void bsort(int arr[][LEN], int len) {
    // Flatten the 2D array
    int size = len * len;
    int flat[size];
    int cur = 0;
    for (int r=0; r<len; r++)
        for (int c=0; c<len; c++)
            flat[cur++] = arr[r][c];

    // Sort the 1D array
    int temp;
    for (int pass=0; pass<size; pass++) {
        for (int i=0; i<size-1; i++) {
            if (flat[i] > flat[i+1]) {
                temp = flat[i];
                flat[i] = flat[i+1];
                flat[i+1] = temp;
            }
        }
    }

    // Print the sorted 1D array
    for (int i=0; i<size; i++)
        printf(BLUE("%2d"), flat[i]);
    printf("\n");
}


int main(void) {
    int arr[LEN][LEN] = { {0} };
    int len = getLength();

    // Generate the random numbers
    srand(time(NULL));
    initialize2Darr(arr, len);

    // Print the array
    print2Darr(arr, len);

    // Print the number of zeros in the array
    printf("\nThe number of Zeros: "BLUE("%d")"\n", findZeros(arr, len));

    // Print the number of even numbers in the array
    int evens = findEvenOdd(arr, len);
    printf("\nThe number of Even numbers: "BLUE("%d")"\n", evens);

    // Print the number of odd numbers in the array
    printf("\nThe number of Odd numbers: "BLUE("%d")"\n", len*len - evens);

    // Print the array transposed
    printf("\nThe array transposed:\n");
    printTrans(arr, len);

    // Print the array flattened
    printf("\nThe array flattened:\n");
    flattenArr(arr, len);

    printf("\n"GREEN("*** BONUS ***")"\n");

    // Print the array flattened and sorted
    printf("\nThe array sorted:\n");
    bsort(arr, len);

    return 0;
}
