/*
 * CST8234 - C Programming
 * Lab 1 - Problem 2
 * Student Name: Emmanuel Fofeyin
 * Date: 23/9/2026
 */

#include <stdio.h>

/* BMI category limits */
#define UNDERWEIGHT 18.5
#define NORMAL 25.0
#define OVERWEIGHT 30.0

int main(void)
{
    double weight;
    double height;
    double bmi;

    /* Get the user's weight and height */
    printf("Enter weight in kilograms: ");
    scanf("%lf", &weight);

    printf("Enter height in meters: ");
    scanf("%lf", &height);

    /* Calculate BMI */
    bmi = weight / (height * height);

    /* Display the BMI */
    printf("BMI = %.2f\n", bmi);

    /* Determine the BMI category */
    if (bmi < UNDERWEIGHT)
    {
        printf("Category: Underweight\n");
    }
    else if (bmi < NORMAL)
    {
        printf("Category: Normal weight\n");
    }
    else if (bmi < OVERWEIGHT)
    {
        printf("Category: Overweight\n");
    }
    else
    {
        printf("Category: Obese\n");
    }

    /* Return 0 to indicate successful program execution */
    return 0;
}