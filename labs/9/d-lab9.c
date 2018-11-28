// Nelson Earle (nwewnh)
// LAB_9

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define RESET    "\33[0m"
#define YELLOW   "\33[93m"
#define RED(x)   "\33[91m" x RESET
#define BLUE(x)  "\33[94m" x RESET

#define MIN         1
#define MAX         50
#define MARGIN      3
#define CELL_WIDTH  4


/**
 * Check that num is between 1 and 50, inclusive.
 */
int check_size(int num) {
    return MIN <= num && num <= MAX;
}


/**
 * Return an integer from the user between 1 and 50, inclusive.
 */
void get_size(int *num) {
    int is_valid;
    char c;

    printf("Enter the size of the input: ");

    do {
        *num = 0;
        is_valid = 1;

        printf(YELLOW);
        // Read characters
        do {
            c = getc(stdin);
            if (c == '\n')
                break;
            if (!('0' <= c && c <= '9')) {
                is_valid = 0;
                // Eat trailing characters to newline if non-digit is read
                while (c != '\n')
                    c = getc(stdin);
                break;
            }
            // Append digit to num
            *num *= 10;
            *num += c - '0';
        } while (1);
        printf(RESET);

        if (is_valid && check_size(*num))
            break;
        else
            printf("Input must be between %d and %d, inclusive: ", MIN, MAX);
    } while (1);
}


/**
 * Fill the given integer array with random number from 1 to 10, inclusive.
 */
void initialize_pointerArray(int *arr, int len) {
    for (int i=0; i<len; i++)
        *(arr+i) = (rand() % 10) + 1;
}


/**
 * Print each element of the given integer array.
 *
 * This function uses the width of the terminal to print newlines where
 * appropriate in order to make sure that the printed out cells do not wrap
 * onto the next line.
 */
void print_pointerArray(int *arr, int len) {
    // Current terminal width
    static struct winsize w;
    static int elemsPerLine;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
        elemsPerLine = (w.ws_col - MARGIN) / CELL_WIDTH;
    else
        // ioctl() failed, default to 80 cols
        elemsPerLine = (80 - MARGIN) / CELL_WIDTH;

    for (int i=0; i<len; i++) {
        if (i > 0 && i % elemsPerLine == 0)
            printf("\n");
        printf(BLUE("%-*d"), CELL_WIDTH, *(arr+i));
    }
    printf("\n");
}


/**
 * Return the minimum value in the given sorted integer array.
 */
int find_min(int *arr, int len) {
    return *arr;
}


/**
 * Return the maximum value in the given sorted integer array.
 */
int find_max(int *arr, int len) {
    return *(arr+len-1);
}


/**
 * Return the medium value of the given integer array.
 * If there is no one median value, the average of the two median values is returned.
 */
float find_median(int *arr, int len) {
    int midpoint = (int) (len-1) / 2;
    return len % 2 == 0 ?
        (float) (*(arr+midpoint) + *(arr+midpoint+1)) / 2 :
        *(arr+midpoint);
}


/**
 * Bubble sort the given integer array.
 */
void bubble_sort(int *arr, int len) {
    int temp;
    for (int pass=0; pass<len; pass++) {
        for (int i=0; i<len-1; i++) {
            if (*(arr+i) > *(arr+i+1)) {
                temp = *(arr+i);
                *(arr+i) = *(arr+i+1);
                *(arr+i+1) = temp;
            }
        }
    }
}


/**
 * Reverse the given integer array.
 */
void reverseArray(int *arr, int len) {
    int temp;
    int end = len - 1;
    for (int i=0; i<(int)len/2; i++) {
        temp = *(arr+i);
        *(arr+i) = *(arr+end-i);
        *(arr+end-i) = temp;
    }
}


/**
 * Fill the given dest array with every other element of the given orig array.
 */
void every_other(int *dest, int *orig, int len) {
    int count = 0;
    for (int i=0; i<len; i++) {
        if (i % 2 == 0)
            *(dest+count++) = *(orig+i);
    }
}


int main(void) {
    srand(time(NULL));

    int arr[MAX];
    int len;
    get_size(&len);

    initialize_pointerArray(arr, len);

    printf("\n");

    printf("The array:\n");
    print_pointerArray(arr, len);

    bubble_sort(arr, len);

    printf("\n");

    printf("The minimum value of the array is: ");
    printf(BLUE("%d") "\n", find_min(arr, len));

    printf("The maximum value of the array is: ");
    printf(BLUE("%d") "\n", find_max(arr, len));

    printf("\n");

    printf("The sorted array:\n");
    print_pointerArray(arr, len);

    printf("\n");

    printf("The median value of the array is: ");
    printf(BLUE("%.2f") "\n", find_median(arr, len));

    printf("\n********** BONUS **********\n\n");

    reverseArray(arr, len);

    int new_len = round((float)len/2);
    int arr_bonus[new_len];
    every_other(arr_bonus, arr, len);

    printf("Every other element of the reversed array is:\n");
    print_pointerArray(arr_bonus, new_len);

    return 0;
}
