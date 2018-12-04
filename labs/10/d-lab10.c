// Nelson Earle (nwewnh)
// LAB_10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define RESET    "\33[0m"
#define YELLOW   "\33[93m"
#define RED(x)   "\33[91m" x RESET
#define BLUE(x)  "\33[94m" x RESET


/**
 * Return whether the given character is an uppercase alphabet character.
 */
int isalphaUpper(char c) {
    return 'A' <= c && c <= 'Z';
}


/**
 * Return whether the given character is a lowercase alphabet character.
 */
int isalphaLower(char c) {
    return 'a' <= c && c <= 'z';
}


/**
 * Check that the given string is valid.
 * Valid strings contain only alphabet characters (a-zA-Z) and the null terminator.
 */
int checkString(char *str, int len) {
    for (int i=0; i<len; i++) {
        if (*(str+i) == '\0')
            break;
        if (!isalphaUpper(*(str+i)))
            return 0;
    }
    return 1;
}


/**
 * Return an integer from the user between 1 and 20, inclusive.
 */
int getSize(void) {
    int is_valid, num;
    char c;

    printf("Enter the size of the string: ");

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

        if (is_valid && 1 <= num && num <= 20)
            return num;
        else
            printf("Size must be between 1 and 20. Try again: ");
    } while (1);
}


/**
 * Convert all lowercase characters of the given string to uppercase.
 */
void upper(char *str, int len) {
    for (int i=0; i<len; i++) {
        if (isalphaLower(*(str+i)))
            *(str+i) -= 32;
    }
}


/**
 * Read a string of length len into the given char*.
 * Return 0 if the string was too long, else 1.
 */
int readString(char *str, int len) {
    len += 1;  // For the newline
    int index = 0;
    int toolong = 0;
    char c = '\n';

    printf(YELLOW);

    // Eat leading newlines
    while (c == '\n')
        c = getc(stdin);

    while (c != '\n') {
        if (index >= len-1 && !toolong)
            toolong = 1;
        if (c != '\n' && index < len-1)
            *(str+index) = c;
        index++;
        c = getc(stdin);
    }
    *(str+index) = '\0';

    // Eat trailing newlines
    while (c != '\n')
        c = getc(stdin);

    printf(RESET);

    return !toolong;
}


int getString(char *str) {
    int len = getSize();

    printf("\nPlease enter the string: ");
    do {
        if (readString(str, len)) {
            upper(str, len);
            if (checkString(str, len))
                break;
        } else {
            printf("The string entered is too long\n");
        }

        printf("Please enter a valid string: ");
    } while (1);

    return len;
}


/**
 * Caesarian cipher the given string.
 */
void cipherString(char *str, int len, int shift) {
    for (int i=0; i<len; i++) {
        if (*(str+i) == '\0')
            break;
        *(str+i) = (*(str+i) - 'A' + shift) % 26;
        if (*(str+i) < 0)
            *(str+i) += 26;
        *(str+i) += 'A';
    }
}


/**
 * Encrypt the given string, ask the user to guess the key.
 */
void guessCipherKey(char *str, int len) {
    int shift = (rand() % 26) + 1;

    char *copy = malloc(sizeof(str));
    strcpy(copy, str);

    cipherString(str, len, shift);

    printf("The ciphered string is "BLUE("%s")", what is the cipher key: ",
           str);

    int guess;
    do {
        printf(YELLOW);
        scanf("%d", &guess);
        printf(RESET);

        if (!(1 <= guess && guess <= 25)) {
            printf("The cipher key is between 1 and 25. Try again: ");
            continue;
        }

        cipherString(str, len, -1*shift);
        printf("The ciphered string shifted back "BLUE("%d")" is "BLUE("%s")
               ", ", guess, copy);
        cipherString(str, len, shift);

        if (guess == shift) {
            printf("correct!\n");
            break;
        } else {
            printf("incorrect!\n");
        }

        printf("The ciphered string is "BLUE("%s")", what is the cipher key: ",
               str);
    } while (1);
}


/**
 * Return the sum of the ASCII values of each letter in the given string.
 */
int stringSum(char *str, int len) {
    int sum = 0;
    for (int i=0; i<len; i++)
        sum += *(str+i);
    return sum;
}


int main(void) {
    srand(time(NULL));

    char *str = malloc(sizeof(char) * 20);
    int len = getString(str);

    printf("\nYou entered: " BLUE("%s") " which has a len of " BLUE("%d") "\n",
           str, len);

    printf("\n");

    guessCipherKey(str, len);

    printf("The sum of the ASCII values of the string is " BLUE("%d") "\n",
           stringSum(str, len));

    printf("\n***** BONUS *****\n");
    printf("The ctype.h library was not used\n");

    return 0;
}
