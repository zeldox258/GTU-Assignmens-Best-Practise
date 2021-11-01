#include <iostream>
#include "Hex.h"
#include "helper.h"
#include <fstream>
#include <string>
using namespace std;

//basic info text
void infoText() {
    cout << "[1]-create new game\n[2]-continue exist game\n[3]-compareGames\n[4]-exit\n";
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

    vec.push_back(Hex(size, type));

}


void startGame() {
    vector<Hex> vec;
    Hex a(15, '1');
    Hex b(12, '2');
    b = a;
    vec.push_back(b);
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
            if (vec[one - 1]==(vec[two - 1])) {
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
}
