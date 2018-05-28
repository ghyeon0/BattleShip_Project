#include "Ship.h"
#include <string>

Position::Position(int _row, int _col){
    row = _row;
    col = _col;
}

Position::~Position(){

}

Position Position::getPosition(){
    return *this;
}

Ship::Ship(int hp, std::string _name, int _row, int _col, int _size, bool _direction){
    remain_HP = 0;
    name = _name;
    position = new Position(_row, _col);
    size = _size;
    direction = _direction;
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

