#ifndef _BATTLESHIP_H_
#define _BATTLESHIP_H_

#include "Ship.h"

class BattleShip : public Ship{
    public:
        BattleShip(int _row, int _col, bool _direction);
        ~BattleShip();
};

#endif