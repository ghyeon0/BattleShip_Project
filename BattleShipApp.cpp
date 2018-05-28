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
    noecho();
    curs_set(0);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    m_pMap = new BattleShipMap();
    m_playerMap = new Player();
    m_pStatPane = new StatPane(30, 3, 30, 7);
    m_pInputPane = new InputPane(30, 15, 30, 4);
}

void BattleShipApp::Play(){
    Init();
    Render();
    gamePlay();
    Destroy();
}

void BattleShipApp::Render(){
    mvprintw(1, 1, "<< Battle Ship Game >>");

    m_pMap -> Draw();
    m_playerMap -> Draw();
    m_pStatPane -> Draw();
    

    refresh();
    m_pInputPane -> Draw();
}

bool BattleShipApp::isFinished(){
    return false;
}


void BattleShipApp::gamePlay(){
    while (!isFinished()){
        char col = getch();
        if ((int)col >= 65 && (int)col <= 72){
            m_pInputPane -> Clear();
            m_pInputPane -> Draw();
            m_pInputPane -> Draw(col);
            char row = getch();
            if (int(row) >= 49 && (int)row <= 56){
                m_pInputPane -> Draw(col, row);
                m_pStatPane -> turnPass();
            }else{
                while (1){
                    char temp = getch();
                    if (int(temp) >= 49 && (int)temp <= 56){
                        row = temp;
                        break;
                    }
                }
                m_pStatPane -> turnPass();
                m_pInputPane -> Draw(col, row);
            }
        }
    }
}

void BattleShipApp::Destroy(){
    getch();
    endwin();
    delete m_pMap;
}