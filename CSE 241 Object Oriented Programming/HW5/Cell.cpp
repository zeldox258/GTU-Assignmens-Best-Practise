#include "Cell.h"
namespace omer {
    Cell::Cell(int x, int y, char value) {
        this->x = x;
        this->y = y;
        this->val = value;
    }

    int Cell::getX() const {
        return x;
    }

    int Cell::getY() const {
        return y;
    }

    char Cell::getVal() const {
        return val;
    }

    void Cell::setX(const int& x) {
        this->x = x;
    }

    void Cell::setY(const int& y) {
        this->y = y;
    }

    void Cell::setVal(const char& value) {
        this->val = value;
    }
}