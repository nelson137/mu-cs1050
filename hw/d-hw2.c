// Nelson Earle (nwewnh)
// HW2

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROW  12  // Number of Rows of seats
#define COL  6   // Number of Columns of seats
#define MAX  25  // Maximum space to reserve for merged strings

#define RESET     "\33[0m"
#define YELLOW    "\33[93m"
#define BOLD(x)   "\33[1m" x RESET
#define RED(x)    "\33[91m" x RESET
#define GREEN(x)  "\33[92m" x RESET


int costMatrix[ROW][COL] = {
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500},
    {500, 200, 500, 500, 200, 500}
};


/**
 * Function: getSafeString
 * Parameters:
 *     string - the target where the input string will be stored
 *     maxsize - the largest string that can be input, including the null-
 *         terminator
 * Discussion:
 *     This function inputs a string from stdin that can contain any character,
 *     except newline.  The function will return when a newline is entered.
 *     Newline is not included in the string.  The string will be null-
 *     terminated.  Characters beyond the max will be thrown away.
 * By: Jim Ries
 * Date: 20181007
 */
void getSafeString(char *string, int maxsize)
{
    int indexcur=0;
    char charcur = '\n';
    
    // Spin until we get something other than newline
    while ('\n'==charcur)
    {
        charcur = getc(stdin);
    }
    
    while (indexcur<(maxsize-1) && '\n'!=charcur)
    {
        if ('\n'!=charcur)
        {
            string[indexcur] = charcur;
        }
        indexcur++;
        charcur = getc(stdin);
    }
    string[indexcur] = '\0';
    
    // Spin until they hit enter
    while ('\n'!=charcur){
        charcur = getc(stdin);
    }
}


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
        puts(RED("Error while reading user input"));
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
 * Print the main menu.
 */
void displayMenu(void) {
    puts("1. Admin portal");
    puts("2. Reserve a seat");
    puts("3. Quit");
}


/**
 * Return the users's choice for the main menu.
 */
int getOption(void) {
    int is_valid, num;

    displayMenu();
    printf("Choose an option: ");
    do {
        num = getNum(&is_valid);
        if (is_valid && 1 <= num && num <= 3)
            break;
        printf("\n" RED("Invalid option!") "\n\n");
        displayMenu();
        printf("Choose an option: ");
    } while (1);

    return num;
}


/**
 * Authenticate attempted login to the admin account.
 */
int loginMatch(int passwd, int adminPasswd) {
    return passwd == adminPasswd;
}


/**
 * Attempt to login as admin, return whether or not login was successful.
 * The user gets three attempts before returning a non-successful value
 * of zero.
 */
int adminLogin(int adminPasswd) {
    int is_valid, passwd, attempts = 0;
    printf("Admin password: ");
    do {
        passwd = getNum(&is_valid);
        // Check that input is a number and it matches adminPasswd
        if (is_valid && loginMatch(passwd, adminPasswd))
            return 1;
        // Return if too many invalid attempts
        if (++attempts >= 3) {
            printf("\n" RED("Too many invalid attempts") "\n");
            return 0;
        }
        printf("\n" RED("Invalid password") "\n\n");
        printf("Admin password: ");
    } while (1);
}


/**
 * Fill flight with count seats.
 * Seats (cells in the flight array) denoted by an 'X' are reserved. Seats
 * denoted by an 'O' are unreserved.
 */
void initialSeats(char flight[][COL], int count) {
    // Mark all seats as unreserved
    for (int r=0; r<ROW; r++)
        for (int c=0; c<COL; c++)
            flight[r][c] = 'O';

    // Mark count seats (chosen randomly) as reserved
    int r, c, marked = 0;
    while (marked < count) {
        r = rand() % ROW;
        c = rand() % COL;
        if (flight[r][c] != 'X') {
            flight[r][c] = 'X';
            marked++;
        }
    }
}


/**
 * Print the flight's seating chart.
 * Reserved seats, denoted by an 'X', are highlighted in red
 */
void printFlightMap(char flight[][COL]) {
    // Print the column headers
    printf("   ");
    for (int i=0; i<COL; i++)
        printf(BOLD("%3d"), i);
    printf("\n");

    for (int r=0; r<ROW; r++) {
        // Print the row headers
        printf(BOLD("%3d "), r);
        for (int c=0; c<COL; c++) {
            if (flight[r][c] == 'X')
                // Print reserved seats (X) in red
                printf(RED("%2c "), flight[r][c]);
            else
                // Print unreserved seats
                printf("%2c ", flight[r][c]);
        }
        printf("\n");
    }
}


/**
 * Print the flight options
 */
void flightMenu(void) {
    puts("1. COU --> MIA");
    puts("2. COU --> BNA");
    puts("3. COU --> LAS");
}


/**
 * Get the user's choice of a flight to reserve a seat in.
 */
int getFlightChoice(void) {
    flightMenu();

    int is_valid, num;
    printf("Choose a flight: ");
    do {
        num = getNum(&is_valid);
        if (is_valid && 1 <= num && num <= 3)
            break;
        printf("\n" RED("Invalid option!") "\n\n");
        flightMenu();
        printf("Choose a flight: ");
    } while (1);

    return num;
}


/**
 * Print the flight map of all three flights.
 */
