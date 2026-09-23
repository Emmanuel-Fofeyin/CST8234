/*
 * CST8234 - C Programming
 * Lab 1 - Problem 3
 * Student Name: Emmanuel Fofeyin
 * Date: 23/9/2026
 */

#include <stdio.h>

/* Macros representing the mathematical divisors for leap year rules */
#define DIV4 4
#define DIV100 100
#define DIV400 400

int main(void)
{
    /* Variable declarations for the target year and the boolean flag (1 for true, 0 for false) */
    int year;
    int isLeapYear;

    /* Prompt the user to input a year and store it in the year variable */
    printf("Enter year: ");
    scanf("%d", &year);

    /* 
     * Check if the year is a leap year
     * 1. Divisible by 4 AND NOT divisible by 100, OR
     * 2. Divisible by 400
     */
    if ((year % DIV4 == 0 && year % DIV100 != 0) || (year % DIV400 == 0))
    {
        isLeapYear = 1; // Set flag to true
    }
    else
    {
        isLeapYear = 0; // Set flag to false
    }

    /* Display the final result to the user based on the isLeapYear flag */
    if (isLeapYear)
    {
        printf("%d is a Leap Year.\n", year);
    }
    else
    {
        printf("%d is not a Leap Year.\n", year);
    }

    /* Return 0 to indicate successful program execution */
    return 0;
}