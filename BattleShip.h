//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/29

#ifndef _BATTLESHIP_H_
#define _BATTLESHIP_H_

#include "Ship.h"

class BattleShip : public Ship{
    public:
        BattleShip(int _row, int _col, bool _direction);
        ~BattleShip();
        void Draw(WINDOW *win);
};

#endif