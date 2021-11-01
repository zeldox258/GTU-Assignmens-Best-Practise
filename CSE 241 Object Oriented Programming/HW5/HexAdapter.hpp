#include "HexAdapter.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#pragma once
using namespace std;
//enum moves { user1 = 'o', user2 = 'x', empty = '.' };//moves enum
namespace omer {
	//enum moves { user1 = 'o', user2 = 'x', empty = '.' };//moves enum
	template<template<typename...> class T>
	HexAdapter<T>::HexAdapter(int size, char type) {
		if (size >= 5)this->size = size;
		this->type = type;
		createBoard();
	}
	template<template<typename...> class T>
	HexAdapter<T>::HexAdapter(char type, int size) {
		if (size >= 5)this->size = size;
		this->type = type;
		createBoard();
	}
	template<template<typename...> class T>
	HexAdapter<T>::HexAdapter(int size) {
		if (size >= 5)this->size = size;
		createBoard();
	}
	template<template<typename...> class T>
	HexAdapter<T>::HexAdapter(char type) {
		this->type = type;
		createBoard();
	}

	template<template<typename...> class T>
	HexAdapter<T>::HexAdapter(const HexAdapter& v2) {
		deepCopy(v2);
	}
	template<template<typename...> class T>
	HexAdapter<T>& HexAdapter<T>::operator = (const HexAdapter<T>& t) {
		deepCopy(t);
		return *this;
	}
	template<template<typename...> class T>
	HexAdapter<T>::~HexAdapter() {
	}

