#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "Tic_Tac_Toe.h"

int main()
{/* code */

	int turn= 0;
	bool isOk= 1;

	char Symbol1 = 'X';
	char Symbol2 = 'O';

    char PlayGround[NROW][NCOL];
	int SelRow;
	int SelCol;
	char Human;
	char Peppino;
	char currentSymbol;

	struct Move BestMove;

	// Initialize a new seed every run to have be random
	srand(time(NULL));

    resetPlayGround(PlayGround);

	int OrderFlag = selectPlayerOrder();
	selectSymbol (&Human, &Peppino, Symbol1, Symbol2);

	printPlayGround(PlayGround);

	while (isOk)
	{
		if (turn % 2 == OrderFlag)
		{
			currentSymbol=Human;
			requestInput(&SelRow, &SelCol, PlayGround);
		}
		else
		{
			currentSymbol=Peppino;
			if ( ((int) turn/2)==0)
			{
				SelRow = rand()% NROW;
				SelCol = rand()% NCOL;
			}
			else
			{
				BestMove=findBestMove(PlayGround, currentSymbol, Human);
				SelRow=BestMove.row;
				SelCol=BestMove.col;
			}

		}
		
		writePlayGround (PlayGround, SelRow, SelCol, currentSymbol);
		printPlayGround (PlayGround);

		if(!isMovesLeft(PlayGround) || isGameEnd(PlayGround))
		{
			isOk=0;

			if(isGameEnd(PlayGround))
			{
				printf("Player [ %c ] win the game", currentSymbol);
				return 0;
			}			

			if(!isMovesLeft(PlayGround))
			{
				printf(" the game is a draw. Retry");
				return 0;
			}
		}

		turn++;
	}
	return 0;
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
	char dummy;
	int isOk=1;

	while (isOk)
	{
		
		printf("Please write the chosen row:");
		scanf( "%d", SelRow); 

		printf("\n");
		printf("Please write the chosen column:");

		fflush(stdin);
		scanf( "%c",&dummy);

		*SelCol=dummy-LOWCASE_SHIFT;

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
		scanf( "%c", SelSymbol);
		fflush(stdin);

		if (*SelSymbol==dummy[0] || *SelSymbol==dummy[1])
		{
			isOK=0;

			if (*SelSymbol==dummy[0])
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
		printf("Hello this is tic-tac-toe from Garzanese. Do you want to go first?");
		printf("\n");
		printf("y - Yes, I want to start");
		printf("\n");
		printf("n - No, I prefer to go second");
		printf("\n");

		scanf( "%c", &dummy);
		fflush(stdin);

		if (dummy=='y' || dummy=='n')
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

bool isGameEnd(char PlayGround[NROW][NCOL])
{
	int irow;
	int icol;

	// Check all the rows
	for (irow=0; irow<NROW; irow++)
	{
		if(PlayGround[irow][1]==PlayGround[irow][0] && PlayGround[irow][2]==PlayGround[irow][0]  && PlayGround[irow][0]!=SPACE)
		{
			return true;
		}
	}

	// check all the columns
	for (icol=0; icol<NCOL; icol++)
	{
		if(PlayGround[1][icol]==PlayGround[0][icol] && PlayGround[2][icol]==PlayGround[0][icol] && PlayGround[0][icol]!=SPACE)
		{
			return true;
		}
	}

	// check first diagonal
	if(PlayGround[1][1]==PlayGround[0][0] &&  PlayGround[2][2]==PlayGround[0][0] && PlayGround[0][0]!=SPACE)
	{
		return true;
	}	

	// check second diagonal
	if(PlayGround[1][1]==PlayGround[0][2] && PlayGround[2][0]==PlayGround[0][2] && PlayGround[0][2]!=SPACE)
	{
		return true;
	}
	return false;	
}

struct Move findBestMove(char PlayGround[NROW][NCOL], char ActiveSymbol, char UnactiveSymbol)
{
	struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

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
                    bestMove.row = irow;
                    bestMove.col = icol;
                    bestMove.value = moveVal;
                    bestVal = moveVal;
                }
            }
        }
    }
	return bestMove;
}

double MiniMax (char PlayGround[NROW][NCOL], int Val, bool isMax, int Depth, char ActiveSymbol, char UnactiveSymbol )
{
	int irow;
	int icol;
	int moveVal;

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
