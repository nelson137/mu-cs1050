// Nelson Earle (nwewnh)
// LAB_9

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int get_size(void) {
    int num, is_valid;
    char c;

    printf("Enter the size of the input: ");

    do {
        num = 0;
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
            num *= 10;
            num += c - '0';
        } while (1);
        printf(RESET);

        if (is_valid && check_size(num))
            break;
        else
            printf("Input must be between %d and %d, inclusive: ", MIN, MAX);
    } while (1);

    return num;
}


/**
 * Fill arr with random number from 1 to 10, inclusive.
 */
void initialize_pointerArray(int *arr, int len) {
    for (int i=0; i<len; i++)
        *(arr+i) = (rand() % 10) + 1;
}


/**
 * Print each element of an array.
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
 * Return the maximum value in arr.
 */
int find_max(int *arr, int len) {
    int max = *(arr);
    for (int i=0; i<len; i++)
        if (*(arr+i) > max)
            max = *(arr+i);
    return max;
}


int main(void) {
    srand(time(NULL));

    int arr[MAX];
    int len = get_size();

    initialize_pointerArray(arr, len);

    printf("\n");

    printf("The array:\n");
    print_pointerArray(arr, len);

    printf("\n");

    printf("The largest value in the pointer is: ");
    printf(BLUE("%d") "\n", find_max(arr, len));

    return 0;
}
