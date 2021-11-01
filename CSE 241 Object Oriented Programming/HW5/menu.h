#include "AbstractHex.h"
#include<vector>
#include <iostream>
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include "HexAdapter.hpp"
#include <queue>
#pragma once
namespace omer {
	//vector<AbstractHex*> games;
	void textMenu();
	void textAddMenu();
	void startGame();
	void addGame();
	void addHexVector(int size, char type);
	void addHexArray1D(int size, char type);
	void addHexAdepterDeque(int size, char type);
	void addHexAdepterVector(int size, char type);
	int getSize();
	char getType();
	void choseGame();
	void compareGames();
	bool isPropper(AbstractHex* game);
	void checkPropper();
	void loadGame();
}
