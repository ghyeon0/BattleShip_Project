#include "Player.h"
#include <ncurses.h>

Player::Player()
    :Pane(4, 16, MAP_SIZE + 3, MAP_SIZE + 2)
{
    for(int i = 0;i < MAP_SIZE;i++){
        for(int j = 0;j < MAP_SIZE;++j){
            m_mapData[i][j] = '0';
        }
    }

    for(int i = 0;i < MAP_SIZE;++i){
        mvprintw(i + 1 + m_y, m_x - 1, "%c", 'A' + i);
        mvprintw(m_y + m_height, m_x + 2 + i, "%d", 1 + i);
    }

    mvwprintw(m_pWindow, 0, 2, "ATTACKER");
}

Player::~Player(){

}

void Player::Draw(){
    wattron(m_pWindow, COLOR_PAIR(1));
    for(int i = 0;i < MAP_SIZE;++i){
        for(int j = 0;j < MAP_SIZE;++j){
            mvwprintw(m_pWindow, i + 1, j + 2, "-");
        }
    }
    wattroff(m_pWindow, COLOR_PAIR(1));

    wrefresh(m_pWindow);
}