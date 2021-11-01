#include <iostream>
#include <fstream>
#include <string>
using namespace std;
enum moves { user1 = 'o', user2 = 'x', empty = '.' };//moves enum
string lastLoad;
//fills board with "."
void fillBoard(char board[12][12] , char ch = '.') {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            board[i][j] = ch;
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
    if (player == moves::user1 && board[x][y] != moves::user1)return;
    if (player == moves::user2 && board[x][y] != moves::user2)return;
    board[x][y] -= ' ';
    if (player == moves::user1) {
        if (x == 0)winCondition[0] = true;
        if (x == sizer-1)winCondition[1] = true;
    }
    if (player == moves::user2) {
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
        if (player == moves::user1 && board[0][i]==moves::user1) {
            isWin(player, 0, i, winCondition, map, board, sizer);
        }
        else if(board[i][0] == moves::user2) {
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
        while (tempx >= 0 && board[tempx][tempy] != moves::empty)tempx--;
        if (tempx == -1) {
            tempx = x;
            tempy++;
            if (tempy == sizer)tempy = 0;
            if (tempy == y)x++;
        }
        else break;
    }
    board[tempx][tempy] = moves::user2;
    cout << "computer played at:" << (char)(tempy + 'A') << " " << tempx + 1 << endl;
    displayBoard(sizer, board);

    if (checkWin(moves::user2, tempx, tempy,board,sizer)) {
        return true;
    }

    return false;
    
}
//saving file to file.txt
void saveFile(const int sizer ,const char choice,const char board[12][12],const int turn,string fileName) {
    ofstream myfile;
    myfile.open(fileName);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            myfile << board[i][j] << " ";
        }
        myfile << endl;
    }
    myfile << sizer << endl;
    myfile << choice << endl;
    myfile << turn << endl;
    myfile.close();
}
//loading file if its exist from file.txt
void loadFile(int& sizer, char& choice, char board[12][12],int& turn) {
    string line;
    ifstream myfile(lastLoad);
    if (myfile.is_open()){
        int step = 0;
        while (getline(myfile, line)){
            if (step == 12) {
                sizer = line[0] - '0';
                if (line.size() > 1) {
                    sizer *= 10;
                    sizer += line[1] - '0';
                }
            }
            else if (step == 13) {
                choice = line[0];
            }
            else if (step == 14) {
                turn = line[0]-'0';
                if (line.size() > 1) {
                    turn *= 10;
                    turn += line[1] - '0';
                }
            }
            else {
                int idx = 0;
                for (int i = 0; i < line.size(); i += 2) {
                    board[step][idx++] = line[i];
                }
            }
            
            step++;
        }
        myfile.close();
        cout << "\nsuccesfully loaded\n";
        displayBoard(sizer, board);
    }

    else cerr << "there is no loadable file sorry :(";

}
//this functions convert strings to real coordinant
void convertCord(int& x, int& y, string& line1 , string& line2) {
    
    if (line1.size() > 1 || line2.size() > 2)return;
    y = line1[0] - 'A';
    x = line2[0] - '0';
    if (line2.size() > 1) {
        x *= 10;
        x += line2[1] - 'A';
    }
    x--;
}

void defaultText(int size = 12) {
    cout << "if you want load game please write `LOAD FILE.TXT`\n";
    cout << "if you want save game please write `SAVE FILE.TXT`\n";
}
//this is game for player versus computer
bool gameForComputer(int& sizer , char board[12][12],int& turn, bool& loadCheck) {
    while (true) {
        cout << "please write num and char in given format(A 1) \n";
        defaultText();
        string line1, line2;
        cin >> line1 >> line2;
        if ((line1.compare("SAVE") == 0)) {
            saveFile(sizer, '1', board, turn,line2);
            cout << "\ngame saved\n";
            continue;
        }
        else if ((line1.compare("LOAD") == 0)) {
            loadCheck = true;
            lastLoad = line2;
            cout << "\ntrying to load\n";
            return false;
        }

        int x = -999, y = -999;
        convertCord(x, y, line1, line2);
        //Checks is movement avalaible
        if (y > sizer - 1 || y < 0 || x>sizer - 1 || x < 0 || board[x][y] != moves::empty) {
            cout << "\nwrong ! Try again\n";
            continue;
        }
        board[x][y] = moves::user1;
        turn++;
        displayBoard(sizer, board);

        if (checkWin(moves::user1, x, y, board, sizer)) {
            cout << "\n player1 won\n";
            displayBoard(sizer, board);
            return true;
        }
        if (playComputerAndCheckWin(x, y, sizer, board)) {
            cout << "\n player2 won\n";
            displayBoard(sizer, board);
            return true;
        }
        if (turn == (sizer * sizer) / 2) {
            cout << "\n DRAW\n";
            return true;
        }
    }
}


//this is game for player versus player
bool gameForUser(int& sizer, char board[12][12], int& turn, bool& loadCheck) {
    while (true) {
        
        if (turn % 2 == 0)
            cout << "Turn for 1 \nplease write num and char in given format(A 1) \n";
        else
            cout << "Turn for 2 \nplease write num and char in given format(A 1) \n";
        defaultText();
        string line1, line2;
        cin >> line1 >> line2;
        if ((line1.compare("SAVE") == 0)) {
            saveFile(sizer, '1', board, turn, line2);
            cout << "\ngame saved\n";
            continue;
        }
        else if ((line1.compare("LOAD") == 0)) {
            loadCheck = true;
            lastLoad = line2;
            cout << "\ntrying to load\n";
            return false;
        }

        int x=-999, y=-999;
        convertCord(x, y, line1, line2);

        //Checks is movement avalaible
        if (y > sizer - 1 || y < 0 || x>sizer - 1 || x < 0 || board[x][y] != moves::empty) {
            cout << "\nwrong ! Try again\n";
            continue;
        }
        if (turn % 2 == 0)
            board[x][y] = moves::user1;
        else
            board[x][y] = moves::user2;

        displayBoard(sizer, board);
        int map[12][12] = { 0 };
        if (turn % 2 == 0) {
            if (checkWin(moves::user1, x, y, board, sizer)) {
                cout << "\n player1 won\n";
                displayBoard(sizer, board);
                return true;
            }
        }

        else {
            if (checkWin(moves::user2, x, y, board, sizer)) {
                cout << "\n player2 won\n";
                displayBoard(sizer, board);
                return true;
            }
        }
        turn++;
        if (turn == (sizer * sizer) / 2) {
            cout << "\n DRAW\n";
            return true;
        }

    }
}

int main(){
    char board[12][12];
    auto sizer = 12;
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

    decltype(sizer) turn = 0;
    displayBoard(sizer, board);

    while (true) {
        bool loadCheck = false;
        if (choice == '1') {
            if (gameForComputer(sizer, board, turn, loadCheck)) break;
        }

        else if (choice == '2') {
            if (gameForUser(sizer, board, turn, loadCheck)) break;
        }
        else {
            cout << "Wrong selection sorry I gotta go :(";
            break;
        }

        if (loadCheck) {
            loadCheck = false;
            loadFile(sizer, choice, board,turn);
        }
    }
    



}
