#include <stdio.h>


/**
 * Check that num is between 1 and 20, inclusive.
 */
int errorCheck(int num) {
    return 1 <= num && num <= 20;
}


/**
 * Return the maximum value for which factorials should be calculated.
 */
int getNum(void) {
    int num;
    char c;

    printf("Enter a value to calculate the factorials to: ");

    do {
        num = 0;

        // Read characters
        do {
            c = getc(stdin);
            // If c is a newline or non-digit character
            if (c == '\n' || !('0' <= c && c <= '9')) {
                // Eat trailing characters to newline if non-digit is read
                while (c != '\n')
                    c = getc(stdin);
                break;
            }
            // Append digit to num
            num *= 10;
            num += c - '0';
        } while (1);

        if (errorCheck(num))
            break;
        else
            printf("Input must be between 1 and 20: ");
    } while (1);

    return num;
}


/**
 * Return the factorial of x.
 */
unsigned long long calcFact(unsigned long long x) {
    return x==1 ? 1 : x * calcFact(x-1);
}


/**
 * Fill array output with the factorial of each number 1 through limit.
 */
void factorial(unsigned long long *output, int limit) {
    for (unsigned long long i=1; i<=limit; i++)
        *(output++) = calcFact(i);
}


void printArray(unsigned long long *arr, int len) {
    printf("The calculated factorial values:\n");
    for (int i=0; i<len; i++)
        printf("%llu ", *(arr+i));
    printf("\n");
}


int main(void) {
    int limit = getNum();
    unsigned long long arr[limit];
    factorial(&arr[0], limit);
    printArray(arr, limit);

    return 0;
}
