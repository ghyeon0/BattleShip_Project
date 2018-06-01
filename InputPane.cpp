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

void InputPane::Clear(){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A3)");
    mvwprintw(m_pWindow, 2, 2, "Input : ");
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}

void InputPane::Draw(){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A3)");
    mvwprintw(m_pWindow, 2, 2, "Input : ");
    for(int i = 0;i < 20;i++){
        mvwprintw(m_pWindow, 3, 2 + i, " ");
    }
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}

void InputPane::Draw(char a){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A3)");
    mvwprintw(m_pWindow, 2, 2, "Input : %c", a);
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}

void InputPane::Draw(char a, char b, std::string data){
    wattron(m_pWindow, COLOR_PAIR(3));
    mvwprintw(m_pWindow, 1, 2, "Input position...(ex: A3)");
    mvwprintw(m_pWindow, 2, 2, "Input : %c%c", a, b);
    for(int i = 0;i < data.length();i++){
        mvwprintw(m_pWindow, 3, 2 + i, "%c", data[i]);
    }
    wattroff(m_pWindow, COLOR_PAIR(3));
    wrefresh(m_pWindow);
}


