using namespace std;
#include <vector>
#include <string>
#include <fstream>
enum moves { user1 = 'o', user2 = 'x', empty = '.' };//moves enum

class Hex {
public:
    explicit Hex(int size, char type);
    explicit Hex(char type, int size);
    explicit Hex(int size);
    explicit Hex(char type);
    Hex(const Hex& game);//compy constructor

    

    class Cell {                    //Cell clas holding types
    public:
        char getVal() const { return val; }
        void setVal(char c) { val = c; }
    private:
        char val = moves::empty;
    };
    void createBoard();             //open speace to hexcells
    void displayBoard() const;      //displays board
    Cell play();                    //play for computer
    Cell play(int x, char y);       //play function for user
    bool gameForUser();             //playing 1vs1 gaming
    bool gameForComputer();         //playing uservscomp
    void isWin(char player, int x, int y, bool winCondition[2], int map[50][50]);
    bool checkWin(char player);
    void playGame();
    void saveFile(string name) const;
    void loadFile(string name) ;


    int getsize()const { return size; }
    void setsize(int n) { size = n; }

    char gettype() const { return type; }
    void settype(char c) { type = c; }

    int gettotalmarked()const { return totalmarked; }
    void settotalmarked(int c) { totalmarked = c; }

    int getlastx() const { return lastx; }
    void setlastx(int c) { lastx = c; }

    int getlasty() const { return lasty; }
    void setlasty(int c) { lasty = c; }

    int getwinCond() const { return winCond; }
    void setwinCond(int c) { winCond = c; }
    

    int getUserScore()const { return maxPointUser; }
    void setUserScore(int c) { maxPointUser = c; }

    int getPcScore()const { return maxPointPc; }
    void setPcScore(int c) { maxPointPc = c; }

    void insertCord(int x, int y);

    int getXPointsLast() const {
        return xPoints[gettotalmarked() - 1];
    }
    int getYPointsLast() const {
        return yPoints[gettotalmarked() - 1];
    }

    void deleteCord();
    int* getXPoints()const { return xPoints; }
    int* getYPoints()const { return yPoints; }

    Cell** getBoard() const{return hexCells;}
    void callLoadSave(char ch);
    void checkMaxPointForUser(int x, int y, int& maxX , int& minX, int map[26][26]);
    void checkMaxPointForPc(int x, int y, int& maxX, int& minX, int map[26][26]);
    void setBoard(int x, int y, char c) {hexCells[x][y].setVal(c);}
    int getGameScore()const;
    Hex operator = (const Hex& game);//assigment constructor
    void operator --();
    void operator --(int);
    bool operator == (const Hex& a);
    void setXPoints(int num, int x) { xPoints[x] = num; }
    void setYPoints(int num, int x) { yPoints[x] = num; }
    void deletethings();
    
    friend istream& operator >>(istream& myfile, Hex& hex) {
        if (&myfile != &cin) {
            string line;
            int step = 0;
            int posind = 0;
            while (getline(myfile, line)) {
                if (step == 26) {
                    int size = line[0] - '0';
                    if (line.length() > 1) {
                        size *= 10;
                        size += line[1] - '0';
                    }
                    hex.setsize(size);
                }
                else if (step == 27) {
                    hex.settype(line[0]);
                }
                else if (step == 28) {
                    int totalmarked = 0;
                    int index = 0;
                    while (index < line.length()) {
                        totalmarked *= 10;
                        totalmarked += line[index++] - '0';
                    }
                    hex.settotalmarked(totalmarked);
                }
                else if (step == 29) {
                    int winCond = line[0] - '0';
                    hex.setwinCond(winCond);
                }
                else if (step == 30) {
                    int a = line[0] - '0';
                    if (line.length() > 1) {
                        a *= 10;
                        a += line[1] - '0';
                    }
                    hex.setlastx(a);
                }
                else if (step == 31) {
                    int a = line[0] - '0';
                    if (line.length() > 1) {
                        a *= 10;
                        a += line[1] - '0';
                    }
                    hex.setlasty(a);
                }
                else if(step < 26){
                    int idx = 0;
                    for (int i = 0; i < line.size(); i += 2) {
                        hex.getBoard()[step][idx++].setVal(line[i]);
                    }
                }
                else {
                    int a = 0;
                    int b = 0;
                    int idx = 0;
                    while (line[idx] != ',') {
                        a *= 10;
                        a += line[idx++] - '0';
                    }
                    idx++;
                    while (idx<line.length()) {
                        b *= 10;
                        b += line[idx++] - '0';
                    }
                    hex.setXPoints(a, posind);
                    hex.setYPoints(b, posind);
                    posind++;
                    
                }

                step++;
            }
        }
        
        return myfile;
    }
    friend ostream& operator <<(ostream& myfile, const Hex& hex) {
        if (&myfile == &cout) {
            hex.displayBoard();
        }
        else {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    myfile << hex.getBoard()[i][j].getVal() << " ";
                }
                myfile << endl;
            }
            myfile << hex.getsize() << endl;
            myfile << hex.gettype() << endl;
            myfile << hex.gettotalmarked() << endl;
            myfile << hex.getwinCond() << endl;
            myfile << hex.getlastx() << endl;
            myfile << hex.getlasty() << endl;
            for (int i = 0; i < hex.gettotalmarked(); i++) {
                myfile << hex.getXPoints()[i] << "," << hex.getYPoints()[i]<<endl;
            }
        }
        return myfile;
           
    }
    ~Hex();//deconstructor
private:
    Cell** hexCells = nullptr;
    int size = 26;
    char type = '1';
    int totalmarked = 0;
    int lastx = 0;
    int lasty = 0;
    int winCond = 0;
    int maxPointUser = 0;
    int maxPointPc = 0;
    int* xPoints = new int[26 * 26];
    int* yPoints = new int[26 * 26];
};

