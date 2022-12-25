#ifndef CELL_H
#define CELL_H
#include <string>
class Cell
{
private:
    char type;
    int x, y;

public:
    Cell();
    /*{
        this->type = '. ';
        this->x = 0;
        this->y = 0;
    }*/

    char getType();

    void setType(char c);

    int getX();

    void setX(int n);

    int getY();

    void setY(int n);

    string toString();
};
#endif