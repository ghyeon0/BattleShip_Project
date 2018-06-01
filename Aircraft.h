#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_

#include "Ship.h"

class Aircraft : public Ship{
    public:
        Aircraft(int _row, int _col, bool _direction);
        ~Aircraft();
        void Draw(WINDOW* win);
};

#endif