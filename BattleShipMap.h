//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _BATTLESHIPMAP_H_
#define _BATTLESHIPMAP_H_

#include "Pane.h"

#define MAP_SIZE 8

class BattleShipMap : public Pane{
    public:
        BattleShipMap();
        ~BattleShipMap();

        void Draw();
    
    protected:
        char m_mapData[MAP_SIZE][MAP_SIZE];
};

#endif