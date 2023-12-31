
#define NCOL 3
#define NROW NCOL
#define SPACE 32
#define LOWCASE_SHIFT 97
#define NUM_SHIFT 48

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

void headerExplanation(void);
void printPlayGround (char [NROW][NCOL]);
void resetPlayGround (char [NROW][NCOL]);
void requestInput (int *, int *, char [NROW][NCOL]);
void selectSymbol (char *, char *, char, char );
void writePlayGround (char [NROW][NCOL], int, int , char);
int selectPlayerOrder(void);
bool isMovesLeft(char [NROW][NCOL]);
bool isGameEnd(char [NROW][NCOL]);
bool isAllEmpty(char [NROW][NCOL]);
int askRetry(void);
int MiniMax (char [NROW][NCOL], int, bool, int, char, char);
void findBestMove(char [NROW][NCOL], char , char , struct Move *);