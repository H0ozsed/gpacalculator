#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_grade_points(char grade) {
    switch (grade) {
        case 'A': return 4;
        case 'B': return 3;
        case 'C': return 2;
        case 'D': return 1;
        case 'E': return 0;
        default: return -1; // Invalid grade
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No arguments passed, print error code 84 and exit
        write(2, "Error: No input arguments\n", 25);
        return 84;
    }

    double total_points = 0.0;
    int total_credits = 0;

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        char *grade_str = strtok(arg, ",");
        char *credit_str = strtok(NULL, ",");

        if (grade_str == NULL || credit_str == NULL) {
            // Invalid format, print error and exit
            write(2, "Error: Invalid argument format\n", 30);
            return 84;
        }

        char grade = grade_str[0]; // Take the first character as grade
        int credits = atoi(credit_str);
        
        // Handle invalid grade or credit value
        if (credits <= 0 || get_grade_points(grade) == -1) {
            write(2, "Error: Invalid grade or credit\n", 30);
            return 84;
        }

        total_points += get_grade_points(grade) * credits;
        total_credits += credits;
    }

    if (total_credits == 0) {
        write(2, "Error: No credits provided\n", 26);
        return 84;
    }

    // Calculate GPA and round to two decimal places
    double gpa = total_points / total_credits;
    printf("%.2f\n", gpa);

    return 0;
}

