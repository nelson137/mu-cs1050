// Nelson Earle (nwewnh)
// LAB_11

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MIN        1
#define MAX       22
#define MAX_NAME  64

#define RESET    "\33[0m"
#define YELLOW   "\33[93m"


char *USAGE = "Usage: %s <infile>\n";

typedef struct {
    char name[MAX_NAME];
    int id;
    int grade;
} Student;

Student INFO[MAX];


/**
 * Print an error message to stderr and exit.
 */
void die(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}


/**
 * Return the number of digits in num.
 */
int numLen(int num) {
    return log10(num) + 1;
}


void spacer(void) {
    for (int i=0; i<79; i++)
        printf("=");
    printf("\n");
}


/**
 * Return an integer from the user.
 */
int get_num(int *num) {
    int ret = 0;
    *num = 0;

    printf(YELLOW);

    // Read characters
    char c;
    do {
        c = getchar();
        if (c == '\n')
            break;
        if (!('0' <= c && c <= '9')) {
            ret = -1;
            // Eat trailing characters up to newline if non-digit is read
            while (c != '\n')
                c = getchar();
            break;
        }
        // Append digit to num
        *num *= 10;
        *num += c - '0';
    } while (1);

    printf(RESET);

    return ret;
}


int check_size(int size) {
    return MIN <= size && size <= MAX;
}


/**
 * Return the number of records in the infile entered from the user.
 */
void get_size(int *size) {
    int ret;

    spacer();
    printf("Enter the size of the input: ");

    do {
        ret = get_num(size);
        spacer();
        if (ret != -1 && check_size(*size)) {
            break;
        } else {
            printf("Invalid size entered! ");
            printf("The minimum is %d and the maximum is %d\n", MIN, MAX);
            spacer();
            printf("Please enter again: ");
        }
    } while (1);
}


/**
 * Load the data from the file into the struct array INFO.
 */
void load_structdata(char *fn, int size) {
    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        die("Could not open file: %s\n", fn);

    for (int i=0; i<size; i++) {
        Student s;
        if (fscanf(fp, "%s\t%d\t%d\n", s.name, &s.id, &s.grade) != 3)
            die("Data in file has invalid format: %s\n", fn);
        INFO[i] = s;
    }

    if (!feof(fp))
        die("Too many records in file: %s\n", fn);

    fclose(fp);
}


/**
 * Print out the struct array INFO.
 */
void print_data(int size) {
    int n_len, longest_name = 4;
    int i_len, longest_id = 2;
    for (int i=0; i<size; i++) {
        n_len = strlen(INFO[i].name);
        i_len = numLen(INFO[i].id);
        if (n_len > longest_name)
            longest_name = n_len;
        if (i_len > longest_id)
            longest_id = i_len;
    }

    printf("Student Records\n\n");
    printf("s/no    Name%*s    Id%*s    Grade\n",
           longest_name-4, " ", longest_id-2, " ");
    char *name;
    int id, grade;
    for (int i=0; i<size; i++) {
        name = INFO[i].name, id = INFO[i].id, grade = INFO[i].grade;
        printf("%2d      %-*s    %-*d    %d\n",
               i+1,
               longest_name, name,
               longest_id, id,
               grade);
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2)
        die(USAGE, argv[0]);

    char *infile = argv[1];

    if (access(infile, F_OK) != 0)
        die("File does not exist: %s\n", infile);

    int size;
    get_size(&size);

    load_structdata(infile, size);

    printf("\n");
    print_data(size);

    return 0;
}
