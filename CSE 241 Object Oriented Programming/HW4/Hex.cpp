#include <iostream>
#include "Hex.h"
#include <fstream>
#include <string>
using namespace std;

Hex::Hex(int size, char type) {
    if (size >= 5)this->size = size;
    this->type = type;
    createBoard();
}
Hex::Hex(char type, int size) {
    if (size >= 5)this->size = size;
    this->type = type;
    createBoard();
}
Hex::Hex(int size) {
    if (size >= 5)this->size = size;
    createBoard();
}
Hex::Hex(char type) {
    this->type = type;
    createBoard();
}
//deletes pointers
void Hex::deletethings() {
    if (hexCells != nullptr) {
        for (int i = 0; i < 26; i++) {
            delete[] hexCells[i];
        }
        delete[] hexCells;
        hexCells = nullptr;
    }
    
    delete[] xPoints;
    delete[] yPoints;
    xPoints = nullptr;
    yPoints = nullptr;
}
Hex::Hex(const Hex& game) {
    deletethings();
    createBoard();
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            hexCells[i][j].setVal(game.hexCells[i][j].getVal());
        }
    }
    size = game.getsize();
    type = game.gettype();
    totalmarked = game.gettotalmarked();
    lastx = game.getlastx();
    lasty = game.getlasty();
    winCond = game.getwinCond();
    maxPointUser = game.getUserScore();
    maxPointPc = game.getPcScore();
    xPoints = new int[26 * 26];
    yPoints = new int[26 * 26];
    for (int i = 0; i < game.gettotalmarked(); i++) {
        xPoints[i] = game.getXPoints()[i];
        yPoints[i] = game.getYPoints()[i];
    }
}

//de const
Hex::~Hex() {
    deletethings();
}
//assigment operator
Hex Hex::operator = (const Hex& game) {
    deletethings();
    createBoard();
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            hexCells[i][j].setVal(game.hexCells[i][j].getVal());
        }
    }
    size = game.getsize();
    type = game.gettype();
    totalmarked = game.gettotalmarked();
    lastx = game.getlastx();
    lasty = game.getlasty();
    winCond = game.getwinCond();
    maxPointUser = game.getUserScore();
    maxPointPc = game.getPcScore();
    xPoints = new int[26 * 26];
    yPoints = new int[26 * 26];
    for (int i = 0; i < game.gettotalmarked(); i++) {
        xPoints[i] = game.getXPoints()[i];
        yPoints[i] = game.getYPoints()[i];
    }
    return *this;
}

//play for computer
Hex::Cell Hex::play() {
    int tempx = lastx;
    int tempy = lasty;

    int prex = lastx;

    while (true) {
        if (tempx != size - 1)tempx++;
        while (tempx >= 0 && hexCells[tempx][tempy].getVal() != moves::empty)tempx--;
        if (tempx == -1) {
            tempx = prex;
            tempy++;
            if (tempy == size)tempy = 0;
            if (tempy == lasty)prex++;
        }
        else break;
    }
    Cell temp;
    temp.setVal(moves::user1);
    setlastx(tempx);
    setlasty(tempy);
    //hexCells[tempx][tempy].setVal(moves::user1);
    //int map[26][26] = { 0 };
    //checkMaxPointForPc(tempx, tempy, tempx, tempy, map);
    insertCord(tempx, tempy);
    cout << "computer played at:" << (char)(tempy + 'A') << " " << tempx + 1 << endl;
    totalmarked++;
    return temp;
}
//play function for users

Hex::Cell Hex::play(int x, char y) {
    Cell temp;
    int a = y - 'A';
    //cout << a << " " << x;
    if (totalmarked % 2 == 0)
        //hexCells[x][a].setVal(moves::user2);
        temp.setVal(moves::user2);
    else
        //hexCells[x][a].setVal(moves::user1);
        temp.setVal(moves::user1);
    insertCord(x, a);
    lastx = x;
    lasty = y - 'A';
    totalmarked++;
    return temp;
}

