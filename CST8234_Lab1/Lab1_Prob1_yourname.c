/*
 * CST8234 - C Programming
 * Lab 1 - Problem 1
 * Student Name: Emmanuel Fofeyin
 */

#include <stdio.h>

/* Macros for operation choices */
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

int main(void)
{
    int firstNum;
    int secondNum;
    int choice;
    int result;

    /* Get two numbers from the user */
    printf("Enter first number: ");
    scanf("%d", &firstNum);

    printf("Enter second number: ");
    scanf("%d", &secondNum);

    /* Ask which operation to perform */
    printf("Select operation (1 for ADD, 2 for SUB, 3 for MUL, 4 for DIV): ");
    scanf("%d", &choice);

    /* Perform the selected operation */
    switch (choice)
    {
        case ADD:
            result = firstNum + secondNum;
            printf("Result: %d + %d = %d\n", firstNum, secondNum, result);
            break;

        case SUB:
            result = firstNum - secondNum;
            printf("Result: %d - %d = %d\n", firstNum, secondNum, result);
            break;

        case MUL:
            result = firstNum * secondNum;
            printf("Result: %d * %d = %d\n", firstNum, secondNum, result);
            break;

        case DIV:
            if (secondNum == 0)
            {
                printf("Error: Division by zero is not allowed!\n");
            }
            else
            {
                result = firstNum / secondNum;
                printf("Result: %d / %d = %d\n", firstNum, secondNum, result);
            }
            break;

        default:
            printf("Error: Invalid operation selected!\n");
    }

    return 0;
}