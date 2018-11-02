// Nelson Earle (nwewnh)
// LAB_5

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define STYLE "\33[33m\33[1m"
#define RESET  "\33[0m"


// Check that 1 <= num <= 50
int check_error(int num) {
    return 1 <= num && num <= 50;
}


// Fill arr with len random integers
void init_array(int arr[], int len) {
    for (int i=0; i<len; i++)
        arr[i] = rand() % 10;
}


// Print out each element of arr on the same line
void print_arr(int arr[], int len) {
    for (int i=0; i<len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


// Return the average of arr
float average(int arr[], int len) {
    int sum = 0;
    for (int i=0; i<len; i++)
        sum += arr[i];
    return (float) sum/len;
}


// Return the standard deviation of arr
float std_dev(int arr[], int len) {
    float std = 0;
    float avg = average(arr, len);

    for (int i=0; i<len; i++)
        std += pow((arr[i]-avg), 2);

    std /= len;

    return sqrt(std);
}


// Return the index of the largest integer in arr
int max(int arr[], int len) {
    int largest_i = 0;
    for (int i=0; i<len; i++)
        if (arr[i] > arr[largest_i])
            largest_i = i;

    return largest_i;
}


int main(void) {
    int arr[50] = {0};

    // Get the number of random integers to generate
    printf("Enter the number of elements to be generated: ");
    int len;
    do {
        scanf(" %d", &len);
        if (check_error(len))
            break;
        else
            printf("Please enter a number between 1 and 50: ");
    } while(1);

    // Generate the random integers
    srand(time(NULL));
    init_array(arr, len);

    float avg = average(arr, len);
    float dev = std_dev(arr, len);
    int max_i = max(arr, len);

    printf("\nThe array is:\n" STYLE);
    print_arr(arr, len);
    printf(RESET);

    printf("The average of the array is: "STYLE"%.2f"RESET"\n", avg);
    printf("The standard deviation of the array is "STYLE"%.2f"RESET"\n", dev);

    printf("\n*** BONUS ***\n");
    printf("The index of the biggest element is "STYLE"%d"RESET"\n", max_i);

    return 0;
}
