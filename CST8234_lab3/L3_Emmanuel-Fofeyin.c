/*
 * Name: Emmanuel Fofeyin
 * Student Number: 041161315
 * Course: CST8234 - C Programming
 * Lab 3: Connect Four
 * Lab Section: 300_301
 * Date: 12/11/2026
 *
 * Description:
 * This program implements a two-player Connect Four game.
 * It features 2D array board management, gravity mechanics,
 * rigorous input validation, and win-condition checking for
 * horizontal, vertical, and diagonal sequences.
 */

#include <stdio.h>   /* Standard input/output library (printf, fgets) */
#include <string.h>  /* String manipulation library (strcpy, strcspn, strcmp) */
#include <ctype.h>   /* Character classification library (isdigit, isalpha, tolower) */
#include <stdlib.h>  /* Standard library for conversion utilities (atoi) */

#define ROWS 6       /* Total rows on the Connect Four board */
#define COLS 7       /* Total columns on the Connect Four board */
#define EMPTY ' '    /* Character representing an empty grid cell */

/* Function Prototypes */
void getPlayerInfo(char p1Name[], char *p1Symbol, char p2Name[], char *p2Symbol);
void initBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
int getAvailableRow(char board[ROWS][COLS], int col);
int checkWin(char board[ROWS][COLS], char symbol);
int isBoardFull(char board[ROWS][COLS]);


int main(void) {
    /* Variable declarations (strict C89 requirement at top of block) */
    char board[ROWS][COLS];
    char p1Name[50], p2Name[50];
    char p1Symbol, p2Symbol;
    char currentName[50];
    char currentSymbol;
    char playAgain[10];
    int playing;

    playing = 1;
    /* Display welcome banner and game instructions */
    printf("Welcome to Connect Four, CST8234 edition!\n");
    printf("You will be dropping chips in the top of a grid. The first\n");
    printf("player to get four chips in a row, horizontally, vertically\n");
    printf("or diagonally, wins!\n\n");

    /* Collect player names and unique chip symbols */
    getPlayerInfo(p1Name, &p1Symbol, p2Name, &p2Symbol);

    /* Main game loop supporting replay */
    while (playing) {
        initBoard(board);
        currentSymbol = p1Symbol;
        strcpy(currentName, p1Name);
        
        while (1) {
            int col;
            int validMove;
            int row;

            validMove = 0;
            printBoard(board);

            /* Input validation loop for player's column choice */
            while (!validMove) {
                char input[100];
                int i;
                int isDigit;

                isDigit = 1;

                printf("%s, what column do you choose? ", currentName);
                if (fgets(input, sizeof(input), stdin) == NULL) {
                    continue;
                }
                
                /* Remove trailing newline if present */
                input[strcspn(input, "\n")] = '\0';

                /* Check if input is empty */
                if (input[0] == '\0') {
                    printf("Invalid input. Enter a number from 1 to 7.\n");
                    continue;
                }

                /* Check if all characters are digits */
                for (i = 0; input[i] != '\0'; i++) {
                    if (!isdigit((unsigned char)input[i])) {
                        isDigit = 0;
                        break;
                    }
                }

                if (!isDigit) {
                    printf("Invalid input. Enter a number from 1 to 7.\n");
                    continue;
                }

                col = atoi(input) - 1; /* Convert 1-7 to 0-6 index */

                if (col < 0 || col >= COLS) {
                    printf("Invalid column. Valid choices are from 1 to 7.\n");
                } else {
                    row = getAvailableRow(board, col);
                    if (row == -1) {
                        printf("Column is full. Choose another column.\n");
                    } else {
                        validMove = 1;
                    }
                }
            }

            /* Place the chip */
            board[row][col] = currentSymbol;

            /* Check for win */
            if (checkWin(board, currentSymbol)) {
                printBoard(board);
                printf("Congratulations, %s, you have won!\n", currentName);
                break;
            }

            /* Check for draw */
            if (isBoardFull(board)) {
                printBoard(board);
                printf("Game is a draw!\n");
                break;
            }

            /* Switch players */
            if (currentSymbol == p1Symbol) {
                currentSymbol = p2Symbol;
                strcpy(currentName, p2Name);
            } else {
                currentSymbol = p1Symbol;
                strcpy(currentName, p1Name);
            }
        }

        /* Play again prompt */
        printf("Play again? (Y/n): ");
        if (fgets(playAgain, sizeof(playAgain), stdin) != NULL) {
            if (playAgain[0] == 'n' || playAgain[0] == 'N') {
                playing = 0;
            }
        }
    }

    return 0;
}

/* Initialize board with empty spaces */
void initBoard(char board[ROWS][COLS]) {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            board[r][c] = EMPTY;
        }
    }
}

