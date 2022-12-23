#ifndef CELL_H
#define CELL_H
class Cell
{
private:
    char type;
    int x, y;

public:
    Cell()
    {
        this->type = '. ';
        this->x = 0;
        this->y = 0;
    }

    char getType()
    {
        return this->type;
    }

    void setType(char c)
    {
        this->type = c;
    }

    int getX()
    {
        return this->x;
    }

    void setX(int n)
    {
        this->x = n;
    }

    int getY()
    {
        return this->y;
    }

    void setY(int n)
    {
        this->y = n;
    }

    string toString()
    {
        return "" + this->type;
    }
};
#endif