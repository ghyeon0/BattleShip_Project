#include "BattleShip.h"
#include <ncurses.h>

BattleShip::BattleShip(int _row, int _col, bool _direction)
    :Ship(4, "Battleship", _row, _col, 4, _direction)
{

}

BattleShip::~BattleShip(){

}

void BattleShip::Draw(WINDOW *win){
    Position p = this -> getPosition();
    int row = p.getRow();
    int col = p.getCol();
    bool direction = this -> getDirection();
    wattron(win, COLOR_PAIR(5));
    if (!direction){
        for(int i = 0;i < this -> getSize();++i){
            mvwprintw(win, i + row + 1, col + 2, "%c", this -> name[0]);
        }
    }else{
        for(int i = 0;i < this -> getSize();++i){
            mvwprintw(win, row + 1, i + col + 2, "%c", this -> name[0]);
        }
    }
    wattroff(win, COLOR_PAIR(4));
    wrefresh(win);
}