void printAllFlights(char f1[][COL], char f2[][COL], char f3[][COL]) {
    puts("\nFlight map for Columbia to Miami:");
    printFlightMap(f1);
    puts("\nFlight map for Columbia to Nashville:");
    printFlightMap(f2);
    puts("\nFlight map for Columbia to Las Vegas:");
    printFlightMap(f3);
}


/**
 * Return the revenue earned from flight.
 * The revenue of a flight is defined as the sum of the cost of the reserved
 * seats. The global two-dimensional array costMatrix is used to determine the
 * cost of the seat.
 */
int getRevenue(char flight[][COL]) {
    int revenue = 0;
    for (int r=0; r<ROW; r++)
        for (int c=0; c<COL; c++)
            if (flight[r][c] == 'X')
                revenue += costMatrix[r][c];
    return revenue;
}


/**
 * Return the total revenue earned from flights flight1, flight2, and flight3.
 * This function can only be called in admin mode.
 */
int getTotalRevenue(char f1[][COL], char f2[][COL], char f3[][COL]) {
    return getRevenue(f1) + getRevenue(f2) + getRevenue(f3);
}


/**
 * Return the user's choice of a row to reserve a seat in.
 */
int getRowChoice(void) {
    int is_valid, row;
    printf("Choose a row: ");
    do {
        row = getNum(&is_valid);
        if (is_valid && 0 <= row && row < ROW)
            break;
        printf(RED("Seat rows are between 0 and %d") "\n", ROW-1);
        printf("Choose a row: ");
    } while (1);

    return row;
}


/**
 * Return the user's choice of a column to reserve a seat in.
 */
int getColChoice(void) {
    int is_valid, col;
    printf("Choose a column: ");
    do {
        col = getNum(&is_valid);
        if (is_valid && 0 <= col && col < COL)
            break;
        printf(RED("Seat columns are between 0 and %d") "\n", COL-1);
        printf("Choose a column: ");
    } while (1);

    return col;
}


/**
 * Reserve a seat in flight chosen by the user.
 * Error check that the chosen row and column are in bounds, and that the seat
 * is not already reserved.
 */
void seatReservation(char flight[][COL]) {
    int row, col;
    printFlightMap(flight);
    printf("\n");
    do {
        // Get row and column of user's choice of seat to reserve
        row = getRowChoice();
        col = getColChoice();
        // Break loop if the seat is unreserved
        if (flight[row][col] == 'O')
            break;
        printf("\n" RED("Sorry, this seat is already reserved") "\n\n");
    } while (1);
    // Reserve the chosen seat
    flight[row][col] = 'X';
}


/**
 * Zip the strings name and num.
 * If name and num are not the same length, the excess characters are appended
 * to the end.
*/
void printMessage(char *name, char *num) {
    char result[strlen(name)+strlen(num)+1];
    int i = 0;

    while (1) {
        if (*name == '\0' && *num == '\0')
            break;
        if (*name != '\0')
            result[i++] = *(name++);
        if (*num != '\0')
            result[i++] = *(num++);
    }
    result[i] = '\0';

    printf("Your e-ticket number is " BOLD("%s") "\n", result);
}


int main (void) {
    srand(time(NULL));

    int adminPasswd = 105018;

    char flight1[ROW][COL];
    char flight2[ROW][COL];
    char flight3[ROW][COL];

    int numSeats = rand() % 20 + 1;
    initialSeats(flight1, numSeats);
    initialSeats(flight2, numSeats);
    initialSeats(flight3, numSeats);

    char num1[] = "MIA1050";
    char num2[] = "BNA1050";
    char num3[] = "LSA1050";

    puts("********** WELCOME TO MIZZOU AIRLINE BOOKING SYSTEM **********");

    int option, totalRevenue, flightChoice;
    char name[MAX];
    while (1) {
        printf("\n\n");
        option = getOption();
        switch (option) {
            case 1:  // Admin login
                printf("\n");
                if (adminLogin(adminPasswd)) {
                    printAllFlights(flight1, flight2, flight3);
                    totalRevenue = getTotalRevenue(flight1, flight2, flight3);
                    printf("\nYour total earnings from all the flights: "
                           GREEN("$%d") "\n", totalRevenue);
                    printf("\nYou have been logged out!\n");
                }
                break;
            case 2:  // Reserve a seat
                // Get the user's name
                printf("\nEnter your first name: ");
                printf(YELLOW);
                getSafeString(name, MAX);
                printf(RESET "\n");
                // Get the user's flight choice
                flightChoice = getFlightChoice();
                printf("\n");
                // Reserve a user-chosen seat in the correct flight
                // Print the success message
                // Print the user's e-ticket number
                char *success_fmt = "\nCongrats, %s! Your seat on flight %s has been reserved.\n";
                switch (flightChoice) {
                    case 1:
                        seatReservation(flight1);
                        printf(success_fmt, name, num1);
                        printMessage(name, num1);
                        break;
                    case 2:
                        seatReservation(flight2);
                        printf(success_fmt, name, num2);
                        printMessage(name, num2);
                        break;
                    default:
                        seatReservation(flight2);
                        printf(success_fmt, name, num2);
                        printMessage(name, num3);
                        break;
                }
                break;
            default:  // Quit
                printf("\nTerminating the program ...\n");
                printf("Thank you for using Mizzou Airline Booking System\n");
                return 0;
        }
    }
}
