#include "Destroyer.h"

Destroyer::Destroyer(int _row, int _col, bool _direction)
    :Ship(2, "Destroyer", _row, _col, 2, _direction)
{

}

Destroyer::~Destroyer(){

}

void Destroyer::Draw(WINDOW *win){
    Position p = this -> getPosition();
    int row = p.getRow();
    int col = p.getCol();
    bool direction = this -> getDirection();
    wattron(win, COLOR_PAIR(7));
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