#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "Tic_Tac_Toe.h"

int main()
{/* code */

	int turn= 0;
	bool isOk= 1;

	char Symbol1 = 'X';
	char Symbol2 = 'O';
	int OrderFlag= 0;

    char PlayGround[NROW][NCOL];
	int SelRow;
	int SelCol;
	char Human;
	char Peppino;
	char currentSymbol;

	struct Move BestMove;

	// Initialize a new seed every run to have be random
	srand((unsigned int)(NULL));

	headerExplanation();
	resetPlayGround(PlayGround);
	
	while (isOk)
	{
		if (isAllEmpty(PlayGround))
		{
			turn = 0;
			OrderFlag = selectPlayerOrder();
			selectSymbol (&Human, &Peppino, Symbol1, Symbol2);
			printPlayGround(PlayGround);
		}
		if (turn % 2 == OrderFlag)
		{
			currentSymbol=Human;
			requestInput(&SelRow, &SelCol, PlayGround);
		}
		else
		{
			currentSymbol=Peppino;
			if (isAllEmpty(PlayGround))
			{
				SelRow = rand()% NROW;
				SelCol = rand()% NCOL;
			}
			else
			{
				findBestMove(PlayGround, currentSymbol, Human, &BestMove);
				SelRow=BestMove.row;
				SelCol=BestMove.col;
			}

		}
		
		writePlayGround (PlayGround, SelRow, SelCol, currentSymbol);
		printPlayGround (PlayGround);

		turn++;

		if(!isMovesLeft(PlayGround) || isGameEnd(PlayGround))
		{
			if(isGameEnd(PlayGround))
			{
				resetPlayGround(PlayGround);
				printf("Player [ %c ] win the game", currentSymbol);
				printf("\n");
				printf("%c",SPACE);
				printf("\n");
			}			

			if(!isMovesLeft(PlayGround))
			{
				resetPlayGround(PlayGround);
				printf("The game is a draw. Retry");
				printf("\n");
				printf("%c",SPACE);
				printf("\n");
			}
			isOk=askRetry();
		}
	}
	printf("Press Any Key to Continue\n");
	fflush(stdin);
	OrderFlag=getchar(); 
	
	return 0;
}

void headerExplanation(void)
{
	printf("Hello this is tic-tac-toe from Garzanese.");
	printf("\n");
	printf("\n");
	printf("Tic-tac-toe is a paper-and-pencil game for two players who take turns marking the spaces in a 3x3 grid with X or O.");
	printf("\n");
	printf("The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row is the winner.");
	printf("\n");
	printf("It is a solved game, with a forced draw assuming best play from both players.");
	printf("\n");
	printf("%c",SPACE);
	printf("\n");
	printf("Now it is time to play.") ;
	printf("\n");
	printf("%c",SPACE);
	printf("\n");

}

void resetPlayGround (char PlayGround[NROW][NCOL])
{ // Function to reset the PlayGround

    char val = SPACE;

    for (int irow=0; irow< NROW; ++irow)
    {
        for (int icol=0; icol< NCOL ; ++icol)
        {
            PlayGround[irow][icol]=val;
        }
    }
}

void printPlayGround (char PlayGround[NROW][NCOL]) 
{
	// Input the pointer to the board array and the size
	// Function prints out the current board status
    int irow;
    int icol;

	for (irow=0; irow<NROW; irow++) 
    {
		printf("\n");
		if (irow> 0) 
        {
			// Print horizontal dividers
			for (icol=0; icol<NCOL; icol++) 
            {
				if (icol > 0) 
                {
					printf("----");
				} else {
					printf("\t---");
				}
			}
		} 
        else 
        {
			// Print headers
			printf("\t");
			for (icol=0;icol<NCOL; icol++) 
            {
				if (icol > 0) 
                {
					printf("  %c ", icol+LOWCASE_SHIFT);
				} else {
					printf(" %c ", icol+LOWCASE_SHIFT);
				}
			}
			printf("\n");
		}
		printf("\n %i", irow);

		// Print row values
		for (icol=0; icol<NCOL; icol++) 
        {
			if (icol > 0) 
            {
				printf("|");
			} 
            else 
			{
				printf("\t");
			}
			printf(" %c ",PlayGround[irow][icol]);
		}
	}
	printf("\n\n");
}

