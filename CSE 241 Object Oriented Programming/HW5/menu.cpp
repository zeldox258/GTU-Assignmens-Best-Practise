#include "menu.h"
#pragma once

using namespace std;
using namespace omer;
namespace omer {
	vector<AbstractHex*> games;

	void textMenu() {
		cout << "[1]-create game \n[2]-play exist game\n[3]-compare two game\n[4]-check is it propper\n[5]-exit\n";
	}
	void textAddMenu() {
		cout << "[1]-addHexVector \n[2]-addHexArray1D\n[3]-addHexAdepterDeque\n[4]-addHexAdepterVector\n";

	}
	void startGame() {
		while (true) {
			textMenu();
			int ch;
			cin >> ch;
			if (ch == 1) {
				addGame();
			}
			else if (ch == 2) {
				choseGame();
			}
			else if (ch == 3) {
				compareGames();
			}
			else if (ch == 4) {
				checkPropper();
			}
			else if (ch == 5) {
				cout << "BABAY\n";
				return;
			}
			else {
				cout << "Wrong selection try again ! \n";
			}
		}
	}

	void addGame() {

		cout << "[1]-Load Game\n[2]-create new game\nAnswer :";
		char cho;
		cin >> cho;
		if (cho == '1') {
			loadGame();
		}
		else if (cho == '2') {
			int size = getSize();
			char type = getType();
			textAddMenu();

			int ch;
			cin >> ch;
			if (ch == 1) {
				addHexVector(size, type);
			}
			else if (ch == 2) {
				addHexArray1D(size, type);
			}
			else if (ch == 3) {
				addHexAdepterDeque(size, type);
			}
			else if (ch == 4) {
				addHexAdepterVector(size, type);
			}
			else {
				cout << "Wrong selection try again ! \n";
			}
		}
		else {
			cout << "Wrong selection try again ! \n";
		}
		
	}

	void addHexVector(int size, char type) {
		games.push_back(new HexVector(size, type));
	}

	void addHexArray1D(int size, char type) {
		games.push_back(new HexArray1D(size, type));
	}

	void addHexAdepterDeque(int size, char type) {
		games.push_back(new HexAdapter<deque>(size, type));
	}

	void addHexAdepterVector(int size, char type) {
		games.push_back(new HexAdapter<vector>(size, type));
	}

	int getSize() {
		int res = 0;
		while (res < 5 || res> 26) {
			cout << "size :";
			cin >> res;
			if (res < 5 || res> 26) {
				cout << "wrong try again\n";
			}
		}

		return res;
	}

	char getType() {
		char res = '3';
		while (res != '1' && res != '2') {
			cout << "[1]-vs computer \n[2]-vs player\n";
			cin >> res;
			if (res != '1' && res != '2') {
				cout << "wrong try again\n";
			}
		}
		return res;
	}

	void choseGame() {
		int g;
		cout << "game index :";
		cin >> g;

		if (g >= games.size()) {
			cout << "wrong indexe try again !\n";
			return;
		}

		games[g]->playGame();

	}

	void compareGames() {
		int g1, g2;
		cout << "first game index :";
		cin >> g1;
		cout << "second game index :";
		cin >> g2;

		if (g1 >= games.size() || g2 >= games.size()) {
			cout << "wrong indexes try again !\n";
			return;
		}

		if (g1 == g2) {
			cout << "This games are equal !! \n";
		}
		else {
			cout << "This games are not equal !! \n";
		}
	}
	bool isPropper(AbstractHex* game){
		int size = game->getSize();
		if (size < 6 || size >26)return false;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((*game)(i, j).getVal() != 'x' && (*game)(i, j).getVal() != 'X' && (*game)(i, j).getVal() != 'O' && (*game)(i, j).getVal() != 'o' && (*game)(i, j).getVal() != '.')
					return false;
			}
		}

		return true;
	}
	void checkPropper(){
		int g;
		cout << "game index :";
		cin >> g;

		if (g >= games.size()) {
			cout << "wrong indexe try again !\n";
			return;
		}

		if (isPropper(games[g])) {
			cout << "this is great game\n";
		}
		else
			cout << "this is nasty game \n";
	}
	void loadGame(){
		string s;
		cout <<"File Name :";
		cin >> s;
		cout << "Which type do you want to convert ?\n[1]-HexVector \n[2]-HexArray1D\n[3]-HexAdepterDeque\n[4]-HexAdepterVector\nAnswer:";
		char ch;
		cin >> ch;
		if (ch == '1') {
			addHexVector(0, '1');
		}
		else if (ch == '2') {
			addHexArray1D(0, '1');
		}
		else if (ch == '3') {
			addHexAdepterDeque(0, '1');
		}
		else if (ch == '4') {
			addHexAdepterVector(0, '1');
		}
		else {
			cout << "Wrong selection try again ! \n";
			return;
		}
		games[games.size() - 1]->readFromFile(s);
	}
}