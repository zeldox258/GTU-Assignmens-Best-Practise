#include "AbstractHex.h"
#include <vector>

#pragma once
namespace omer {
    class HexVector :public AbstractHex {
    public:
        HexVector(int size, char type);
        HexVector(char type, int size);
        HexVector(int size);
        HexVector(char type);
        HexVector(const HexVector& v2);
        HexVector& operator = (const HexVector& t);
        ~HexVector();
        void print() const;
        void readFromFile(const string& fileName);
        void writeToFile(const string& fileName);
        void reset();
        void setSize(const int& size);
        void play();
        void play(const int& x, const int& y);
        bool isEnd(char player);
        void isWin(char player, int x, int y, bool winCondition[2], int map[50][50]);
        Cell operator()(int a, int b)const;
        bool operator == (AbstractHex* second)const;
        Cell lastMove()const;
        int numberOfMoves()const;
        void createBoard();
        void playGame();
        void gameForComputer();
        void gameForUser();
        int getSize()const;
        void deepCopy(const HexVector& t);

        char getType()const;
        int getLastX()const;
        int getLastY()const;
        int getWinCond()const;
    private:
        int size = 26;
        char type = 1;
        int totalmarked = 0;
        int lastX;
        int lastY;
        int winCond = 0;
        vector<vector<Cell>> board;
        vector<Cell> moves;
    };
}