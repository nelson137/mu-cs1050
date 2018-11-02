// Nelson Earle (nwewnh)
// HW1

#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RESET        "\33[0m"
#define BOLD(x)      "\33[1m" x RESET
#define UNDERLINE(x) "\33[4m" x RESET

#define FG_BRIGHT_RED(x)   "\33[91m" x RESET
#define FG_BRIGHT_GREEN(x) "\33[92m" x RESET
#define FG_BRIGHT_BLUE     "\33[94m"


void fix_colors(int sig) {
    printf(RESET "\n");
}


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
    printf(FG_BRIGHT_BLUE);
    char *ret = fgets(input, sizeof(input), stdin);
    printf(RESET);

    // Check that no error occurred
    if (ret == NULL)
        exit(1);

    // Convert the input to a long
    // Non-digit characters are ignored
    num = strtol(input, &end, 10);
    // Convert the long back to a string
    sprintf(num_str, "%ld", num);
    // Trim the whitespace from both
    trim(num_str);
    trim(input);
    // Make sure they are equal and num is positive
    if (strcmp(num_str, input) != 0)
        *is_valid = 0;

    return num;
}


// Return 0 or 1 from the user
int getYesNo(char *prompt, char *err_msg) {
    int is_valid, num;
    do {
        // Print prompt
        printf(prompt);

        num = getNum(&is_valid);
        if (is_valid == 1 && (num == 0 || num == 1)) {
            // Parsed number is valid and is 0 or 1
            return num;
        } else {
            // Parsed number is not valid
            // Print error message, continue loop
            puts(err_msg);
            printf("\n");
        }
    } while (1);
}


// Return a positive integer from the user
int getUnits(void) {
    int is_valid, num;
    do {
        // Print prompt
        printf("Enter the number of units (in kWh): ");

        num = getNum(&is_valid);
        if (is_valid == 1 && num > 0)
            // Parsed number is valid and positive
            return num;
        else
            // Parsed number is not valid
            // Print error message, continue loop
            puts("Invalid input!\n");
    } while (1);
}


// Return a positive integer from the user
int getBonusNum(void) {
    int is_valid, num;

    // Print prompt
    printf("Enter a number: ");
    do {
        num = getNum(&is_valid);
        if (is_valid == 1 && num > 0)
            // Parsed number is valid and positive
            return num;
        else
            // Parsed number is not valid
            // Print error message, continue loop
            printf("Enter a positive number: ");
    } while (1);
}


/**
 * Gets an integer choice from the user corresponding to a menu option
 * @param prompt_func A function that prints the prompt
 * @param err_msg A string to print in response to each invalid input given
 * @param check_func A function that validates the user's input
 * @return An integer choice of menu options from the user
 */
int menu(void (*prompt_func)(void), char *err_msg, int (*check_func)(int)) {
    int is_valid, num;
    do {
        // Print prompt
        prompt_func();

        num = getNum(&is_valid);
        if (is_valid == 1 && check_func(num)) {
            // Parsed number is valid and between given bounds
            return num;
        } else {
            // Parsed number is not valid
            // Print error message, continue loop
            puts(err_msg);
            printf("\n");
        }
    } while (1);
}


// Error check menu input
int errorCheck(int option) {
    if (option >= 1 && option <= 3)
        // Valid input
        return 1;
    return 0;
}


// Error check units input
int errorCheckUnits(int units) {
    if (units > 0)
        // Valid input
        return 1;
    return 0;
}


// Return the rate in cents/kWh based on the category and units used
float getRate(int units, int option) {
    switch (option) {
        case 1:  // Residential
            if (units <= 200)
                return 7.5;
            else if (units <= 700)
                return 10;
            else if (units <= 1250)
                return 13.5;
            else
                return 15;
            break;
        case 2:  // Commercial
            if (units <= 300)
                return 10.5;
            else if (units <= 1000)
                return 14;
            else if (units <= 2000)
                return 17.5;
            else
                return 20;
            break;
        default:  // Industrial
            if (units <= 500)
                return 36.5;
            else if (units <= 2000)
                return 40;
            else if (units <= 3000)
                return 45.5;
            else
                return 50;
            break;
    }
}


// Return the connection charge based on the category
int charge(int option) {
    switch (option) {
        case 1:  // Residential
            return 25;
        case 2:  // Commercial
            return 90;
        default:  // Industrial
            return 850;
    }
}


// Print the menu prompt
void displayMenu(void) {
    puts("1. Residential");
    puts("2. Commercial");
    puts("3. Industrial");
    printf("Choose the type of connection: ");
}


// Return the energy charge + the connection charge
float calculateBill(void) {
    char *choice_err = "Invalid choice! Please enter a valid choice.";
    int option = menu(displayMenu, choice_err, errorCheck);

    printf("\n");

    int units = getUnits();

    printf("\n");
    
    float rate = getRate(units, option);

    float energy_charge = (float) units * rate / 100;
    float conn_charge = charge(option);
    float bill = energy_charge + conn_charge;

    char *te_fmt = "Total energy charge for this customer is: " \
                   FG_BRIGHT_GREEN("$%.2f") "\n";
    printf(te_fmt, energy_charge);

    char *cc_fmt = "Connection charge for this customer is: " \
                   FG_BRIGHT_GREEN("$%.2f") "\n";
    printf(cc_fmt, conn_charge);

    char *b_fmt = "Total bill due from this connection is: " \
                  UNDERLINE(FG_BRIGHT_GREEN("$%.2f")) "\n";
    printf(b_fmt, bill);

    return bill;
}


int main(void) {
    // Fix colors even with SIGINT (^C)
    signal(SIGINT, fix_colors);

    float total_bill = 0;
    int n_bills = 0;

    char *prompt = "Do you want to continue and calculate another bill? If yes enter 1, else 0: ";
    char *err_msg = "Invalid choice, try again";
    do {
        total_bill += calculateBill();
        n_bills++;
        printf("\n");
        if (getYesNo(prompt, err_msg) == 0)
            break;
        else
            printf("\n");
    } while (1);

    printf("\n");

    char *tb_fmt = "You calculated the bill " FG_BRIGHT_RED("%d") \
                   " time%s and the total amount from all of the bills due is " \
                   BOLD(FG_BRIGHT_GREEN("$%.2f\n"));
    printf(tb_fmt, n_bills, n_bills>1?"s":"", total_bill);

    puts("\n\n*** BONUS ***\n");

    int num = getBonusNum();

    printf("The numbers are:");
    long long prod = 1, prod_evens = 1, prod_odds = 1;
    for (int i=1; i<=num; i++) {
        printf(FG_BRIGHT_RED(" %d"), i);
        if (i == 0)
            continue;
        prod = prod * i;
        if (i % 2 == 0)
            prod_evens *= i;
        else
            prod_odds *= i;
    }
    printf("\n");

    char *a_prod_fmt = "The product of all numbers from " FG_BRIGHT_RED("1") \
                       " to " FG_BRIGHT_RED("%d") " is " FG_BRIGHT_RED("%ld") "\n";
    printf(a_prod_fmt, num, prod);

    char *e_prod_fmt = "The product of all " UNDERLINE("even") \
                       " numbers is " FG_BRIGHT_RED("%ld") "\n";
    printf(e_prod_fmt, prod_evens);

    char *o_prod_fmt = "The product of all " UNDERLINE("odd") \
                       " numbers is " FG_BRIGHT_RED("%ld") "\n";
    printf(o_prod_fmt, prod_odds);

    return 0;
}
