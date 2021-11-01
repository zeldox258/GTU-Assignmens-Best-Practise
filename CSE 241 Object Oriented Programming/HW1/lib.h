
void fillBoard(char board[12][12]);
void displayBoard(int sizer , char board[12][12]);
void isWin(char player, int x, int y, bool winCondition[2], int map[12][12],char board[12][12],int sizer);
bool checkWin(char player, int x, int y,char board[12][12],int sizer);
bool playComputerAndCheckWin(int x, int y,int sizer , char board[12][12]);

