// Nelson Earle (nwewnh)
// HW3

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 255

#define RESET     "\33[0m"
#define BOLD(x)   "\33[1m" x RESET
#define BLUE(x)   "\33[94m" x RESET
#define GREEN(x)  "\33[92m" x RESET

char *USAGE = "Usage: %s <infile> <outfile>\n";


/**
 * Print a message to stderr.
 */
void err_msg(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}


/**
 * Return whether a file with the given name exists.
 */
int file_exists(char *fn) {
    return access(fn, F_OK) == 0;
}


/**
 * Returns whether the user has permissions to a file with the given name.
 * The second argument is a string containing any combination of "r", "w", and
 * "x". If any other character is found in that string, -1 is returned. If the
 * user does not have the specified permissions, 0 is returned. Otherwise, 1 is
 * returned.
 */
int has_permissions(char *fn, char *permissions) {
    for (int i=0; permissions[i]; i++) {
        if (permissions[i] == 'r') {
            if (access(fn, R_OK) != 0)
                return 0;
        } else if (permissions[i] == 'w') {
            if (file_exists(fn) && access(fn, W_OK) != 0)
                return 0;
        } else if (permissions[i] == 'x') {
            if (access(fn, X_OK) != 0)
                return 0;
        } else {
            return -1;
        }
    }
    return 1;
}


/**
 * Return the number of lines in a file with the given name.
 */
int get_record_count(char *infn) {
    int nlines = 0;

    FILE *infp = fopen(infn, "r");
    if (infp == NULL)
        return -1;

    char buff[MAX_LINE_LENGTH];
    while (1) {
        if (fgets(buff, MAX_LINE_LENGTH, infp) == NULL) {
            if (feof(infp))
                break;
            else
                return -2;
        }
        nlines++;
    }

    fclose(infp);

    return nlines;
}


/**
 * Read len lines of data from a file named infn into the given arrays.
 */
int load_data(char *infn, int *accounts, float *balances, int len) {
    FILE *infp = fopen(infn, "r");
    if (infp == NULL)
        return 0;

    // TODO: factor out the acct and bal vars
    int count = 0;
    int acct;
    float bal;
    while (1) {
        if (fscanf(infp, "%d %f", &acct, &bal) != 2) {
            if (feof(infp))
                break;
            else
                return -1;
        }
        accounts[count] = acct;
        balances[count++] = bal;
    }

    fclose(infp);

    return 1;
}


/**
 * Print out the arrays in a chart.
 */
void print_data(int *accounts, float *balances, int len) {
    printf(BOLD("Account No.") "   " BOLD("Balance") "\n");
    for (int i=0; i<len; i++)
        printf("%-*d   %*.2f\n",
               11, accounts[i],
               7, balances[i]);
}


/**
 * Return the index of the highest balance in the given array.
 */
int highest_amount(float *balances, int len) {
    int max_i = 0;
    for (int i=0; i<len; i++)
        if (balances[i] > balances[max_i])
            max_i = i;
    return max_i;
}


/**
 * Return the index of the lowest balance in the given array.
 */
int lowest_amount(float *balances, int len) {
    int min_i = 0;
    for (int i=0; i<len; i++)
        if (balances[i] < balances[min_i])
            min_i = i;
    return min_i;
}


/**
 * Return the average of the given array.
 */
float average_amount(float *balances, int len) {
    float sum = 0.0;
    for (int i=0; i<len; i++)
        sum += balances[i];
    return (float) sum / len;
}


/**
 * Write the given data to a file named outfn.
 */
int write_data(char *outfn, int *accounts, float *balances, int len, int max_i,
               int min_i, float average) {
    FILE *outfp = fopen(outfn, "w");
    if (outfp == NULL)
        return 0;

    for (int i=0; i<len; i++)
        fprintf(outfp, "%d %.2f\n", accounts[i], balances[i]);

    fprintf(outfp, "Account %d has the highest balance of %.2f\n",
            accounts[max_i], balances[max_i]);
    fprintf(outfp, "Account %d has the lowest balance of %.2f\n",
            accounts[min_i], balances[min_i]);
    fprintf(outfp, "The average balance is %.2f\n", average);

    fclose(outfp);

    return 1;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        err_msg(USAGE, argv[0]);
        return 1;
    }

    char *infn = argv[1];
    char *outfn = argv[2];

    if (! file_exists(infn)) {
        err_msg("Infile does not exist: %s\n", infn);
        return 1;
    }

    if (! has_permissions(infn, "r")) {
        err_msg("Cannot read infile: %s\n", infn);
        return 1;
    }

    if (file_exists(outfn) && !has_permissions(outfn, "w")) {
        err_msg("Cannot write to outfile: %s\n", outfn);
        return 1;
    }

    int ret;
    int nlines = get_record_count(infn);
    if (nlines < 0) {
        err_msg("Could not open file: %s\n", infn);
        return 1;
    } else if (nlines == -2) {
        err_msg("Error reading from infile: %s\n", infn);
        return 1;
    }

    int exitstatus = 0;

    int *accounts = malloc(sizeof(int) * nlines);
    float *balances = malloc(sizeof(float) * nlines);

    ret = load_data(infn, accounts, balances, nlines);
    if (ret == 0) {
        err_msg("Could not open infile: %s\n", infn);
        exitstatus = 1;
        goto end;
    } else if (ret == -1) {
        err_msg("Invalid data in infile: %s\n", infn);
        exitstatus = 1;
        goto end;
    }

    printf("The file contains " BLUE("%d") " records.\n\n", nlines);

    print_data(accounts, balances, nlines);

    printf("\n");

    int max_i = highest_amount(balances, nlines);
    printf("Account " BLUE("%d") " has the highest balance of " GREEN("$%.2f") ".\n",
           accounts[max_i],
           balances[max_i]);

    int min_i = lowest_amount(balances, nlines);
    printf("Account " BLUE("%d") " has the lowest balance of " GREEN("$%.2f") ".\n",
           accounts[min_i],
           balances[min_i]);

    float avg_bal = average_amount(balances, nlines);
    printf("The average balance is " GREEN("$%.2f") ".\n", avg_bal);

    ret = write_data(outfn, accounts, balances, nlines, max_i, min_i, avg_bal);
    if (!ret) {
        err_msg("Could not open outfile: %s\n", outfn);
        exitstatus = 1;
        goto end;
    }

    end:
        free(accounts);
        free(balances);
        return exitstatus;
}
