//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _BATTLESHIPMAP_H_
#define _BATTLESHIPMAP_H_

#include "Pane.h"
#include <string>

#define MAP_SIZE 8

class BattleShipMap : public Pane{
    public:
        BattleShipMap();
        ~BattleShipMap();
        void update(int row, int col, bool direction, int size, char name);
        void Draw();
        bool isSafe(int a, int b, bool direction, int size);
        std::string attack(int col, int row);
        char getData(int col, int row);
    
    protected:
        char m_mapData[MAP_SIZE][MAP_SIZE];
};

#endif