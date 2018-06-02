//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _STATPANE_H_
#define _STATPANE_H_

#include "Pane.h"

class StatPane : public Pane{
    public:
        StatPane(int x, int y, int width, int height);
        ~StatPane();

        void Draw(bool aircraft, bool battleship, bool cruiser, bool destroyer);
        void turnPass();
    protected:
        int turn;
};

#endif