#include "Ship.h"
#include <string>
#include <ncurses.h>
#include "BattleShipMap.h"

Position::Position(int _row, int _col){
    row = _row;
    col = _col;
}

Position::~Position(){

}

Position Position::getPosition(){
    return *this;
}

int Position::getRow(){
    return row;
}

int Position::getCol(){
    return col;
}

Ship::Ship(int hp, std::string _name, int _row, int _col, int _size, bool _direction){
    remain_HP = 0;
    name = _name;
    position = new Position(_row, _col);
    size = _size;
    direction = _direction;
}

Ship::~Ship(){

}

std::string Ship::getName(){
    return name;
}

Position Ship::getPosition(){
    return position -> getPosition();
}

int Ship::getRemainHP(){
    return remain_HP;
}

int Ship::getSize(){
    return size;
}

bool Ship::getDirection(){
    return direction;
}

void Ship::setPosition(int _row, int _col){
    delete position;
    position = new Position(_row, _col);
}

bool Ship::isDestroyed(){
    return remain_HP == 0;
}

void Ship::Draw(WINDOW* win){
    Position p = this -> getPosition();
    int row = p.getRow();
    int col = p.getCol();
    bool direction = this -> getDirection();
    wattron(win, COLOR_PAIR(4));
    if (!direction){
        for(int i = 0;i < this -> getSize();++i){
            mvwprintw(win, i + row + 1, col + 2, "%c", this -> name[0]);
        }
    }else{
        for(int i = 0;i < this -> getSize();++i){
            mvwprintw(win, row + 1, i + col, "%c", this -> name[0]);
        }
    }
    wattroff(win, COLOR_PAIR(4));
}