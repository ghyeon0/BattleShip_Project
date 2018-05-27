//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _BATTLESHIPAPP_H_
#define _BATTLESHIPAPP_H_

#include "Player.h"
#include "BattleShipMap.h"
#include "StatPane.h"
#include "InputPane.h"

class BattleShipApp{
    public:
        BattleShipApp();
        ~BattleShipApp();

        void Play();

    protected:
        void Init();
        void Render();
        void Destroy();

    protected:
        BattleShipMap* m_pMap;
        Player* m_playerMap;
        StatPane* m_pStatPane;
        InputPane* m_pInputPane;
};

#endif