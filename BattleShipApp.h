#ifndef _BATTLESHIPAPP_H_
#define _BATTLESHIPAPP_H_

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
        StatPane* m_pStatPane;
        InputPane* m_pInputPane;
};

#endif