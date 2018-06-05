#include "InputPane.h"
#include <ncurses.h>
#include <string>

InputPane::InputPane(int x, int y, int width, int height)
    :Pane(x, y, width, height)
{
    mvwprintw(m_pWindow, 0, 3, "< INPUT >");
}

InputPane::~InputPane(){

}

void InputPane::Draw(){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A 3)");
    mvwprintw(m_pWindow, 2, 2, "Input :                   ");
    for(int i = 0;i < 25;i++){
        mvwprintw(m_pWindow, 3, 2 + i, " ");
    }
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}

void InputPane::Draw(char a){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A 3)");
    mvwprintw(m_pWindow, 2, 2, "Input : %c", a);
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}

void InputPane::Draw(char a, char b, std::string data){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A 3)");
    mvwprintw(m_pWindow, 2, 2, "Input : %c %c", a, b);
    mvwprintw(m_pWindow, 3, 2, "%c", a);
    mvwprintw(m_pWindow, 3, 4, "%c", b);
    for(int i = 0;i < data.length();i++){
        mvwprintw(m_pWindow, 3, 6 + i, "%c", data[i]);
    }
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}


