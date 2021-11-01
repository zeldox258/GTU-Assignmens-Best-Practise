#include <string>
#include "Cell.h"
#pragma once


using namespace std;

namespace omer {
    enum class moves { user1 = 'o', user2 = 'x', empty = '.' };//moves enum
    class AbstractHex {
    public:
        // pure virtual functions
        virtual void print() const = 0;//prints board
        virtual void readFromFile(const string& fileName) = 0;//load games
        virtual void writeToFile(const string& fileName) = 0;//save games
        virtual void reset() = 0;//resetgames
        virtual void setSize(const int& size) = 0;//set game size with new value than reset game
        virtual void play() = 0;//one step plat for computer
        virtual void play(const int& x, const int& y) = 0;//one step plat for users
        virtual bool isEnd(char player) = 0;//checks game is end
        virtual Cell operator()(int a, int b)const = 0;//returns games cell which given index
        virtual bool operator == (AbstractHex* second)const = 0;//compare two games
        virtual Cell lastMove()const = 0;//returns last move
        virtual int numberOfMoves()const = 0;//returns total marked cell in selected game
        virtual int getSize()const = 0;//returns size
        virtual void playGame() = 0;//starts game 
    private:
    };
}
