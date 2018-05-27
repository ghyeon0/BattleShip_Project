#include "InputPane.h"
#include <ncurses.h>

InputPane::InputPane(int x, int y, int width, int height)
    :Pane(x, y, width, height)
{
    mvwprintw(m_pWindow, 0, 3, "< INPUT >");
}

InputPane::~InputPane(){

}

void InputPane::Draw(){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A 3");
    mvwprintw(m_pWindow, 2, 2, "Input : ");
    wattroff(m_pWindow, COLOR_PAIR(3));

    wrefresh(m_pWindow);
}