#include "BattleShip.h"

BattleShip::BattleShip(int _row, int _col, bool _direction)
    :Ship(4, "Battleship", _row, _col, 4, _direction)
{

}

BattleShip::~BattleShip(){

}