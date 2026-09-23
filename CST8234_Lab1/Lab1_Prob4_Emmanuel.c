/*
 * CST8234 - C Programming
 * Lab 1 - Problem 4
 * Student Name: Emmanuel Fofeyin
 */

#include <stdio.h>

int main(void)
{
    int n;
    int previous = 0;
    int current = 1;
    int next;
    int i;

    /* Get the number of terms from the user */
    printf("Enter the value of N: ");
    scanf("%d", &n);

    /* Print the Fibonacci sequence */
    printf("Fibonacci Sequence up to %dth term: ", n);

    /* Print the first term */
    if (n >= 1)
    {
        printf("0");
    }

    /* Print the second term */
    if (n >= 2)
    {
        printf(" 1");

        /* Calculate and print the remaining terms */
        for (i = 2; i < n; i++)
        {
            next = previous + current;
            printf(" %d", next);

            /* Update the previous two terms */
            previous = current;
            current = next;
        }
    }

    printf("\n");
    
    /* Return 0 to indicate successful program execution */
    return 0;
}