void requestInput 	(int *SelRow, int *SelCol, char PlayGround[NROW][NCOL])
{
	char EmptyVal = SPACE;
	int isOk=1;
	char dummy_col;
	char dummy_row;

	while (isOk)
	{
		printf("Please write the chosen row & column [e.g. 0a]:");
		fflush(stdin);
		scanf( "%c %c", &dummy_row, &dummy_col); 
	
		*SelCol=tolower(dummy_col)-LOWCASE_SHIFT;
		*SelRow=tolower(dummy_row)-NUM_SHIFT;
		if(*SelRow<NROW && *SelCol<NCOL)
		{
			if (PlayGround[*SelRow][*SelCol]==EmptyVal)
			{
				isOk=0;
			}
			else
			{
				printf("The selected cell has already been chosen, please retry \n");
			}
			
		}
		else
		{
			printf("Provided values not correct, please retry. \n");
		}
	}
}

void selectSymbol (char *SelSymbol, char *OpponentSymbol, char Symbol1, char Symbol2)
{
	char dummy[2] 		= {Symbol1, Symbol2};
	int isOK 			= 1;

	while (isOK)
	{
		printf("Select which symbol do you want to use [ %c ] or [ %c ]:",dummy[0],dummy[1]);
		fflush(stdin);
		scanf( "%c", SelSymbol);

		if (tolower(*SelSymbol)==tolower(dummy[0]) || (tolower(*SelSymbol)==tolower(dummy[1])))
		{
			isOK=0;

			if (tolower(*SelSymbol)==tolower(dummy[0]))
			{
				*OpponentSymbol=dummy[1];
			}
			else
			{
				*OpponentSymbol=dummy[0];
			}
		}
		else
		{
			printf("The chosen symbol was not corret.");
			printf("\n");
		}
	}
}

void writePlayGround (char PlayGround[NROW][NCOL], int irow, int icol, char SelSymbol)
{
	PlayGround[irow][icol]=SelSymbol;
}

int selectPlayerOrder(void)
{
	int isOK 	= 1;
	int out 	= 0;

	while (isOK)
	{
		char dummy;
		printf("Do you want to go first?");
		printf("\n");
		printf("y - Yes, I want to start");
		printf("\n");
		printf("n - No, I prefer to go second");
		printf("\n");

		fflush(stdin);
		scanf( "%c", &dummy);

		if (tolower(dummy)=='y' || tolower(dummy)=='n')
		{
			isOK=0;

			if(dummy=='n')
			{
				out = 1;
			}
		}
		else
		{
			printf("The chosen symbol was not corret.");
			printf("\n");
		}
	}
	return out;
}

bool isMovesLeft(char PlayGround[NROW][NCOL])
{
    for (int i = 0; i<NROW; i++)
	{
        for (int j = 0; j<NCOL; j++)
		{
            if (PlayGround[i][j]==SPACE)
                return true;
		}
	}
    return false;
}

bool isAllEmpty(char PlayGround[NROW][NCOL])
{
    for (int i = 0; i<NROW; i++)
	{
        for (int j = 0; j<NCOL; j++)
		{
            if (PlayGround[i][j]!=SPACE)
                return false;
		}
	}
    return true;
}

bool isGameEnd(char PlayGround[NROW][NCOL])
{
	int irow;
	int icol;
	int i;

	bool winRow;
	bool winCol;
	bool winDiag = true;
	bool winDiag2 = true;
	
	// check all the raws
	for (irow=0; irow<NCOL; irow++)
	{
		winRow = true;
		for (icol=1; icol<NROW; icol++)
		{
			winRow = winRow && (PlayGround[irow][icol]==PlayGround[irow][0]) && (PlayGround[irow][0]!=SPACE);
		}
		if (winRow)
		{
			break;
		}
	}
	
	// check all the columns
	for (icol=0; icol<NCOL; icol++)
	{
		winCol = true;
		for (irow=1; irow<NROW; irow++)
		{
			winCol= winCol && (PlayGround[irow][icol]==PlayGround[0][icol]) && (PlayGround[0][icol]!=SPACE);
		}
		if (winCol)
		{
			break;
		}
	}

	// check major diagonal
	for (i=0; i<NCOL; i++)
	{
		winDiag= winDiag && (PlayGround[i][i]==PlayGround[0][0]) && (PlayGround[0][0]!=SPACE);
	}

	// check minor diagonal
	for (i=0; i<NCOL; i++)
	{
		winDiag2= winDiag2 && (PlayGround[NROW-1-i][i]==PlayGround[NROW-1][0]) && (PlayGround[NROW-1][0]!=SPACE);	
	}

	return winDiag2 || winDiag || winRow || winCol;
}