//displays board
void Hex::displayBoard()const {
    cout << " ";
    for (int i = 0; i < getsize(); i++)cout << char('A' + i) << " ";
    cout << endl;
    for (int i = 0; i < getsize(); i++) {
        cout << i + 1;
        if (i < 9) {
            for (int j = 0; j < i + 1; j++) {
                cout << " ";
            }
        }
        else {
            for (int j = 0; j < i; j++) {
                cout << " ";
            }
        }
        for (int j = 0; j < getsize(); j++) {
            cout << hexCells[i][j].getVal() << " ";
        }
        cout << endl;
    }
    if (gettype() == '1') {
        int a = getGameScore();
        cout <<"User Score :" << getGameScore() << endl;
    }
}
//delete cord from arrays and board
void Hex::deleteCord() {
    if (gettotalmarked() == 0)return;
    int x = getXPointsLast();
    int y = getYPointsLast();
    hexCells[x][y].setVal(moves::empty);
    settotalmarked(gettotalmarked() - 1);
}
//create board
void Hex::createBoard() {
    hexCells = new Cell * [26];
    for (int i = 0; i < 26; i++) {
        hexCells[i] = new Cell[26];
    }
}
//add cords to arrays
void Hex::insertCord(int x, int y) {
    xPoints[gettotalmarked()] = x;
    yPoints[gettotalmarked()] = y;
}
//undo
void Hex::operator--() {
    deleteCord();
}
//undo
void Hex::operator --(int) {
    deleteCord();
}
//compare
bool Hex::operator == (const Hex& a) {
    return a.gettotalmarked() == gettotalmarked();
}
//decide load or save 
void Hex::callLoadSave(char ch) {
    string name;
    cout << "please write file name\n";
    cin >> name;

    if (ch == 's')saveFile(name);
    else loadFile(name);
}

//computer vs player
bool Hex::gameForComputer() {
    while (true) {
        cout << *this;
        cout << "[q]-quit , [u] - undo movement , [s] - Save game ,[l] - Load game\n";
        cout << "please write num and char in given format(A 1) \n";
        int x, y;
        char c;
        cin >> c;
        if (c == 'q') return true;
        if (c == 'u') {
            (*this)--;
            (*this)--;
            continue;
        }
        if (c == 's' || c == 'l') {
            callLoadSave(c);
            continue;
        }
        cin >> x;
        y = c - 'A';
        x--;
        //Checks is movement avalaible
        if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || hexCells[x][y].getVal() != moves::empty) {
            cout << "\nwrong ! Try again\n";
            continue;
        }
        Cell tempo = play(x, c);
        getBoard()[x][y] = tempo;
        int map[26][26] = { 0 };
        int xx = x, yy = y;
        checkMaxPointForUser(x, y, xx, yy, map);
        /*hexCells[x][y].setVal(moves::user2);
        totalmarked++;
        nonempty++;*/
        

        if (checkWin(moves::user2)) {
            cout << "\n player1 won\n";
            winCond = 1;
            cout << *this;
            return true;
        }
        Cell temp = play();    
        getBoard()[getlastx()][getlasty()] = temp;
        int mapo[26][26] = { 0 };
        int a = getlastx();
        int b = getlasty();
        checkMaxPointForPc(getlastx(), getlasty(), a, b, mapo);

        if (checkWin(moves::user1)) {
            cout << "\n Computer won\n";
            winCond = 2;
            cout << *this;
            return true;
        }
        if (totalmarked == (size * size)) {
            cout << "\n DRAW\n";
            return true;
        }
    }
}


//this is game for player versus player
bool Hex::gameForUser() {
    while (true) {
        cout << *this;
        cout << "[q]-quit , [u] - undo movement , [s] - Save game ,[l] - Load game\n";
        if (totalmarked % 2 == 0)
            cout << "Turn for 1 \nplease write num and char in given format(A 1) \n";
        else
            cout << "Turn for 2 \nplease write num and char in given format(A 1) \n";

        int x, y;
        char c;
        cin >> c;
        if (c == 'q') return true;
        if (c == 'u') {
            (*this)--;
            continue;
        }
        if (c == 's' || c == 'l') {
            callLoadSave(c);
            continue;
        }
        cin >> x;
        y = c - 'A';
        x--;

        //Checks is movement avalaible
        if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || hexCells[x][y].getVal() != moves::empty) {
            cout << "\nwrong ! Try again\n";
            continue;
        }

        Cell tempo = play(x, c);
        getBoard()[x][y] = tempo;
        int map[26][26] = { 0 };
        int xx = x, yy = y;
        checkMaxPointForPc(x, y, xx, yy, map);
         
        if (checkWin(moves::user2)) {
            cout << "\n player1 won\n";
            winCond = 1;
            cout << *this;
            return true;
        }

        if (checkWin(moves::user1)) {
            cout << "\n player2 won\n";
            winCond = 2;
            cout << *this;
            return true;
        }

        if (totalmarked == (size * size)) {
            cout << "\n DRAW\n";
            return true;
        }

    }
}

