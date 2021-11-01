#include "AbstractHex.h"
#pragma once
using namespace std;
namespace omer {

    template<template<typename...> class T>//template for container
    class HexAdapter :public AbstractHex {
    public:
        //constructors
        HexAdapter(int size, char type);
        HexAdapter(char type, int size);
        HexAdapter(int size);
        HexAdapter(char type);

        //Big three
        HexAdapter(const HexAdapter& v2);
        HexAdapter& operator = (const HexAdapter& t);
        ~HexAdapter();

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
        int getSize()const;
        void playGame();

	//my helper functions
        void isWin(char player, int x, int y, bool winCondition[2], int map[50][50]);//helps is end to check win
        void createBoard();//open space for board than make them all dot
        void gameForComputer();//computer games playing in here
        void gameForUser();//user games playing in here

        void deepCopy(const HexAdapter& t);//deep copy for == copy constructor

        char getType()const;//returns game type
        int getLastX()const;//returns last played x
        int getLastY()const;//returns las plaed y
        int getWinCond()const;//return 1 or 2 for decided winner
    private:
        int size = 26;//game size
        char type = 1;//game type
        int totalmarked = 0;//total marked cells
        int lastX;//last played x
        int lastY;//last played y
        int winCond = 0;// 1 or 2 for decided winner
        T<T<Cell>> board;//all data in here I mean cell board
        Cell* last = nullptr;//for the lastMove we return this
    };

}
