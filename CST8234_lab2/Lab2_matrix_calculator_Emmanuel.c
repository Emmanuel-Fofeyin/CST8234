/*
 * Name: Emmanuel Fofeyin
 * Student Number: 041161315
 * Course: CST8234 - C Programming
 * Lab 2: Matrix Calculator
 * Lab Section: 300_301
 *
 * Description:
 * This program is a menu-driven matrix calculator.
 * It uses dynamically allocated 2D arrays, pointers,
 * pointer dereferencing, and dynamic memory management.
 */

#include <stdio.h>
#include <stdlib.h>

/* Function prototypes */
void clearInputBuffer(void);
int getPositiveInteger(const char *message);
int getNonNegativeInteger(const char *message);
int **allocateMatrix(int rows, int columns);
void freeMatrix(int **matrix, int rows);
void inputMatrix(int **matrix, int rows, int columns);
void displayMatrix(int **matrix, int rows, int columns);
int **addMatrices(int **matrixA, int **matrixB,
                  int rows, int columns);
int **multiplyMatrices(int **matrixA, int rowsA, int columnsA,
                       int **matrixB, int rowsB, int columnsB);
int **scalarMultiply(int **matrix, int rows, int columns, int scalar);

int main(void)
{
    char choice;

    int **matrixA;
    int **matrixB;
    int **result;

    int rowsA;
    int columnsA;
    int rowsB;
    int columnsB;

    int rows;
    int columns;
    int scalar;

    matrixA = NULL;
    matrixB = NULL;
    result = NULL;

    do
    {
        printf("\nMatrix Calculator Menu:\n");
        printf("1. Add Matrices\n");
        printf("2. Multiply Matrices\n");
        printf("3. Evaluate Matrix by Scalar\n");
        printf("X. Exit\n");

        printf("Enter your choice (1/2/3/X): ");

        if (scanf(" %c", &choice) != 1)
        {
            clearInputBuffer();
            choice = '\0';
        }

        clearInputBuffer();

        if (choice == '1')
        {
            printf("\n--- Matrix Addition ---\n");

            rowsA = getPositiveInteger("Enter rows for first matrix: ");
            columnsA = getPositiveInteger("Enter columns for first matrix: ");

            matrixA = allocateMatrix(rowsA, columnsA);

            if (matrixA == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                continue;
            }

            inputMatrix(matrixA, rowsA, columnsA);

            rowsB = getPositiveInteger("Enter rows for second matrix: ");
            columnsB = getPositiveInteger("Enter columns for second matrix: ");

            matrixB = allocateMatrix(rowsB, columnsB);

            if (matrixB == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                freeMatrix(matrixA, rowsA);
                matrixA = NULL;
                continue;
            }

            inputMatrix(matrixB, rowsB, columnsB);

            if (rowsA != rowsB || columnsA != columnsB)
            {
                printf("Error: Matrix addition not possible.\n");
                printf("Both matrices must have the same dimensions.\n");
            }
            else
            {
                result = addMatrices(matrixA, matrixB, rowsA, columnsA);

                if (result == NULL)
                {
                    printf("Error: Memory allocation failed.\n");
                }
                else
                {
                    printf("\nSum of the matrices:\n");
                    displayMatrix(result, rowsA, columnsA);

                    freeMatrix(result, rowsA);
                    result = NULL;
                }
            }

            freeMatrix(matrixA, rowsA);
            freeMatrix(matrixB, rowsB);

            matrixA = NULL;
            matrixB = NULL;
        }
        else if (choice == '2')
        {
            printf("\n--- Matrix Multiplication ---\n");

            rowsA = getPositiveInteger("Enter rows for first matrix: ");
            columnsA = getPositiveInteger("Enter columns for first matrix: ");

            matrixA = allocateMatrix(rowsA, columnsA);

            if (matrixA == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                continue;
            }

            inputMatrix(matrixA, rowsA, columnsA);

            rowsB = getPositiveInteger("Enter rows for second matrix: ");
            columnsB = getPositiveInteger("Enter columns for second matrix: ");

            matrixB = allocateMatrix(rowsB, columnsB);

            if (matrixB == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                freeMatrix(matrixA, rowsA);
                matrixA = NULL;
                continue;
            }

            inputMatrix(matrixB, rowsB, columnsB);

            if (columnsA != rowsB)
            {
                printf("Error: Matrix multiplication not possible.\n");
                printf("Columns of the first matrix must equal ");
                printf("rows of the second matrix.\n");
            }
            else
            {
                result = multiplyMatrices(matrixA, rowsA, columnsA,
                                          matrixB, rowsB, columnsB);

                if (result == NULL)
                {
                    printf("Error: Memory allocation failed.\n");
                }
                else
                {
                    printf("\nResult of matrix multiplication:\n");
                    displayMatrix(result, rowsA, columnsB);

                    freeMatrix(result, rowsA);
                    result = NULL;
                }
            }

            freeMatrix(matrixA, rowsA);
            freeMatrix(matrixB, rowsB);

            matrixA = NULL;
            matrixB = NULL;
        }
        else if (choice == '3')
        {
            printf("\n--- Scalar Evaluation ---\n");

            rows = getPositiveInteger("Enter rows for the matrix: ");
            columns = getPositiveInteger("Enter columns for the matrix: ");

            matrixA = allocateMatrix(rows, columns);

            if (matrixA == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                continue;
            }

            inputMatrix(matrixA, rows, columns);

            scalar = getNonNegativeInteger("Enter scalar value: ");

            result = scalarMultiply(matrixA, rows, columns, scalar);

            if (result == NULL)
            {
                printf("Error: Memory allocation failed.\n");
            }
            else
            {
                printf("\nResulting matrix after scalar multiplication:\n");
                displayMatrix(result, rows, columns);

                freeMatrix(result, rows);
                result = NULL;
            }

            freeMatrix(matrixA, rows);
            matrixA = NULL;
        }
        else if (choice == 'X' || choice == 'x')
        {
            printf("\nExiting Matrix Calculator.\n");
        }
        else
        {
            printf("Error: Invalid menu choice.\n");
            printf("Please enter 1, 2, 3, or X.\n");
        }

    } while (choice != 'X' && choice != 'x');

    return 0;
}

