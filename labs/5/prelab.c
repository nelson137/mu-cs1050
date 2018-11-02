// Nelson Earle (nwewnh)
// LAB_5

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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


int check_error(int num) {
    return 1 <= num && num <= 50;
}


int getNumber(void) {
    int is_valid, num;
    printf("Enter the size of the array: ");
    do {
        num = getNum(&is_valid);
        if (is_valid && check_error(num))
            break;
        printf("Invalid input enter the size of the array again: ");
    } while (1);

    return num;
}


void initialize_array(int arr[], int size) {
    for (int i=0; i<size; i++)
        arr[i] = rand() % 10;
}


void print_array(int arr[], int size) {
    printf("Random array:");
    for (int i=0; i<size; i++)
        printf(" %d", arr[i]);
    printf("\n");
}


int main(void) {
    int arr[50] = {0};
    int size = getNumber();

    srand(time(NULL));
    initialize_array(arr, size);

    printf("\n");
    print_array(arr, size);

    return 0;
}
