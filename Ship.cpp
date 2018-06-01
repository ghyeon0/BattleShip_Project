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
    remain_HP = _size;
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
    return remain_HP <= 0;
}

void Ship::Draw(WINDOW* win){

}

void Ship::attacked(){
    remain_HP -= 1;
}