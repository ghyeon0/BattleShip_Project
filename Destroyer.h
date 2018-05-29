#ifndef _DESTROYER_H
#define _DESTROYER_H

#include "Ship.h"

class Destroyer : public Ship{
    public:
        Destroyer(int _row, int _col, bool _direction);
        ~Destroyer();
};

#endif