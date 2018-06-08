#include "BattleShipMap.h"
#include <ncurses.h>

BattleShipMap::BattleShipMap()
    :Pane(4, 4, MAP_SIZE + 3, MAP_SIZE + 2)
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

    mvwprintw(m_pWindow, 0, 2, "DEFENDER");
}

BattleShipMap::~BattleShipMap(){

}

void BattleShipMap::Draw(){
    wattron(m_pWindow, COLOR_PAIR(1));
    for(int i = 0;i < MAP_SIZE;++i){
        for(int j = 0;j < MAP_SIZE;++j){
            if (m_mapData[i][j] == '0')
                mvwprintw(m_pWindow, i + 1, j + 2, "-");
            else{
                mvwprintw(m_pWindow, i + 1, j + 2, "%c", m_mapData[i][j]);
            }
        }
    }
    wattroff(m_pWindow, COLOR_PAIR(1));

    wrefresh(m_pWindow);
}

void BattleShipMap::update(int row, int col, bool direction, int size, char name){
    if (direction){
        for(int i = 0;i < size;i++){
            m_mapData[row][col + i] = name;
        }
    }else{
        for(int i = 0;i < size;i++){
            m_mapData[row + i][col] = name;
        }
    }
}

bool BattleShipMap::isSafe(int a, int b, bool dir, int size){
    if (dir){
        for(int i = 0;i < size;i++){
            if (m_mapData[a][b + i] != '0') return false;
        }
    }else{
        for(int i = 0;i < size;i++){
            if (m_mapData[a + i][b] != '0') return false;
        }
    }
    return true;
}

char BattleShipMap::getData(int row, int col){
    return m_mapData[row][col];
}

std::string BattleShipMap::attack(int row, int col){
    if (m_mapData[row][col] == '0'){
        return "miss";
    }
    else{
        return "hit";
    }
}