	template<template<typename...> class T>
	void HexAdapter<T>::print() const {
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
				cout << board[i][j].getVal() << " ";
			}
			cout << endl;
		}
	}
	template<template<typename...> class T>
	void HexAdapter<T>::readFromFile(const string& fileName) {
		string line;
		ifstream myfile(fileName);
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
						board[step][idx++].setVal(line[i]);
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
	template<template<typename...> class T>
	void HexAdapter<T>::writeToFile(const string& fileName) {
		ofstream myfile;
		myfile.open(fileName);
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				myfile << board[i][j].getVal() << " ";
			}
			myfile << endl;
		}
		myfile << size << endl;
		myfile << type << endl;
		myfile << totalmarked << endl;
		myfile << winCond << endl;
		myfile.close();
	}
	template<template<typename...> class T>
	void HexAdapter<T>::reset() {
		totalmarked = 0;
		board.clear();
		last = NULL;
		createBoard();
	}
	template<template<typename...> class T>
	void HexAdapter<T>::setSize(const int& size) {
		totalmarked = 0;
		board.clear();
		this->size = size;
		last = NULL;
		createBoard();
	}
	template<template<typename...> class T>
	void HexAdapter<T>::play() {
		cout << totalmarked << endl;
		int tempx = lastX;
		int tempy = lastY;

		int prex = lastX;

		while (true) {
			if (tempx != size - 1)tempx++;
			while (tempx >= 0 && board[tempx][tempy].getVal() != '.')tempx--;
			if (tempx == -1) {
				tempx = prex;
				tempy++;
				if (tempy == size)tempy = 0;
				if (tempy == lastY)prex++;
			}
			else break;
		}
		board[tempx][tempy].setVal('o');
		board[tempx][tempy].setX(tempx);
		board[tempx][tempy].setY(tempy);
		last = &board[tempx][tempy];
		cout << "computer played at:" << (char)(tempy + 'A') << " " << tempx + 1 << endl;
		totalmarked++;
	}
	template<template<typename...> class T>
	void HexAdapter<T>::play(const int& x, const int& y) {
		int a = y - 'A';
		//cout << a << " " << x;
		if (totalmarked % 2 == 0)
			board[x][a].setVal('x');
		else
			board[x][a].setVal('o');
		board[x][a].setX(x);
		board[x][a].setY(a);
		lastX = x;
		lastY = y - 'A';
		last = &board[x][a];
		totalmarked++;
	}
	template<template<typename...> class T>
	bool HexAdapter<T>::isEnd(char player) {
		for (int i = 0; i < size; i++) {
			int map[50][50] = { 0 };
			bool winCondition[2] = { false };
			if (player == 'x' && (*this)(0, i).getVal() == 'x') {
				isWin(player, 0, i, winCondition, map);
			}
			else if ((*this)(i, 0).getVal() == 'o') {
				isWin(player, i, 0, winCondition, map);
			}
			if (winCondition[0] && winCondition[1])
				return true;
		}

		return false;
	}
	template<template<typename...> class T>
	void HexAdapter<T>::isWin(char player, int x, int y, bool winCondition[2], int map[50][50]) {
		if (x >= size || y >= size || x < 0 || y < 0 || map[x][y] == 1 || (winCondition[0] && winCondition[1]))return;
		if (player == 'x' && (*this)(x, y).getVal() != 'x')return;
		if (player == 'o' && (*this)(x, y).getVal() != 'o')return;

		(*this)(x, y).setVal((*this)(x, y).getVal() - ' ');
		if (player == 'x') {
			if (x == 0)winCondition[0] = true;
			if (x == size - 1)winCondition[1] = true;
		}
		if (player == 'o') {
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
		(*this)(x, y).setVal((*this)(x, y).getVal() + ' ');
	}
	template<template<typename...> class T>
	Cell HexAdapter<T>::operator()(int a, int b)const {
		return board[a][b];
	}
	template<template<typename...> class T>
	bool HexAdapter<T>::operator==(AbstractHex* second) const {
		if (second->getSize() != this->getSize()) return false;
		for (int i = 0; i < second->getSize(); i++) {
			for (int j = 0; j < second->getSize(); j++) {
				if ((*this)(i, j).getVal() != (*second)(i, j).getVal()) return false;
			}
		}

		return true;
	}
	template<template<typename...> class T>
	Cell HexAdapter<T>::lastMove() const {
		try {
			if (size > 0)return *last;
			else throw out_of_range("error");
		}
		catch (exception e) {
			cout << e.what();
		}
		
	}
	template<template<typename...> class T>
	int HexAdapter<T>::numberOfMoves() const {
		return totalmarked;
	}
	template<template<typename...> class T>
	int HexAdapter<T>::getSize() const {
		return size;
	}
	template<template<typename...> class T>
	void HexAdapter<T>::playGame() {
		if (winCond == 1) {
			cout << "\n player1 won\n";
			print();
			return;
		}

		else if (winCond == 2) {
			cout << "\n player2 or Computer won\n";
			print();
			return;
		}
		else if (winCond == 3) {
			cout << "\nDRAW !!\n";
			print();
			return;
		}

		print();
		if (type == '1') {
			gameForComputer();
		}
		else {
			gameForUser();
		}
	}
	template<template<typename...> class T>
	void HexAdapter<T>::createBoard() {
		for (int i = 0; i < 26; i++) {
			T<Cell> tempCell;
			for (int j = 0; j < 26; j++) {
				tempCell.insert(tempCell.begin(), Cell(i, j, '.'));
			}
			board.insert(board.begin(), tempCell);
		}
	}
	template<template<typename...> class T>
	void HexAdapter<T>::gameForComputer() {
		while (true) {
			cout << "[1]-save\n[2]-load\n[3]-last move\n[4]-set size\n[5]-reset\n[q]-quit\n";
			cout << "please write num and char in given format(A 1) \n";
			int x, y;
			char c;
			cin >> c;
			if (c == 'q') return;
			if (c == '1' || c == '2') {
				string s;
				cout << "give me filename:";
				cin >> s;
				if (c == '1')
					writeToFile(s);
				else {
					readFromFile(s);
					print();
				}
				continue;
			}
			if (c == '3') {
				Cell l = lastMove();
				cout << l.getVal() << " " << l.getX() << " " << l.getY() << endl;
				continue;
			}
			if (c == '4') {
				int a;
				cout << "give me new size:";
				cin >> a;
				if (a >= 6 && a <= 26)
					setSize(a);
				else
					cout << "WRONG TYPE \n";
				print();
				continue;
			}
			if (c == '5') {
				reset();
				print();
				continue;
			}

			cin >> x;
			y = c - 'A';
			x--;
			//Checks is movement avalaible
			if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || (*this)(x, y).getVal() != '.') {
				cout << "\nwrong ! Try again1\n";
				continue;
			}
			play(x, c);

			print();

			if (isEnd('x')) {
				cout << "\n player1 won\n";
				winCond = 1;
				print();
				return;
			}
			play();
			print();
			if (isEnd('o')) {
				cout << "\n Computer won\n";
				winCond = 2;
				print();
				return;
			}
			if (totalmarked == (size * size)) {
				cout << "\n DRAW\n";
				return;
			}
		}
	}
	template<template<typename...> class T>
	void HexAdapter<T>::gameForUser() {
		while (true) {
			cout << "[1]-save\n[2]-load\n[3]-last move\n[4]-set size\n[5]-reset\n[q]-quit\n";
			if (totalmarked % 2 == 0)
				cout << "Turn for 1 \nplease write num and char in given format(A 1) \n";
			else
				cout << "Turn for 2 \nplease write num and char in given format(A 1) \n";

			int x, y;
			char c;
			cin >> c;

			if (c == '1' || c == '2') {
				string s;
				cout << "give me filename:";
				cin >> s;
				if (c == '1')
					writeToFile(s);
				else {
					readFromFile(s);
					print();
				}
				continue;
			}
			if (c == '3') {
				Cell l = lastMove();
				cout << l.getVal() << " " << l.getX() << " " << l.getY() << endl;
				continue;
			}
			if (c == '4') {
				int a;
				cout << "give me new size:";
				cin >> a;
				if (a >= 6 && a <= 26)
					setSize(a);
				else
					cout << "WRONG TYPE \n";
				print();
				continue;
			}
			if (c == '5') {
				reset();
				print();
				continue;
			}
			if (c == 'q') return;
			cin >> x;
			y = c - 'A';
			x--;

			//Checks is movement avalaible
			if (y > size - 1 || y < 0 || x>size - 1 || x < 0 || (*this)(x, y).getVal() != '.') {
				cout << "\nwrong ! Try again2\n";
				continue;
			}


			play(x, (char)(y + 'A'));

			print();
			if (totalmarked % 2 == 0) {
				if (isEnd('x')) {
					cout << "\n player1 won\n";
					winCond = 1;
					print();
					return;
				}
			}

			else {
				if (isEnd('o')) {
					cout << "\n player2 won\n";
					winCond = 2;
					print();
					return;
				}
			}
			if (totalmarked == (size * size)) {
				cout << "\n DRAW\n";
				winCond = 3;
				return;
			}

		}
	}

	template<template<typename...> class T>
	void HexAdapter<T>::deepCopy(const HexAdapter& t) {
		size = t.getSize();
		type = t.getType();
		int totalmarked = t.numberOfMoves();
		int lastX = t.getLastX();
		int lastY = t.getLastY();
		int winCond = t.getWinCond();

		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				board[i][j].setVal(t.board[i][j].getVal());
			}
		}
		last = t.last;
	}
	template<template<typename...> class T>
	char HexAdapter<T>::getType()const
	{
		return type;
	}
	template<template<typename...> class T>
	int HexAdapter<T>::getLastX()const
	{
		return lastX;
	}
	template<template<typename...> class T>
	int HexAdapter<T>::getLastY()const
	{
		return lastY;
	}
	template<template<typename...> class T>
	int HexAdapter<T>::getWinCond()const
	{
		return lastY;
	}
}
