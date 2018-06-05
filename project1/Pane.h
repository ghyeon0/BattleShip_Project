//C++ BattleShip Project
//20171701 정지현
//작성일자 2018/05/27

#ifndef _PANE_H_
#define _PANE_H_

#include <ncurses.h>

class Pane{
    public:
        Pane(int x, int y, int width, int height);
        virtual ~Pane();

        virtual void Draw();

        WINDOW* getWindow();
    
    protected:
        int m_width, m_height;
        int m_x, m_y;
        WINDOW* m_pWindow;
};

#endif