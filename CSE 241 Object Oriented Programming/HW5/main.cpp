#include <iostream>
#include "menu.h"
using namespace std;
using namespace omer;
int main(){
	try {
		startGame();
	}
	catch (exception e) {
		cout << e.what();
	}
	
}