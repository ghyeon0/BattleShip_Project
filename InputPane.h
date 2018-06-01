//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _INPUTPANE_H_
#define _INPUTPANE_H_

#include <string>
#include "Pane.h"

class InputPane : public Pane{
    public:
        InputPane(int x, int y, int width, int height);
        ~InputPane();

        virtual void Draw();
        virtual void Draw(char a);
        virtual void Draw(char a, char b, std::string data);
        virtual void Clear();
};

#endif