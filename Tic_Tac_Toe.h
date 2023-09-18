
#define NCOL 3
#define NROW 3
#define SPACE 32
#define LOWCASE_SHIFT 97

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
    #define min(a,b) ((a) < (b) ? (a) : (b))
#endif

struct Move 
{
    int row;
    int col;
    int value;
};

void printPlayGround (char [NROW][NCOL]);
void resetPlayGround (char [NROW][NCOL]);
void requestInput (int *, int *, char [NROW][NCOL]);
void selectSymbol (char *, char *, char, char );
void writePlayGround (char [NROW][NCOL], int, int , char);
int selectPlayerOrder(void);
bool isMovesLeft(char [NROW][NCOL]);
bool isGameEnd(char [NROW][NCOL]);
double MiniMax (char [NROW][NCOL], int, bool, int, char, char);
struct Move findBestMove(char [NROW][NROW], char, char);
