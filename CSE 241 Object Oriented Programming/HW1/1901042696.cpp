#include <iostream>
#include"lib.h"
using namespace std;

int main(){
    char board[12][12];
    int sizer = 12;
    fillBoard(board);
    displayBoard(sizer,board);
    while (true) {
        cout << "Welcome to hex game , please write down size of board (max 12 min 6) \n";
        cin >> sizer;
        if (sizer > 12 || sizer < 6) {
            cout << "please choice between 6 and 12 " << endl;
            continue;
        }
        displayBoard(sizer,board);
        break;
    }

    cout << "Welcome to hex game again :), you have 2 choice now play against computer or play against to your friend :) \n";
    cout << "1 for computer 2 for friend\n";
    char choice;
    cin >> choice;
    int turn = 0;
    displayBoard(sizer, board);
    if (choice == '1') {
        while (true) {
            char z, f;
            cout << "please write num and char(A 1) \n";
            cin >> z >> f;
            int y = z - 'A';
            int x = f - '1';
            //Checks is movement avalaible
            if (y > sizer - 1 || y < 0 || x>sizer - 1 || x < 0 || board[x][y] != '.') {
                cout << "\nwrong ! Try again\n";
                continue;
            }
            board[x][y] = 'o';
            turn++;
            displayBoard(sizer, board);

            if (checkWin('o', x, y,board,sizer)) {
                cout << "\n player1 won";
                displayBoard(sizer, board);
                return true;
            }
            if (playComputerAndCheckWin(x, y,sizer,board)) {
                cout << "\n player2 won";
                displayBoard(sizer, board);
                break;
            }
            if (turn == (sizer * sizer) / 2) {
                cout << "\n DRAW";
                break;
            }
        }
    }

    else if (choice == '2') {
        while (true) {
            char z, f;
            if (turn % 2 == 0)
                cout << "Turn for 1 \nplease write num and char(A 1) \n";
            else
                cout << "Turn for 2 \nplease write num and char(A 1) \n";
            cin >> z >> f;
            int y = z - 'A';
            int x = f - '1';
            //Checks is movement avalaible
            if (y > sizer - 1 || y < 0 || x>sizer - 1 || x < 0 || board[x][y] != '.') {
                cout << "\nwrong ! Try again\n";
                continue;
            }
            if (turn % 2 == 0)
                board[x][y] = 'o';
            else
                board[x][y] = 'x';

            displayBoard(sizer, board);
            int map[12][12] = { 0 };
            if (turn % 2 == 0) {
                if (checkWin('o', x, y,board,sizer)) {
                    cout << "\n player1 won";
                    displayBoard(sizer, board);
                    return true;
                }
            }

            else {
                if (checkWin('x', x, y,board,sizer)) {
                    cout << "\n player2 won";
                    displayBoard(sizer, board);
                    return true;
                }
            }
            turn++;

        }
    }
    else cout << "Wrong selection sorry I gotta go :(";



}

