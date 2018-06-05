//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/29

#ifndef _CRUISER_H_
#define _CRUISER_H_

#include "Ship.h"

class Cruiser : public Ship{
    public:
        Cruiser(int _row, int _col, bool _direction);
        ~Cruiser();
        void Draw(WINDOW *win);
};

#endif