//checks is the game ended
void Hex::isWin(char player, int x, int y, bool winCondition[2], int map[50][50]) {
    if (x >= size || y >= size || x < 0 || y < 0 || map[x][y] == 1 || (winCondition[0] && winCondition[1]))return;
    if (player == moves::user2 && hexCells[x][y].getVal() != moves::user2)return;
    if (player == moves::user1 && hexCells[x][y].getVal() != moves::user1)return;
    hexCells[x][y].setVal(hexCells[x][y].getVal() - ' ');
    if (player == moves::user2) {
        if (x == 0)winCondition[0] = true;
        if (x == size - 1)winCondition[1] = true;
    }
    if (player == moves::user1) {
        if (y == 0)winCondition[0] = true;
        if (y == size - 1)winCondition[1] = true;
    }
    map[x][y] = 1;

    isWin(player, x - 1, y, winCondition, map);
    isWin(player, x - 1, y + 1, winCondition, map);
    isWin(player, x, y + 1, winCondition, map);
    isWin(player, x + 1, y, winCondition, map);
    isWin(player, x + 1, y - 1, winCondition, map);
    isWin(player, x, y - 1, winCondition, map);
    if (winCondition[0] && winCondition[1]) return;
    hexCells[x][y].setVal(hexCells[x][y].getVal() + ' ');

}
// checks is anybody won
bool Hex::checkWin(char player) {
    for (int i = 0; i < size; i++) {
        int map[50][50] = { 0 };
        bool winCondition[2] = { false };
        if (player == moves::user2 && hexCells[0][i].getVal() == moves::user2) {
            isWin(player, 0, i, winCondition, map);
        }
        else if (hexCells[i][0].getVal() == moves::user1) {
            isWin(player, i, 0, winCondition, map);
        }
        if (winCondition[0] && winCondition[1])
            return true;
    }


    return false;
}

//saves game to file
void Hex::saveFile(string name) const{
    ofstream myfile;
    myfile.open(name);  
    myfile << *this;
    myfile.close();

}
//loading file if its exist from file.txt
void Hex::loadFile(string name) {
    xPoints = new int[26 * 26];
    yPoints = new int[26 * 26];

    //cout << name;
    ifstream myfile(name);
    if (myfile.is_open()) {
        myfile >> *this;
        myfile.close();
        cout << "\nsuccesfully loaded\n";
    }

    else cerr << "there is no loadable file sorry :(";
    

}


//decide game type and start game
void Hex::playGame() {
    if (winCond == 1) {
        cout << "\n player1 won\n";
        cout << *this;
        return;
    }

    else if (winCond == 2) {
        cout << "\n player2 or Computer won\n";
        cout << *this;
        return;
    }

    if (type == '1') {
        gameForComputer();
    }
    else {
        gameForUser();
    }
}

//max point for user
void Hex::checkMaxPointForUser(int x, int y, int& maxX, int& minX, int map[26][26]) {
    if (x >= getsize() || y >= getsize() || x < 0 || y < 0 || map[x][y] == 1 )return;
    if (hexCells[x][y].getVal() != moves::user2)return;

    maxX = max(x, maxX);
    minX = min(x, minX);
    
    setUserScore(max(getUserScore(), (maxX - minX)));

    map[x][y] = 1;

    checkMaxPointForUser( x - 1, y, maxX, minX, map);
    checkMaxPointForUser( x - 1, y + 1, maxX, minX, map);
    checkMaxPointForUser( x, y + 1, maxX, minX, map);
    checkMaxPointForUser( x + 1, y, maxX, minX, map);
    checkMaxPointForUser( x + 1, y - 1, maxX, minX, map);
    checkMaxPointForUser( x, y - 1, maxX, minX, map);


}


//max point for pc
void Hex::checkMaxPointForPc(int x, int y, int& maxX, int& minX, int map[26][26]) {
    if (x >= getsize() || y >= getsize() || x < 0 || y < 0 || map[x][y] == 1)return;
    if (hexCells[x][y].getVal() != moves::user1)return;

    maxX = max(y, maxX);
    minX = min(y, minX);

    setPcScore(max(getPcScore(), (maxX - minX)));

    map[x][y] = 1;

    checkMaxPointForUser(x - 1, y, maxX, minX, map);
    checkMaxPointForUser(x - 1, y + 1, maxX, minX, map);
    checkMaxPointForUser(x, y + 1, maxX, minX, map);
    checkMaxPointForUser(x + 1, y, maxX, minX, map);
    checkMaxPointForUser(x + 1, y - 1, maxX, minX, map);
    checkMaxPointForUser(x, y - 1, maxX, minX, map);
}

// return games score
int Hex::getGameScore()const {
    if (getwinCond() == 1) return getsize();
    return getUserScore()-getPcScore();
}


