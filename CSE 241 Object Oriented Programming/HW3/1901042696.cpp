#include <iostream>
#include <vector>
#include <fstream>
#include <string>
enum moves { user1 = 'o', user2 = 'x', empty = '.' };//moves enum
using namespace std;
//static var for the static function
static int nonempty = 0;
//game class
class Hex {

public:
    int gameSaveNum = 1;
    int size = 26;
    char type = '1';
    void createBoard();
    int totalmarked = 0;
    //char gameType;
    int lastx = 0;
    int lasty = 0;
    int winCond = 0;
    Hex(int size, char type, int gsn) {
        if (size >= 5)this->size = size;
        this->type = type;
        gameSaveNum = gsn;
        createBoard();
    }
    Hex(char type, int size, int gsn) {
        if (size >= 5)this->size = size;
        this->type = type;
        gameSaveNum = gsn;
        createBoard();
    }
    Hex(int size, int gsn) {
        if (size >= 5)this->size = size;
        gameSaveNum = gsn;
        createBoard();
    }
    Hex(char type, int gsn) {
        this->type = type;
        gameSaveNum = gsn;
        createBoard();
    }

    void saveFile();
    void loadFile();
    int getSize();
    void displayBoard();
    void play();
    void play(int x, char y);
    void isWin(char player, int x, int y, bool winCondition[2], int map[50][50]);
    bool checkWin(char player);
    void playGame();
    static int calcTotalMarked() { return nonempty; }
    bool gameForUser();
    bool gameForComputer();
    bool compare(Hex a) {
        return totalmarked > a.totalmarked;
    }
private:


    class Cell {
    public:
        char val = moves::empty;
        Cell(char val) {
            this->val = val;
        }
        void  setVal(char c) {
            val = c;
        }
    };
    vector<vector<Cell>> hexCells;
};
//createing board
void Hex::createBoard() {
    //hexCells.clear();
    for (int i = 0; i < 26; i++) {
        vector<Cell> tempCell;
        for (int j = 0; j < 26; j++) {
            tempCell.push_back(Cell(moves::empty));
        }
        hexCells.push_back(tempCell);
    }
}
//play for computer
void Hex::play() {
    int tempx = lastx;
    int tempy = lasty;

    int prex = lastx;

    while (true) {
        if (tempx != size - 1)tempx++;
        while (tempx >= 0 && hexCells[tempx][tempy].val != moves::empty)tempx--;
        if (tempx == -1) {
            tempx = prex;
            tempy++;
            if (tempy == size)tempy = 0;
            if (tempy == lasty)prex++;
        }
        else break;
    }
    hexCells[tempx][tempy].setVal(moves::user1);
    cout << "computer played at:" << (char)(tempy + 'A') << " " << tempx + 1 << endl;
    totalmarked++;
    nonempty++;
}
//play function for users
void Hex::play(int x, char y) {
    int a = y - 'A';
    //cout << a << " " << x;
    if (totalmarked % 2 == 0)
        hexCells[x][a].setVal(moves::user2);
    else
        hexCells[x][a].setVal(moves::user1);
    lastx = x;
    lasty = y - 'A';
    totalmarked++;
    nonempty++;
}

//displays board
void Hex::displayBoard() {
    cout << " ";
    for (int i = 0; i < size; i++)cout << char('A' + i) << " ";
    cout << endl;
    for (int i = 0; i < size; i++) {
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
        for (int j = 0; j < size; j++) {
            cout << hexCells[i][j].val << " ";
        }
        cout << endl;
    }
}
//checks is the game ended
void Hex::isWin(char player, int x, int y, bool winCondition[2], int map[50][50]) {
    if (x >= size || y >= size || x < 0 || y < 0 || map[x][y] == 1 || (winCondition[0] && winCondition[1]))return;
    if (player == moves::user2 && hexCells[x][y].val != moves::user2)return;
    if (player == moves::user1 && hexCells[x][y].val != moves::user1)return;
    hexCells[x][y].setVal(hexCells[x][y].val - ' ');
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
    hexCells[x][y].setVal(hexCells[x][y].val + ' ');

}
// checks is anybody won
bool Hex::checkWin(char player) {
    for (int i = 0; i < size; i++) {
        int map[50][50] = { 0 };
        bool winCondition[2] = { false };
        if (player == moves::user2 && hexCells[0][i].val == moves::user2) {
            isWin(player, 0, i, winCondition, map);
        }
        else if (hexCells[0][i].val == moves::user1) {
            isWin(player, i, 0, winCondition, map);
        }
        if (winCondition[0] && winCondition[1])
            return true;
    }


    return false;
}
//computer vs player
bool Hex::gameForComputer() {
    while (true) {
        cout << "if you want quit type 'q'\n";
        cout << "please write num and char in given format(A 1) \n";
        int x, y;
        char c;
        cin >> c;
        if (c == 'q') return true;
        cin >> x;
        y = c - 'A';
        x--;
        //Checks is movement avalaible
        if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || hexCells[x][y].val != moves::empty) {
            cout << "\nwrong ! Try again\n";
            continue;
        }
        play(x, c);
        /*hexCells[x][y].setVal(moves::user2);
        totalmarked++;
        nonempty++;*/
        displayBoard();

        if (checkWin(moves::user2)) {
            cout << "\n player1 won\n";
            winCond = 1;
            displayBoard();
            return true;
        }
        play();
        displayBoard();
        if (checkWin(moves::user1)) {
            cout << "\n Computer won\n";
            winCond = 2;
            displayBoard();
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
        cout << "if you want quit type 'q'\n";
        if (totalmarked % 2 == 0)
            cout << "Turn for 1 \nplease write num and char in given format(A 1) \n";
        else
            cout << "Turn for 2 \nplease write num and char in given format(A 1) \n";

        int x, y;
        char c;
        cin >> c;
        if (c == 'q') return true;
        cin >> x;
        y = c - 'A';
        x--;

        //Checks is movement avalaible
        if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || hexCells[x][y].val != moves::empty) {
            cout << "\nwrong ! Try again\n";
            continue;
        }


        play(x, (char)(y + 'A'));

        displayBoard();
        if (totalmarked % 2 == 0) {
            if (checkWin(moves::user2)) {
                cout << "\n player1 won\n";
                winCond = 1;
                displayBoard();
                return true;
            }
        }

        else {
            if (checkWin(moves::user1)) {
                cout << "\n player2 won\n";
                winCond = 2;
                displayBoard();
                return true;
            }
        }
        if (totalmarked == (size * size)) {
            cout << "\n DRAW\n";
            return true;
        }

    }
}

