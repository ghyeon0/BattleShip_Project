#include "StatPane.h"
#include <ncurses.h>

StatPane::StatPane(int x, int y, int width, int height)
    :Pane(x, y, width, height)
{
    mvwprintw(m_pWindow, 0, 3, "< STATUS >");
    turn = 1;
}

StatPane::~StatPane(){

}

void StatPane::Draw(bool aircraft = 0, bool battleship = 0, bool cruiser = 0, bool destroyer = 0){
    wattron(m_pWindow, COLOR_PAIR(2));
    mvwprintw(m_pWindow, 1, 2, "TURN : %d", turn);
    if (aircraft){
        wattroff(m_pWindow, COLOR_PAIR(2));
        wattron(m_pWindow, COLOR_PAIR(8));
        mvwprintw(m_pWindow, 2, 2, "AIRCRAFT : AAAAA");
        wattroff(m_pWindow, COLOR_PAIR(8));
        wattron(m_pWindow, COLOR_PAIR(2));
    }else{
        mvwprintw(m_pWindow, 2, 2, "AIRCRAFT : AAAAA");
    }
    if (battleship){
        wattroff(m_pWindow, COLOR_PAIR(2));
        wattron(m_pWindow, COLOR_PAIR(8));
        mvwprintw(m_pWindow, 3, 2, "BATTLESHIP : BBBB");
        wattroff(m_pWindow, COLOR_PAIR(8));
        wattron(m_pWindow, COLOR_PAIR(2));
    }else{
        mvwprintw(m_pWindow, 3, 2, "BATTLESHIP : BBBB");
    }
    if (cruiser){
        wattroff(m_pWindow, COLOR_PAIR(2));
        wattron(m_pWindow, COLOR_PAIR(8));
        mvwprintw(m_pWindow, 4, 2, "CRUISER : CCC");
        wattroff(m_pWindow, COLOR_PAIR(8));
        wattron(m_pWindow, COLOR_PAIR(2));
    }else{
        mvwprintw(m_pWindow, 4, 2, "CRUISER : CCC");
    }
    if (destroyer){
        wattroff(m_pWindow, COLOR_PAIR(2));
        wattron(m_pWindow, COLOR_PAIR(8));
        mvwprintw(m_pWindow, 5, 2, "DESTROYER : DD DD");
        wattroff(m_pWindow, COLOR_PAIR(8));
        wattron(m_pWindow, COLOR_PAIR(2));
    }else{
        mvwprintw(m_pWindow, 5, 2, "DESTROYER : DD DD");
    }
    wattroff(m_pWindow, COLOR_PAIR(2));

    wrefresh(m_pWindow);
}

void StatPane::turnPass(){
    turn++;
}