int MiniMax (char PlayGround[NROW][NCOL], int Val, bool isMax, int Depth, char ActiveSymbol, char UnactiveSymbol )
{

	if (isGameEnd(PlayGround))
	{
		if (!isMax)
		{
			return Val - Depth;
		}
		else
		{
			return -Val + Depth;
		}	
	}

	if (!isMovesLeft(PlayGround))
	{
		return 0;
	}

    if (isMax)
    {// If this maximizer's move
        int best = -1000;
    
        for (int irow = 0; irow<NROW; irow++)
        {// Traverse all cells
            for (int icol = 0; icol<NCOL; icol++)
            {
                if (PlayGround[irow][icol]==SPACE)
                {// Check if cell is empty
                    // Make the move
                    PlayGround[irow][icol] = ActiveSymbol;
  
                    // Call minimax recursively and choose the maximum value
                    best = max( best,
                        MiniMax (PlayGround, Val, !isMax, Depth+1, UnactiveSymbol, ActiveSymbol ));
  
                    // Undo the move
                    PlayGround[irow][icol] = SPACE;
                }
            }
        }
        return best;
    }
    else
    {// If this minimizer's move
        int best = 1000;
  
        // Traverse all cells
        for (int irow = 0; irow<NROW; irow++)
        {
            for (int icol = 0; icol<NCOL; icol++)
            {
                // Check if cell is empty
                if (PlayGround[irow][icol]==SPACE)
                {
                    // Make the move
                    PlayGround[irow][icol] = ActiveSymbol;
  
                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                           MiniMax (PlayGround, Val, !isMax, Depth+1, UnactiveSymbol, ActiveSymbol ));
  
                    // Undo the move
                    PlayGround[irow][icol] = SPACE;
                }
            }
        }
        return best;
	}
}

void findBestMove(char PlayGround[NROW][NCOL], char ActiveSymbol, char UnactiveSymbol, struct Move *bestMove)
{
    bestMove->row = -1;
    bestMove->col = -1;

    int bestVal = -1000;
	int MaxVal  = 10;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int irow = 0; irow<NROW; irow++)
    {
        for (int icol = 0; icol<NCOL; icol++)
        {
            // Check if cell is empty
            if (PlayGround[irow][icol]==SPACE)
            {
                // Make the move
                PlayGround[irow][icol] = ActiveSymbol;
  
                // compute evaluation function for this
                // move.
                int moveVal = MiniMax (PlayGround, MaxVal, false, 0, UnactiveSymbol, ActiveSymbol);
  
                // Undo the move
                PlayGround[irow][icol] = SPACE;
  
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove->row = irow;
                    bestMove->col = icol;
                    bestMove->value = moveVal;
                    bestVal = moveVal;
                }
            }
        }
    }
}

int askRetry(void)
{
	int isOK 	= 1;
	int out 	= 1;

	while (isOK)
	{
		char dummy;
		printf("Do you want to play another game?");
		printf("\n");
		printf("y - Yes, I want to start again");
		printf("\n");
		printf("n - No, I prefer to go work");
		printf("\n");
		printf("%c",SPACE);
		printf("\n");
		
		fflush(stdin);
		scanf( "%c", &dummy);
		

		if (dummy=='y' || dummy=='n')
		{
			isOK=0;

			if(dummy=='n')
			{

				out = 0;
			}
		}
		else
		{
			printf("The chosen symbol was not corret.");
			printf("\n");
		}
	}
	return out;
}