/*
 * Clears unwanted characters from the input buffer.
 */
void clearInputBuffer(void)
{
    int character;

    character = getchar();

    while (character != '\n' && character != EOF)
    {
        character = getchar();
    }
}

/*
 * Gets a positive integer from the user.
 */
int getPositiveInteger(const char *message)
{
    int value;
    int result;

    while (1)
    {
        printf("%s", message);

        result = scanf("%d", &value);

        if (result == 1 && value > 0)
        {
            clearInputBuffer();
            return value;
        }

        printf("Error: Please enter a valid positive integer.\n");
        clearInputBuffer();
    }
}

/*
 * Gets a non-negative integer from the user.
 */
int getNonNegativeInteger(const char *message)
{
    int value;
    int result;

    while (1)
    {
        printf("%s", message);

        result = scanf("%d", &value);

        if (result == 1 && value >= 0)
        {
            clearInputBuffer();
            return value;
        }

        printf("Error: Please enter a valid non-negative integer.\n");
        clearInputBuffer();
    }
}

/*
 * Dynamically allocates a 2D matrix using int **.
 */
int **allocateMatrix(int rows, int columns)
{
    int **matrix;
    int i;

    matrix = (int **)malloc(rows * sizeof(int *));

    if (matrix == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(columns * sizeof(int));

        if (matrix[i] == NULL)
        {
            while (i > 0)
            {
                i--;
                free(matrix[i]);
            }

            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

/*
 * Frees all memory used by a matrix.
 */
void freeMatrix(int **matrix, int rows)
{
    int i;

    if (matrix != NULL)
    {
        for (i = 0; i < rows; i++)
        {
            free(matrix[i]);
        }

        free(matrix);
    }
}

/*
 * Gets the elements of a matrix from the user.
 */
void inputMatrix(int **matrix, int rows, int columns)
{
    int i;
    int j;

    printf("Enter elements of the matrix:\n");

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            while (1)
            {
                printf("Enter element [%d][%d]: ", i, j);

                if (scanf("%d", &matrix[i][j]) == 1 &&
                    matrix[i][j] >= 0)
                {
                    clearInputBuffer();
                    break;
                }

                printf("Error: Please enter a valid non-negative integer.\n");
                clearInputBuffer();
            }
        }
    }
}

/*
 * Displays a matrix in a tabular format.
 */
void displayMatrix(int **matrix, int rows, int columns)
{
    int i;
    int j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d", *(*(matrix + i) + j));

            if (j < columns - 1)
            {
                printf(" ");
            }
        }

        printf("\n");
    }
}

/*
 * Adds two matrices.
 */
int **addMatrices(int **matrixA, int **matrixB,
                  int rows, int columns)
{
    int **result;
    int i;
    int j;

    result = allocateMatrix(rows, columns);

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    return result;
}

/*
 * Multiplies two matrices.
 */
int **multiplyMatrices(int **matrixA, int rowsA, int columnsA,
                       int **matrixB, int rowsB, int columnsB)
{
    int **result;
    int i;
    int j;
    int k;

    (void)rowsB;

    result = allocateMatrix(rowsA, columnsB);

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rowsA; i++)
    {
        for (j = 0; j < columnsB; j++)
        {
            result[i][j] = 0;

            for (k = 0; k < columnsA; k++)
            {
                result[i][j] =
                    result[i][j] +
                    (*(*(matrixA + i) + k) *
                     *(*(matrixB + k) + j));
            }
        }
    }

    return result;
}

/*
 * Multiplies every element of a matrix by a scalar.
 */
int **scalarMultiply(int **matrix, int rows, int columns, int scalar)
{
    int **result;
    int i;
    int j;

    result = allocateMatrix(rows, columns);

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            result[i][j] = matrix[i][j] * scalar;
        }
    }

    return result;
}