/* Print the game board matching lab output style */
void printBoard(char board[ROWS][COLS]) {
    int r, c;
    printf("\nCurrent game board status:\n");
    printf("1 2 3 4 5 6 7\n");
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            printf("+-");
        }
        printf("+\n");
        for (c = 0; c < COLS; c++) {
            printf("|%c", board[r][c]);
        }
        printf("|\n");
    }
    for (c = 0; c < COLS; c++) {
        printf("+-");
    }
    printf("+\n\n");
}

/* Get player info with robust validation and exact error strings */
void getPlayerInfo(char p1Name[], char *p1Symbol, char p2Name[], char *p2Symbol) {
    char colorInput[100];
    int validColor;
    int i;

    /* Player 1 Name */
    printf("Player 1, enter your name: ");
    fgets(p1Name, 50, stdin);
    p1Name[strcspn(p1Name, "\n")] = '\0';

    /* Player 1 Colour */
    validColor = 0;
    while (!validColor) {
        printf("%s, what colour are your chips? ", p1Name);
        if (fgets(colorInput, sizeof(colorInput), stdin) == NULL) continue;
        colorInput[strcspn(colorInput, "\n")] = '\0';

        validColor = 1;
        if (colorInput[0] == '\0') {
            validColor = 0;
        }
        for (i = 0; colorInput[i] != '\0'; i++) {
            if (!isalpha((unsigned char)colorInput[i])) {
                validColor = 0;
                break;
            }
        }

        if (!validColor) {
            printf("That is not a colour I recognize. Please only use letters.\n");
        }
    }
    *p1Symbol = tolower((unsigned char)colorInput[0]);

    /* Player 2 Name */
    while (1) {
        printf("Player 2, enter your name: ");
        fgets(p2Name, 50, stdin);
        p2Name[strcspn(p2Name, "\n")] = '\0';

        if (strcmp(p1Name, p2Name) == 0) {
            printf("Names must be different. Enter another name.\n");
        } else {
            break;
        }
    }

    /* Player 2 Colour */
    validColor = 0;
    while (!validColor) {
        printf("%s, what colour are your chips? ", p2Name);
        if (fgets(colorInput, sizeof(colorInput), stdin) == NULL) continue;
        colorInput[strcspn(colorInput, "\n")] = '\0';

        validColor = 1;
        if (colorInput[0] == '\0') {
            validColor = 0;
        }
        for (i = 0; colorInput[i] != '\0'; i++) {
            if (!isalpha((unsigned char)colorInput[i])) {
                validColor = 0;
                break;
            }
        }

        if (!validColor) {
            printf("That is not a colour I recognize. Please only use letters.\n");
        } else if (tolower((unsigned char)colorInput[0]) == *p1Symbol) {
            printf("Both colours start with '%c'. Choose another colour.\n", *p1Symbol);
            validColor = 0;
        }
    }
    *p2Symbol = tolower((unsigned char)colorInput[0]);
    printf("Excellent. Setup complete.\n\n");
}

/* Find available row in a column (gravity effect) */
int getAvailableRow(char board[ROWS][COLS], int col) {
    int r;
    for (r = ROWS - 1; r >= 0; r--) {
        if (board[r][col] == EMPTY) {
            return r;
        }
    }
    return -1;
}

/* Check if the board is completely full */
int isBoardFull(char board[ROWS][COLS]) {
    int c;
    for (c = 0; c < COLS; c++) {
        if (board[0][c] == EMPTY) {
            return 0;
        }
    }
    return 1;
}

/* Check win condition (Horizontal, Vertical, Diagonal) */
int checkWin(char board[ROWS][COLS], char symbol) {
    int r, c;

    /* Horizontal check */
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == symbol && board[r][c+1] == symbol &&
                board[r][c+2] == symbol && board[r][c+3] == symbol) {
                return 1;
            }
        }
    }

    /* Vertical check */
    for (r = 0; r <= ROWS - 4; r++) {
        for (c = 0; c < COLS; c++) {
            if (board[r][c] == symbol && board[r+1][c] == symbol &&
                board[r+2][c] == symbol && board[r+3][c] == symbol) {
                return 1;
            }
        }
    }

    /* Diagonal (/) check */
    for (r = 3; r < ROWS; r++) {
        for (c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == symbol && board[r-1][c+1] == symbol &&
                board[r-2][c+2] == symbol && board[r-3][c+3] == symbol) {
                return 1;
            }
        }
    }

    /* Diagonal (\) check */
    for (r = 0; r <= ROWS - 4; r++) {
        for (c = 0; c <= COLS - 4; c++) {
            if (board[r][c] == symbol && board[r+1][c+1] == symbol &&
                board[r+2][c+2] == symbol && board[r+3][c+3] == symbol) {
                return 1;
            }
        }
    }

    return 0;
}