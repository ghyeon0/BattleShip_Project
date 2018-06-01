//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "Pane.h"

#define MAP_SIZE 8

class Player : public Pane{
    public:
        Player();
        ~Player();

        void Draw();
        void update(int row, int col, char data);
        std::string attack(int row, int col);
    
    protected:
        char m_mapData[MAP_SIZE][MAP_SIZE];
};

#endif