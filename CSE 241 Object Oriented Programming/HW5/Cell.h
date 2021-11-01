#pragma once
namespace omer {
	class Cell {
	public:
		Cell(int x, int y, char value);

		int getX()const;//return x cord
		int getY()const;//return y cor
		char getVal()const;//return val of cell
		void setX(const int& x);//set x cord
		void setY(const int& y);//set y cord
		void setVal(const char& value);//set val of cell

	private:
		int x;
		int y;
		char val;
	};
}
