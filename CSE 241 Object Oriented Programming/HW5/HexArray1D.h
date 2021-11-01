#include "AbstractHex.h"

#pragma once
namespace omer {

    class HexArray1D :public AbstractHex {
    public:
        //constructors
        HexArray1D(int size, char type);
        HexArray1D(char type, int size);
        HexArray1D(int size);
        HexArray1D(char type);

        //Big three
        HexArray1D(const HexArray1D& v2);
        HexArray1D& operator = (const HexArray1D& t);
        ~HexArray1D();

        // pure virtual functions
        void print() const;
        void readFromFile(const string& fileName);
        void writeToFile(const string& fileName);
        void reset();
        void setSize(const int& size);
        void play();
        void play(const int& x, const int& y);
        bool isEnd(char player);
        Cell operator()(int a, int b)const;
        bool operator == (AbstractHex* second)const;
        Cell lastMove()const;
        int numberOfMoves()const;

        //my virtual functions
        int getSize()const;
        void playGame();
        void isWin(char player, int x, int y, bool winCondition[2], int map[50][50]);
        void createBoard();
        void gameForComputer();
        void gameForUser();

        void deepCopy(const HexArray1D& t);

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
        Cell* board;
        Cell* last = nullptr;
    };

}