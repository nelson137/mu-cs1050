// Nelson Earle (nwewnh)
// LAB_11

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MIN        4
#define MAX       40
#define MAX_NAME  32

#define RESET    "\33[0m"
#define YELLOW   "\33[93m"


char *USAGE = "Usage: %s <infile>\n";

typedef struct {
    char county[MAX_NAME];
    int zipcode;
    char city[MAX_NAME];
    int group;
} County;

County DATA[MAX];
char *GROUP_CITIES[MAX];
int GROUP_CITIES_C;


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


void load_data(char *fn, int size) {
    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        die("Could not open file: %s\n", fn);

    for (int i=0; i<size; i++) {
        County c;
        if (fscanf(fp, "%s\t%d\t%s\n", c.county, &c.zipcode, c.city) != 3)
            die("Data in file has invalid format: %s\n", fn);
        DATA[i] = c;
    }

    fclose(fp);

    int cn_len, longest_county = 6;
    int zc_len, longest_zipcode = 7;
    for (int i=0; i<size; i++) {
        cn_len = strlen(DATA[i].county);
        zc_len = numLen(DATA[i].zipcode);
        if (cn_len > longest_county)
            longest_county = cn_len;
        if (zc_len > longest_zipcode)
            longest_zipcode = zc_len;
    }

    printf("s/no    %-*s    %-*s    City\n",
           longest_county, "County",
           longest_zipcode, "Zipcode");
    for (int i=0; i<size; i++)
        printf("%2d      %-*s    %-*d    %s\n",
               i+1,
               longest_county, DATA[i].county,
               longest_zipcode, DATA[i].zipcode,
               DATA[i].city);
}


void classify(char *fn, int size) {
    int cn_len, longest_county = 6;
    int zc_len, longest_zipcode = 7;
    int ci_len, longest_city = 6;
    for (int i=0; i<size; i++) {
        cn_len = strlen(DATA[i].county);
        zc_len = numLen(DATA[i].zipcode);
        ci_len = strlen(DATA[i].city);
        if (cn_len > longest_county)
            longest_county = cn_len;
        if (zc_len > longest_zipcode)
            longest_zipcode = zc_len;
        if (ci_len > longest_city)
            longest_city = ci_len;
    }

    printf("s/no    %-*s    %-*s    %-*s   Group\n",
           longest_county, "County",
           longest_zipcode, "Zipcode",
           longest_city, "City");

    int zc;
    for (int i=0; i<size; i++) {
        zc = DATA[i].zipcode;
        if (63000 <= zc && zc <= 63999)
            DATA[i].group = 1;
        else if (64000 <= zc && zc <= 64999)
            DATA[i].group = 2;
        else if (65000 <= zc && zc <= 66000)
            DATA[i].group = 3;
        else
            die("Cannot classify zipcode: %d\n", zc);

        printf("%2d      %-*s    %-*d    %-*s   %d\n",
               i+1,
               longest_county, DATA[i].county,
               longest_zipcode, DATA[i].zipcode,
               longest_city, DATA[i].city,
               DATA[i].group);
    }
}


int check_group(int group) {
    return 1 <= group && group <= 3;
}


/**
 * Return the number of records in the infile entered from the user.
 */
void get_group(int *size) {
    int ret;

    spacer();
    do {
        printf("Enter the group number: ");
        ret = get_num(size);
        spacer();
        if (ret != -1 && check_group(*size)) {
            break;
        } else {
            printf("Invalid group number entered! ");
            printf("The minimum is 1 and the maximum is 3\n");
            spacer();
        }
    } while (1);
}


int city_frequency(char *city, int size) {
    int freq = 0;
    for (int i=0; i<GROUP_CITIES_C; i++) {
        if (strcmp(city, GROUP_CITIES[i]) == 0)
            freq++;
    }
    return freq;
}


void frequency(char *fn, int size, int group) {
    int cities_to_freq = GROUP_CITIES_C > 3 ? 3 : GROUP_CITIES_C;
    int c_len, longest_city = 4;
    for (int i=0; i<cities_to_freq; i++) {
        c_len = strlen(GROUP_CITIES[i]);
        if (c_len > longest_city)
            longest_city = c_len;
    }

    printf("Frequency Table...\n\n");
    printf("s/no    %-*s    Frequency\n", longest_city, "City");
    for (int i=0; i<cities_to_freq; i++)
        printf("%2d      %-*s    %d\n",
               i+1,
               longest_city, GROUP_CITIES[i],
               city_frequency(GROUP_CITIES[i], size));
}


int main(int argc, char *argv[]) {
    if (argc != 2)
        die(USAGE, argv[0]);

    char *infile = argv[1];

    if (access(infile, F_OK) != 0)
        die("File does not exist: %s\n", infile);

    int size;
    get_size(&size);

    load_data(infile, size);

    spacer();

    classify(infile, size);

    spacer();

    int g1_count = 0;
    int g2_count = 0;
    int g3_count = 0;
    for (int i=0; i<size; i++) {
        if (DATA[i].group == 1)
            g1_count++;
        else if (DATA[i].group == 2)
            g2_count++;
        else if (DATA[i].group == 3)
            g3_count++;
    }
    printf("Number of cities in group %d: %d\n", 1, g1_count);
    printf("Number of cities in group %d: %d\n", 2, g2_count);
    printf("Number of cities in group %d: %d\n", 3, g3_count);

    int group;
    get_group(&group);

    printf("Cities in group %d...\n", group);
    GROUP_CITIES_C = 0;
    for (int i=0; i<size; i++) {
        if (DATA[i].group == group) {
            GROUP_CITIES[GROUP_CITIES_C++] = DATA[i].city;
            printf("[%d]   %s\n", GROUP_CITIES_C, DATA[i].city);
        }
    }

    spacer();

    frequency(infile, size, group);

    return 0;
}