//starts game after checks is it end
void Hex::playGame() {
    if (winCond == 1) {
        cout << "\n player1 won\n";
        displayBoard();
        return;
    }

    else if (winCond == 2) {
        cout << "\n player2 or Computer won\n";
        displayBoard();
        return;
    }

    displayBoard();

    if (type == '1') {
        gameForComputer();
    }
    else {
        gameForUser();
    }

    saveFile();

}
//returns game size
int Hex::getSize() {
    return size;
}
//saves game to file
void Hex::saveFile() {
    ofstream myfile;
    string name = "";
    for (int i = 0; i < gameSaveNum; i++) {
        name += "a";
    }
    name += ".txt";
    //cout << name;
    myfile.open(name);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            myfile << hexCells[i][j].val << " ";
        }
        myfile << endl;
    }
    myfile << size << endl;
    myfile << type << endl;
    myfile << totalmarked << endl;
    myfile << winCond << endl;
    myfile.close();
}
//loading file if its exist from file.txt
void Hex::loadFile() {
    string line;
    string name = "";
    for (int i = 0; i < gameSaveNum; i++) {
        name += "a";
    }
    name += ".txt";
    //cout << name;
    ifstream myfile(name);
    if (myfile.is_open()) {
        int step = 0;
        while (getline(myfile, line)) {

            if (step == 26) {
                size = line[0] - '0';
                if (line.size() > 1) {
                    size *= 10;
                    size += line[1] - '0';
                }
            }
            else if (step == 27) {
                type = line[0];
            }
            else if (step == 28) {
                totalmarked = 0;
                int index = 0;
                while (index < line.size()) {
                    totalmarked *= 10;
                    totalmarked += line[index++] - '0';
                }
            }
            else if (step == 29) {
                winCond = line[0] - '0';
            }
            else {
                int idx = 0;
                for (int i = 0; i < line.size(); i += 2) {
                    hexCells[step][idx++].setVal(line[i]);
                }
            }

            step++;
        }
        myfile.close();
        return;
        cout << "\nsuccesfully loaded\n";
        //displayBoard(size);
    }

    else cerr << "there is no loadable file sorry :(";

}
//basic info text
void infoText() {
    cout << "[1]-create new game\n[2]-continue exist game\n[3]-compareGames\n[4]-exit\n";
}

//this function reload all saves games
vector<Hex> reloadGames() {
    vector<Hex> vec;

    string line;
    ifstream myfile("savess.txt");
    if (myfile.is_open()) {
        int step = 0;
        while (getline(myfile, line)) {

            Hex temp = Hex(25, line[0] - '0');
            temp.loadFile();

            vec.push_back(temp);
        }
        myfile.close();
    }

    else {}//cerr << "there is no loadable file sorry :(";

    for (int i = 0; i < vec.size(); i++) {
        nonempty += vec[i].totalmarked;
    }

    return vec;
}
//this function increament game nums
void editSaves(int size) {
    ofstream myfile;
    myfile.open("savess.txt");

    for (int j = 1; j <= size; j++) {
        myfile << j << "\n";
    }


    myfile.close();
}
//creates another game
void createGame(vector<Hex>& vec) {
    cout << "please write following things\n";
    int size;
    char type;
    cout << "board size :";
    cin >> size;
    cout << "Game type [1] to computer [2] to friend:";
    cin >> type;

    vec.push_back(Hex(size, type, vec.size() + 1));
    editSaves(vec.size());
}

int main() {
    vector<Hex> vec = reloadGames();
    cout << "Welcome to hex game\n";
    bool flag = true;
    while (flag) {
        infoText();
        int chc;
        cin >> chc;
        switch (chc) {
        case 1:
            createGame(vec);
            vec[vec.size() - 1].playGame();
            break;
        case 2:
            if (vec.size() == 0) cout << "there is no avalaible game\n";
            else {
                cout << "there are " << vec.size() << "game now which one doyou want to play ? 1 to " << vec.size() << "\n";
                int gameNum;
                cin >> gameNum;
                gameNum--;
                if (gameNum >= vec.size()) {
                    cout << "\nwrong entry\n";
                    continue;
                }
                vec[gameNum].playGame();
            }
            break;
        case 3:
            int one, two;
            cout << "\nenter first game :";
            cin >> one;
            cout << "\nenter second game :";
            cin >> two;
            if (one > vec.size() || two > vec.size()) {
                cout << "wrong try again\n";
                break;
            }
            if (vec[one - 1].compare(vec[two - 1])) {
                cout << "first game have more cells\n";
            }
            else {
                cout << "second game have more cells\n";
            }
            break;
        case 4:
            flag = false;
            break;
        default:
            cout << "wrong entry try again";
            break;
        }
    }
    cout << nonempty;

    return 0;
}
