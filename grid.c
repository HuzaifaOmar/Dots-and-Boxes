#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ansi_colors.h"
#include "grid.h" 
#include "game_logic.h"

void clearConsole()
{
    printf("\e[1;1H\e[2J"); // ANSI escape code to clear the console
}

void initializeGrid(Grid *gameGrid)
{
    unsigned char ch = '0';

    for (int i = 0; i < gameGrid->size; i++)
        for (int j = 0; j < gameGrid->size; j++)
            if ((i % 2 == 0) && (j % 2 == 0))
                gameGrid->grid[i][j] = DOT;
            else if ((i % 2 == 1) && (j % 2 == 1))
                gameGrid->grid[i][j] = ' ';
            else
            {
                gameGrid->grid[i][j] = ch;
                if (ch <= 'A')
                    ch = (ch == '9') ? 'A' : ch + 1;
                else
                    ch = (ch == 'Z') ? 'a' : ch + 1;
            }
}

//* printing grid
void printGameTitle()
{
    printf(BHRED "\t                           _       __ ______ __    ______ ____   __  ___ ______   ______ ____   \n");
    printf("\t                          | |     / // ____// /   / ____// __ \\ /  |/  // ____/  /_  __// __ \\  \n");
    printf("\t                          | | /| / // __/  / /   / /    / / / // /|_/ // __/      / /  / / / /  \n");
    printf("\t                          | |/ |/ // /___ / /___/ /___ / /_/ // /  / // /___     / /  / /_/ /   \n");
    printf("\t    ____   ____  ______ __|_/  |________/______/_____/ \\_____/_/__/_//_____/ ___/_/__/_____/ ______ ___     __  ___ ______\n" RESET);
    printf(BHMAG "\t   / __ \\ / __ \\/_  __// ___/   /   |   / | / // __ \\   / __ ) / __ \\| |/ / / ____// ___/   / ____//   |   /  |/  // ____/\n");
    printf("\t  / / / // / / / / /   \\__ \\   / /| |  /  |/ // / / /  / __  |/ / / /|   / / __/   \\__ \\   / / __ / /| |  / /|_/ // __/   \n");
    printf("\t / /_/ // /_/ / / /   ___/ /  / ___ | / /|  // /_/ /  / /_/ // /_/ //   | / /___  ___/ /  / /_/ // ___ | / /  / // /___   \n");
    printf("\t/_____/ \\____/ /_/   /____/  /_/  |_|/_/ |_//_____/  /_____/ \\____//_/|_|/_____/ /____/   \\____//_/  |_|/_/  /_//_____/   \n" RESET);
}
void printDotsRow(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
        if (j % 2 == 0)
            if ((gameGrid.grid[row][j + 1] == PLAYER1) || (gameGrid.grid[row][j + 1] == PLAYER2))
                printf(BHGRN "%c" RESET, gameGrid.grid[row][j]);
            else
                printf(BHGRN "%-5c" RESET, gameGrid.grid[row][j]);
        else
            switch (gameGrid.grid[row][j])
            {
            case PLAYER1:
                for (int k = 0; k < 9; k++)
                    printf(BHBLU "%c" RESET, DASH);
                break;
            case PLAYER2:
                for (int k = 0; k < 9; k++)
                    printf(BHRED "%c" RESET, DASH);
                break;
            default:
                printf(BHYEL "%-5c" RESET, gameGrid.grid[row][j]);
            }
}
void printVerticalLines(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
    {
        if (j % 2 == 0)
        {
            if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
            {
                switch (gameGrid.grid[row][j])
                {
                case PLAYER1:
                    printf(BHBLU "%c" RESET, '|');
                    break;
                case PLAYER2:
                    printf(BHRED "%c" RESET, '|');
                    break;
                }
            }

            if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
                printf("%-9c", ' ');
            else
                printf("%-10c", ' ');
        }
    }
}
void printCharacterOrBox(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
    {
        if (j % 2 == 0) // print vertical character or whitespace
            if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
                switch (gameGrid.grid[row][j])
                {
                case PLAYER1:
                    printf(BHBLU "%-5c" RESET, '|');
                    break;
                case PLAYER2:
                    printf(BHRED "%-5c" RESET, '|');
                    break;
                }
            else
                printf(BHYEL "%-5c" RESET, gameGrid.grid[row][j]);
        else // print box
            switch (gameGrid.grid[row][j])
            {
            case PLAYER1:
                printf(BHBLU "%-5c" RESET, '1');
                break;
            case PLAYER2:
                printf(BHRED "%-5c" RESET, '2');
                break;
            default:
                printf(BHRED "%-5c" RESET, ' ');
            }
    }
}

void printGrid(Grid gameGrid, GameState *currentGame)
{
    SmallNumber timeDiffMinutes;
    SmallNumber timeDiffSeconds;
    getTimeDiff(&timeDiffMinutes, &timeDiffSeconds);
    clearConsole();
    printf("\n");
    for (int i = 0; i < gameGrid.size; i++)
    {
        printf("\t\t\t\t\t");
        if (i % 2 == 0)
            printDotsRow(gameGrid, i);
        else
        {
            printf("\n");
            for (int line = 0; line <= 2; line++)
            {
                printf("\t\t\t\t\t");
                if (line % 2 == 0)
                    printVerticalLines(gameGrid, i);
                else
                    printCharacterOrBox(gameGrid, i);
                printf("\n");
            }
        }
    }
    printf("\n\n");
    printf(GRN "Remaining Boxes: %d" RESET, currentGame->remainingBoxes);
    printf(BHBLU "\t\t\tPlayer 1 current score: %d\n" RESET, currentGame->player1Score);
    printf(MAG "Remaining Lines: %d" RESET, currentGame->remainingLines);
    printf(BHRED "\t\t\tPlayer 2 current score: %d\n" RESET, currentGame->player2Score);
    printf(BHWHT "Time: %02d:%02d\n" RESET, timeDiffMinutes, timeDiffSeconds);

    switch (currentGame->CurrentTurn)
    {
    case enPLAYER_1:
        printf("\t\t\t\t\t" BHBLU "Player 1 turn: " RESET);
        break;
    case enPLAYER_2:
        printf("\t\t\t\t\t" BHRED "Player 2 turn: " RESET);
        break;
    }
}

Grid createGrid(SmallNumber size)
{
    Grid newGrid;
    newGrid.size = size;

    newGrid.grid = (unsigned char **)malloc(size * sizeof(unsigned char *));
    if (newGrid.grid == NULL)
    {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        newGrid.grid[i] = (unsigned char *)malloc(size * sizeof(unsigned char));
        if (newGrid.grid[i] == NULL)
        {
            printf("Memory allocation failed. Exiting...\n");
            exit(1);
        }
    }

    return newGrid;
}
void freeGrid(Grid *gameGrid)
{
    for (int i = 0; i < gameGrid->size; i++) // Free memory for each row in the grid
        free(gameGrid->grid[i]);

    free(gameGrid->grid); // Free the memory allocated for the grid itself
}