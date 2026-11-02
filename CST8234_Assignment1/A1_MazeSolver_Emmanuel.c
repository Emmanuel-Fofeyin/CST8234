
/*
    Name: Emmanuel Fofeyin
    Course: CST8234 - C Programming
    Assignment: Assignment 1 - Maze Solver
    Date: November 2, 2026
    Description: Solves a maze using dynamic memory allocation
                 and recursive backtracking.
*/

/* Include required libraries */

#include <stdio.h>      /* Input and output */
#include <stdlib.h>     /* malloc, free, strtol */
#include <string.h>     /* strlen, strcmp */
#include <limits.h>     /* INT_MAX */
#include <errno.h>      /* Checks for conversion errors */

/* Global variables */

/* Pointer to the dynamically allocated maze */
char **maze = NULL;

/* Stores the number of rows and columns */
int rows = 0;
int cols = 0;

/* Stores the starting position */
int startRow = 0;
int startCol = 0;

/* Stores the exit position */
int exitRow = 0;
int exitCol = 0;

/* Tracks whether a maze is loaded or solved */
int mazeLoaded = 0;
int mazeSolved = 0;

/* Tracks how many rows have been allocated */
int allocatedRows = 0;

/* Function prototypes */

int readPositiveInteger(char prompt[]);
int isValidMove(char **maze, int rows, int cols, int r, int c);
int backtrack(char **maze, int rows, int cols, int r, int c);

void inputMaze(void);
void printMaze(void);
void solveMaze(void);
void freeMemory(void);

/* Reads and validates a positive integer */

int readPositiveInteger(char prompt[])
{
    char input[50];     /* Stores user input */
    char *endPtr;       /* Checks where number conversion ends */
    long number;        /* Stores converted number */

    /* Keep asking until valid input is entered */
    while (1)
    {
        printf("%s", prompt);

        /* Read input as text */
        if (scanf("%49s", input) != 1)
        {
            return 0;
        }

        /* Convert text into a number */
        errno = 0;
        number = strtol(input, &endPtr, 10);

        /* Check if input is a valid positive integer */
        if (errno != ERANGE && endPtr != input &&
            *endPtr == '\0' && number > 0 &&
            number <= INT_MAX)
        {
            return (int)number;
        }

        /* Display error if input is invalid */
        printf("Error: Invalid input.\n");
        printf("Please enter a valid positive integer.\n");
    }
}

/* Allocates memory and reads the maze from the user */

void inputMaze(void)
{
    int i;
    int j;
    int startCount;     /* Counts start positions */
    int exitCount;      /* Counts exit positions */
    char cell[50];      /* Stores each maze cell */

    /* Free the previous maze before creating a new one */
    freeMemory();

    /* Ask the user for maze dimensions */
    rows = readPositiveInteger("Enter number of rows: ");

    if (rows == 0)
    {
        return;
    }

    cols = readPositiveInteger("Enter number of columns: ");

    if (cols == 0)
    {
        rows = 0;
        return;
    }

    /* Allocate memory for the row pointers */
    maze = (char **)malloc(rows * sizeof(char *));

    /* Check if memory allocation was successful */
    if (maze == NULL)
    {
        printf("Memory allocation failed.\n");
        rows = 0;
        cols = 0;
        return;
    }

    /* Allocate memory for each row of the maze */
    for (i = 0; i < rows; i++)
    {
        maze[i] = (char *)malloc(cols * sizeof(char));

        /* Stop if memory allocation fails */
        if (maze[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            freeMemory();
            return;
        }

        /* Keep track of allocated rows */
        allocatedRows++;
    }

    /* Start counting from zero */
    startCount = 0;
    exitCount = 0;

    printf("Enter the maze row by row:\n");

    /* Read every cell in the maze */
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            /* Read one maze cell */
            if (scanf("%49s", cell) != 1)
            {
                printf("Error: Invalid maze input.\n");
                freeMemory();
                return;
            }

            /* Check if the character is allowed */
            if (strlen(cell) != 1 ||
                (cell[0] != '0' &&
                 cell[0] != '1' &&
                 cell[0] != 'S' &&
                 cell[0] != 'E'))
            {
                printf("Error: Invalid character detected.\n");
                printf("Valid characters are 0, 1, S, and E.\n");
                freeMemory();
                return;
            }

            /* Store the character in the maze */
            maze[i][j] = cell[0];

            /* Find and save the starting position */
            if (maze[i][j] == 'S')
            {
                startRow = i;
                startCol = j;
                startCount++;
            }

            /* Find and save the exit position */
            if (maze[i][j] == 'E')
            {
                exitRow = i;
                exitCol = j;
                exitCount++;
            }
        }
    }

    /* Check that exactly one start and exit exist */
    if (startCount != 1 || exitCount != 1)
    {
        printf("Error: Invalid maze configuration.\n");

        /* Display an error if the start is missing or repeated */
        if (startCount != 1)
        {
            printf("Reason: Maze must contain exactly one start position (S).\n");
        }

        /* Display an error if the exit is missing or repeated */
        if (exitCount != 1)
        {
            printf("Reason: Maze must contain exactly one exit position (E).\n");
        }

        freeMemory();
        return;
    }

    /* Mark the maze as successfully loaded */
    mazeLoaded = 1;
    mazeSolved = 0;

    printf("Maze loaded successfully!\n");
}

