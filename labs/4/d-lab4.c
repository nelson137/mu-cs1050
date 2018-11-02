// Nelson Earle (nwewnh)
// LAB_4

#include <stdio.h>

#define SPACER "================================================"


// Check that the number of courses is greater than 1
int courseNumCheck(int num) {
    return num > 1;
}


// Get the number of courses being taken from the user
int getNumCourses(void) {
    // Print the primary prompt
    printf("Enter the number of courses: ");
    int n_courses;
    do {
        // Get user input
        scanf("%d", &n_courses);
        // Validate input
        if (courseNumCheck(n_courses))
            return n_courses;
        else
            printf("Error! Please enter a number of courses greater than 1: ");
    } while (1);
}


// Check that the course score is between 0 and 100, inclusive
int scoreErrorCheck(float score) {
    return 0 <= score && score <= 100;
}


// Get the course score from the user
float getScore(void) {
    int score;
    scanf("%d", &score);
    return (float)score;
}


// Check that the course unit is greater than 0
int unitErrorCheck(int unit) {
    return unit > 0;
}


// Get the course unit from the user
int getUnit(void) {
    int unit;
    scanf("%d", &unit);
    return unit;
}


// Return the equivalent grade point for a course score
int getScorePoint(float score) {
    switch ((int)score) {
        case 90 ... 100:
            return 4;
        case 80 ... 89:
            return 3;
        case 70 ... 79:
            return 2;
        case 60 ... 69:
            return 1;
        default:  // 0 ... 60
            return 0;
    }
}


// *** BONUS ***
// Return the SCU of a course
int computeSCU(float scp, int unit) {
    return (int)scp * unit;
}


// Comment on the GPA of a student
void printComment(float full_gpa) {
    int gpa = full_gpa * 100;
    char *comment;

    switch (gpa) {
        case 380 ... 400:
            comment = "Outstanding!";
            break;
        case 350 ... 379:
            comment = "Excellent!";
            break;
        case 300 ... 349:
            comment = "Good.";
            break;
        case 250 ... 299:
            comment = "Satisfactory.";
            break;
        case 200 ... 249:
            comment = "Not satisfactory.";
            break;
        default:  // 0 ... 199
            comment = "Do better next semester.";
            break;
    }

    puts(SPACER);
    printf("COMMENT: %s\n", comment);
    puts(SPACER);
}


int main(void) {
    puts(SPACER);
    puts("STUDENT ASP CALCULATOR");
    puts(SPACER);

    puts("");

    // Get the number of courses
    int n_courses = getNumCourses();

    puts("");

    int score, unit, scu, total_scu = 0, total_units = 0;
    float scp;
    for (int i=0; i<n_courses; i++) {
        // Get the course score
        printf("Enter the student score for course %d (percent): ", i+1);
        do {
            score = getScore();
            if (scoreErrorCheck(score))
                break;
            else
                printf("Error! Please enter a valid course score: ");
        } while(1);

        // Get the course unit
        printf("Enter the number of units for course %d: ", i+1);
        do {
            unit = getUnit();
            if (unitErrorCheck(unit))
                break;
            else
                printf("Error! Please enter a course unit greater than zero: ");
        } while(1);

        scp = (float) getScorePoint(score);
        scu = computeSCU(scp, unit);
        printf("MULTIPLICATION OF SCP AND CU: %d\n", scu);
        total_scu += scu;
        total_units += unit;

        puts("");
    }

    // Calculate and print the student's GPA
    float gpa = (float) total_scu/total_units;
    printf("The student GPA: %.2f\n\n", gpa);

    // Comment on the student's GPA
    printComment(gpa);

    return 0;
}
