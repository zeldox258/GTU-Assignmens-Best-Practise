#include"lib.h"
#include <iostream>
using namespace std;
//fills board with "."
void fillBoard(char board[12][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            board[i][j] = '.';
        }
    }
}
// prints board to screen
void displayBoard(int sizer , char board[12][12]) {
    cout << " ";
    for (int i = 0; i < sizer; i++)cout << char('A' + i) << " ";
    cout << endl;
    for (int i = 0; i < sizer; i++) {
        cout << i + 1;
        if (i < 9) {
            for (int j = 0; j <i+1 ; j++) {
                cout << " ";
            }
        }
        else {
            for (int j = 0; j < i; j++) {
                cout << " ";
            }
        }
        for (int j = 0; j < sizer; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// checks the road connected between teo wall
void isWin(char player, int x, int y, bool winCondition[2], int map[12][12],char board[12][12],int sizer) {
    if (x >= sizer || y >= sizer || x < 0 || y < 0 || map[x][y] == 1 || (winCondition[0] && winCondition[1]))return;
    if (player == 'o' && board[x][y] != 'o')return;
    if (player == 'x' && board[x][y] != 'x')return;
    board[x][y] -= ' ';
    if (player == 'o') {
        if (x == 0)winCondition[0] = true;
        if (x == sizer-1)winCondition[1] = true;
    }
    if (player == 'x') {
        if (y == 0)winCondition[0] = true;
        if (y == sizer-1)winCondition[1] = true;
    }
    map[x][y] = 1;

    isWin(player, x - 1, y, winCondition, map,board,sizer);
    isWin(player, x - 1, y + 1, winCondition, map, board, sizer);
    isWin(player, x, y + 1, winCondition, map, board, sizer);
    isWin(player, x + 1, y, winCondition, map, board, sizer);
    isWin(player, x + 1, y - 1, winCondition, map, board, sizer);
    isWin(player, x, y - 1, winCondition, map, board, sizer);
    if (winCondition[0] && winCondition[1]) return;
    board[x][y] += ' ';

}
// Checks the is anybody won the match
bool checkWin(char player, int x, int y,char board[12][12],int sizer) {
    for (int i = 0; i < sizer; i++) {
        int map[12][12] = { 0 };
        bool winCondition[2] = { false };
        if (player == 'o' && board[0][i]=='o') {
            isWin(player, 0, i, winCondition, map, board, sizer);
        }
        else if(board[i][0] == 'x') {
            isWin(player, i, 0, winCondition, map, board, sizer);
        }
        if(winCondition[0] && winCondition[1])
            return true;
    }
    
    
    return false;
}
//decides computer moves and checks the computer win
bool playComputerAndCheckWin(int x, int y,int sizer , char board[12][12]) {
    int tempx = x;
    int tempy = y;
    
    while (true) {
        if (tempx != sizer-1)tempx++;
        while (tempx >= 0 && board[tempx][tempy] != '.')tempx--;
        if (tempx == -1) {
            tempx = x;
            tempy++;
            if (tempy == sizer)tempy = 0;
            if (tempy == y)x++;
        }
        else break;
    }
    board[tempx][tempy] = 'x';
    displayBoard(sizer, board);

    if (checkWin('x', tempx, tempy,board,sizer)) {
        return true;
    }

    return false;
    
}

