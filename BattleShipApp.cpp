#include "BattleShipApp.h"

#include <ncurses.h>

BattleShipApp::BattleShipApp(){

}

BattleShipApp::~BattleShipApp(){

}

void BattleShipApp::Init(){
    initscr();
    start_color();
    cbreak();
    refresh();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    m_pMap = new BattleShipMap();
    m_pStatPane = new StatPane(30, 3, 30, 6);
    m_pInputPane = new InputPane(30, 15, 30, 4);
}

void BattleShipApp::Play(){
    Init();
    Render();
    Destroy();
}

void BattleShipApp::Render(){
    mvprintw(1, 1, "<< Battle Ship Game >>");

    m_pMap -> Draw();
    m_pStatPane -> Draw();
    m_pInputPane -> Draw();

    refresh();
}

void BattleShipApp::Destroy(){
    getch();
    endwin();
    delete m_pMap;
}