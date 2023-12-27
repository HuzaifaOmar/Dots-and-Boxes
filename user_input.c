#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_logic.h"

bool isValidGridInput(char userInput, char gridSize) //* validate user input based on grid size
{
    bool inputInGrid;

    if (gridSize == 9 || gridSize == 11)
    {
        inputInGrid = (userInput >= '0' && userInput <= '9') ||
                      (userInput >= 'A' && userInput <= 'Z') ||
                      (userInput >= 'a' && userInput <= (gridSize * 10 + 10));
    }
    else
        switch (gridSize)
        {
        case 5:
            inputInGrid = (userInput >= '0' && userInput <= '9') || (userInput >= 'A' && userInput <= 'B');
            break;
        case 7:
            inputInGrid = (userInput >= '0' && userInput <= '9') || (userInput >= 'A' && userInput <= 'N');
            break;
        default:
            printf("Invalid grid size");
            exit(1);
        }
    return inputInGrid;
}
unsigned char getUserInput(char gridSize)
{
    char inputBuffer[MAX_INPUT_LENGTH];
    scanf("%s", inputBuffer);

    char userInput;
    if (inputBuffer[0] != '\n')
        userInput = inputBuffer[0];
    else
        userInput = inputBuffer[1];

    bool inputInGrid = isValidGridInput(userInput, gridSize);
    while (!inputInGrid)
    {
        printf("Please, choose a character from the grid!\n");
        fgets(inputBuffer, MAX_INPUT_LENGTH, stdin);

        if (inputBuffer[0] != '\n')
            userInput = inputBuffer[0];
        else
            userInput = inputBuffer[1];

        inputInGrid = isValidGridInput(userInput, gridSize);
    }
    return userInput;
}

void updateGridWithUserInput(Grid *gameGrid, Player player, GameState *currentGame, char userInput,MovesHistory *movesHistory)
{
    Move move;
    while (1)
    {
        for (int i = 0; i < gameGrid->size; i++)
            if (i % 2 == 0)
            {
                for (int j = 1; j < gameGrid->size; j += 2)
                    if (gameGrid->grid[i][j] == userInput)
                    {
                        move.i=i;move.j=j;                        //! ubdate Move Struct
                        move.oldValue=userInput;
                        move.playerSymbol=player.symbol;

                        movesHistory->moves[movesHistory->currentMove+1]=move;  //! update movesHistory struct
                        movesHistory->currentMove++;
                        movesHistory->numMovesPlayed++;
                    
                        gameGrid->grid[i][j] = player.symbol;                  //! update grid
                        currentGame->remainingLines--;
                        checkBoxesAroundLine(i, j, gameGrid, player.symbol, currentGame);
                        return;
                    }
            }
            else
                for (int j = 0; j < gameGrid->size; j += 2)
                    if (gameGrid->grid[i][j] == userInput)
                    {
                        move.i=i;move.j=j;                        //! ubdate Move Struct
                        move.oldValue=userInput;
                        move.playerSymbol=player.symbol;

                        movesHistory->moves[movesHistory->currentMove+1]=move;  //! update movesHistory struct
                        movesHistory->currentMove++;
                        movesHistory->numMovesPlayed++;
                    

                        gameGrid->grid[i][j] = player.symbol;                    //! update grid
                        currentGame->remainingLines--;
                        checkBoxesAroundLine(i, j, gameGrid, player.symbol, currentGame);
                        return;
                    }

        printf("\nLine was chosen before. Please choose another line.\n");
        userInput = getUserInput(gameGrid->size);
    }
}