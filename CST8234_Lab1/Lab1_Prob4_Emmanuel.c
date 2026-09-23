```c
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

    /* Get the number of Fibonacci terms */
    printf("Enter the value of N: ");
    scanf("%d", &n);

    /* Print the Fibonacci sequence */
    printf("Fibonacci Sequence up to %dth term: ", n);

    if (n >= 1)
    {
        printf("0");
    }

    if (n >= 2)
    {
        printf(" 1");

        for (i = 2; i < n; i++)
        {
            next = previous + current;
            printf(" %d", next);

            previous = current;
            current = next;
        }
    }

    printf("\n");

    return 0;
}
```
