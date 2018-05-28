#ifndef _SHIP_H_
#define _SHIP_H_

#include <string>

class Position{
    private:
        int row;
        int col;
    public:
        Position(int _row, int _col);
        ~Position();
        Position getPosition();
};

class Ship{
    private:
        int remain_HP;
        std::string name;
        Position *position;
        int size;
        bool direction;
    public:
        Ship(int hp, std::string _name, int _row, int _col, int _size, bool _direction);
        ~Ship();
        std::string getName();
        Position getPosition();
        int getRemainHP();
        int getSize();
        bool getDirection();
        void setPosition(int row, int col);
};

#endif