/* Displays the current maze */

void printMaze(void)
{
    int i;
    int j;

    /* Check if a maze has been loaded */
    if (mazeLoaded == 0)
    {
        printf("No maze loaded.\n");
        return;
    }

    /* Go through each row */
    for (i = 0; i < rows; i++)
    {
        /* Display each cell in the row */
        for (j = 0; j < cols; j++)
        {
            printf("%c ", maze[i][j]);
        }

        /* Move to the next line */
        printf("\n");
    }
}

/* Checks whether the next move is allowed */

int isValidMove(char **maze, int rows, int cols, int r, int c)
{
    /* Check if the position is outside the maze */
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        return 0;
    }

    /* Do not allow movement into walls */
    if (maze[r][c] == '1')
    {
        return 0;
    }

    /* Do not visit cells that were already visited */
    if (maze[r][c] == '*')
    {
        return 0;
    }

    /* The move is allowed */
    return 1;
}

/* Uses recursion to find a path to the exit */

int backtrack(char **maze, int rows, int cols, int r, int c)
{
    /* Check if the current move is valid */
    if (isValidMove(maze, rows, cols, r, c) == 0)
    {
        return 0;
    }

    /* Base case: Return success when the exit is found */
    if (maze[r][c] == 'E')
    {
        return 1;
    }

    /* Mark the current cell as part of the path */
    /* Keep the starting position unchanged */
    if (maze[r][c] != 'S')
    {
        maze[r][c] = '*';
    }

    /* Try moving Down */
    if (backtrack(maze, rows, cols, r + 1, c))
    {
        return 1;
    }

    /* Try moving Up */
    if (backtrack(maze, rows, cols, r - 1, c))
    {
        return 1;
    }

    /* Try moving Right */
    if (backtrack(maze, rows, cols, r, c + 1))
    {
        return 1;
    }

    /* Try moving Left */
    if (backtrack(maze, rows, cols, r, c - 1))
    {
        return 1;
    }

    /* Backtrack: Restore the cell if no path was found */
    if (maze[r][c] != 'S')
    {
        maze[r][c] = '0';
    }

    /* Return failure if all directions fail */
    return 0;
}

/* Starts the maze-solving process */

void solveMaze(void)
{
    /* Check if a maze has been loaded */
    if (mazeLoaded == 0)
    {
        printf("No maze loaded.\n");
        return;
    }

    /* Avoid solving the same maze again */
    if (mazeSolved == 1)
    {
        printf("Maze already solved successfully!\n");
        printf("Solved Maze:\n");
        printMaze();
        return;
    }

    /* Display the original maze before solving */
    printf("\nOriginal Maze:\n");
    printMaze();

    /* Start recursive backtracking from S */
    if (backtrack(maze, rows, cols, startRow, startCol))
    {
        /* Mark the maze as solved */
        mazeSolved = 1;

        printf("\nMaze solved successfully!\n");
        printf("Solved Maze:\n");

        /* Display the path */
        printMaze();
    }
    else
    {
        /* Display a message if no path exists */
        printf("\nNo valid path exists from start to exit.\n");
    }
}

/* Frees all dynamically allocated memory */

void freeMemory(void)
{
    int i;

    /* Check if memory was allocated */
    if (maze != NULL)
    {
        /* Free each individual row */
        for (i = 0; i < allocatedRows; i++)
        {
            free(maze[i]);
        }

        /* Free the array of row pointers */
        free(maze);
    }

    /* Reset the maze pointer */
    maze = NULL;

    /* Reset allocated row count */
    allocatedRows = 0;

    /* Reset maze dimensions */
    rows = 0;
    cols = 0;

    /* Reset start position */
    startRow = 0;
    startCol = 0;

    /* Reset exit position */
    exitRow = 0;
    exitCol = 0;

    /* Reset maze status */
    mazeLoaded = 0;
    mazeSolved = 0;
}

/* Main program: Displays the menu and handles user choices */

int main(void)
{
    char choice[50];    /* Stores the user's menu choice */

    /* Keep displaying the menu until the user exits */
    while (1)
    {
        printf("\nMaze Solver Menu:\n");
        printf("1. Input a new maze\n");
        printf("2. Display the maze\n");
        printf("3. Solve the maze\n");
        printf("X. Exit\n");

        printf("Enter your choice: ");

        /* Read the user's menu selection */
        if (scanf("%49s", choice) != 1)
        {
            break;
        }

        /* Option 1: Input a new maze */
        if (strcmp(choice, "1") == 0)
        {
            inputMaze();
        }

        /* Option 2: Display the current maze */
        else if (strcmp(choice, "2") == 0)
        {
            printMaze();
        }

        /* Option 3: Solve the current maze */
        else if (strcmp(choice, "3") == 0)
        {
            solveMaze();
        }

        /* Option X: Exit the program */
        else if (strcmp(choice, "X") == 0 ||
                 strcmp(choice, "x") == 0)
        {
            freeMemory();

            printf("Exiting program.\n");
            break;
        }

        /* Handle invalid menu choices */
        else
        {
            printf("Invalid menu option.\n");
        }
    }

    /* Make sure all memory is freed before exiting */
    freeMemory();

    return 0;
}
