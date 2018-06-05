//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/29

#ifndef _DESTROYER_H
#define _DESTROYER_H

#include "Ship.h"

class Destroyer : public Ship{
    public:
        Destroyer(int _row, int _col, bool _direction);
        ~Destroyer();
        void Draw(WINDOW *win);
};

#endif