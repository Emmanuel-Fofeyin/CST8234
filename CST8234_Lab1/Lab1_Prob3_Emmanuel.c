/*
 * CST8234 - C Programming
 * Lab 1 - Problem 3
 * Student Name: Emmanuel Fofeyin
 */

#include <stdio.h>

/* Macros for leap year rules */
#define DIV4 4
#define DIV100 100
#define DIV400 400

int main(void)
{
    int year;
    int isLeapYear;

    /* Get the year from the user */
    printf("Enter year: ");
    scanf("%d", &year);

    /* Check if the year is a leap year */
    if ((year % DIV4 == 0 && year % DIV100 != 0) || (year % DIV400 == 0))
    {
        isLeapYear = 1;
    }
    else
    {
        isLeapYear = 0;
    }

    /* Display the result */
    if (isLeapYear)
    {
        printf("%d is a Leap Year.\n", year);
    }
    else
    {
        printf("%d is not a Leap Year.\n", year);
    }

    return 0;
}