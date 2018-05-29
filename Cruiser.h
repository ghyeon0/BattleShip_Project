#ifndef _CRUISER_H_
#define _CRUISER_H_

#include "Ship.h"

class Cruiser : public Ship{
    public:
        Cruiser(int _row, int _col, bool _direction);
        ~Cruiser();
};

#endif