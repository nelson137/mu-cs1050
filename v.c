#define _POSIX_C_SOURCE 199309L

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define ARRLEN(x)  sizeof(x)/sizeof(x[0])

#define RESET  "\33[0m"
#define RED    "\33[91m"
#define GREEN  "\33[92m"


void handle_sigint(int sig) {
    printf("\n\n");
    fprintf(stderr, RED "Error: Interrupt (^C) not available during "
            "installation process" RESET);
    printf("\33[2A");
}


void handle_sigtstp(int sig) {
    printf("\n\n");
    fprintf(stderr, RED "Error: Suspend (^Z) not available during "
            "installation process" RESET);
    printf("\33[2A");
}


void install_virus(void) {
    // Trap interrupt signal (^C)
    struct sigaction act = {.sa_handler = handle_sigint};
    sigaction(SIGINT, &act, NULL);
    // Trap terminal stop signal (^Z)
    act.sa_handler = handle_sigtstp;
    sigaction(SIGTSTP, &act, NULL);

    // Disable stty echo
    struct termios t, oldt;
    tcgetattr(STDIN_FILENO, &t);
    oldt = t;
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Payload
    int message[] = {89, 79, 85, 39, 86, 69, 32, 66, 69, 69, 78, 32, 80, 87, 78, 69, 68, 10,
                     72, 65, 80, 80, 89, 32, 72, 65, 76, 76, 79, 87, 69, 69, 78, 33, 10};

    // Write the payload to a file
    char fn[] = {112, 119, 110, 101, 100};  // Filename

    // Return if the payload file exists
    if (access(fn, F_OK) == 0)
        return;

    FILE *f = fopen(fn, "w");
    if (f == NULL)
        return;
    for (int i=0; i<ARRLEN(message); i++)
        fprintf(f, "%c", message[i]);
    fclose(f);

    // Current terminal width
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int cols = w.ws_col;

    int iters = 40;  // How many times to update progress bar
    int percent, spaces, num_eq;
    int width = (cols - 27 - 2) * 0.85;
    // The loading spinner after the progress bar
    char spinner[] = "/-\\|";
    // How long to sleep between iterations
    struct timespec ts = {.tv_nsec = 80*1000*1000};
    // Holds remaining time to sleep if sleep get's interruped by signal
    struct timespec r = {};

    for (int i=0; i<=iters; i++) {
        // Reset cursor position
        printf("\r\33[2K");

        // Progress percentage
        percent = 100 * i / iters;
        // The number of spaces to put in front of percent
        spaces = percent==0 ? 2 : 3 - ( floor(log10(percent)) + 1 );
        // The number of equals signs to print in the progress bar
        num_eq = width * i / iters;

        printf("Installing Virus: ");
        // Print the progress percentage
        printf("%*s%d%% [", spaces, "", percent);
        // Make the progress bar green
        printf(GREEN);
        // Print the equals signs
        for (int j=0; j<num_eq; j++)
            printf("=");
        printf(RESET);
        // Print the spaces after the equals signs
        for (int j=0; j<width-num_eq; j++)
            printf(" ");
        printf("]");
        // Print the spinner if not "complete"
        if (percent < 100)
            printf(" %c", spinner[i%4]);

        fflush(stdout);

        // Resume nanosleep if a signal interrupts the sleep
        while (nanosleep(&ts, &r) == -1)
            nanosleep(&r, &r);
    }
    printf("\n\n\n\n");

    system("ls -l ./pwned");

    // Reset stty settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}


int main(void) {
    install_virus();
    return 0;
}
