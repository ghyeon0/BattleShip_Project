#include "BattleShipApp.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    init_pair(4, COLOR_WHITE, COLOR_RED);

    m_pMap = new BattleShipMap();
    m_playerMap = new Player();
    m_pStatPane = new StatPane(30, 5, 30, 7);
    m_pInputPane = new InputPane(30, 17, 30, 4);
    
}

void BattleShipApp::arrangeShips(){
    srand((unsigned int)time(NULL));
    //Aircraft
    bool dir = rand() % 2;
    int a = rand() % 4;
    int b = rand() % 7;
    if (dir){
        aircraft = new Aircraft(b, a, dir);
        m_pMap -> update(b, a, dir, 5, 'A');
    }else{
        aircraft = new Aircraft(a, b, dir);
        m_pMap -> update(a, b, dir, 5, 'A');
    }
    //Battleship
    while (1){
        dir = rand() % 2;
        a = rand() % 4;
        b = rand() % 7;
        if (dir){
            if (isSafe(b, a, dir, 4)){
                battleship = new BattleShip(b, a, dir);
                m_pMap -> update(b, a, dir, 4, 'B');
                break;
            }
        }else{
            if (isSafe(a, b, dir, 4)){
                battleship = new BattleShip(a, b, dir);
                m_pMap -> update(a, b, dir, 4, 'B');
                break;
            }
        }
    }
    //Cruiser
    while (1){
        dir = rand() % 2;
        a = rand() % 4;
        b = rand() % 7;
        if (dir){
            if (isSafe(b, a, dir, 3)){
                cruiser = new Cruiser(b, a, dir);
                m_pMap -> update(b, a, dir, 3, 'C');
                break;
            }
        }else{
            if (isSafe(a, b, dir, 3)){
                cruiser = new Cruiser(a, b, dir);
                m_pMap -> update(a, b, dir, 3, 'C');
                break;
            }
        }
    }
    //Destroyer_one
    while (1){
        dir = rand() % 2;
        a = rand() % 4;
        b = rand() % 7;
        if (dir){
            if (isSafe(b, a, dir, 2)){
                destroyer_one = new Destroyer(b, a, dir);
                m_pMap -> update(b, a, dir, 2, 'D');
                break;
            }
        }else{
            if (isSafe(a, b, dir, 2)){
                destroyer_one = new Destroyer(a, b, dir);
                m_pMap -> update(a, b, dir, 2, 'D');
                break;
            }
        }
    }
    //Destroyer_two
    while (1){
        dir = rand() % 2;
        a = rand() % 4;
        b = rand() % 7;
        if (dir){
            if (isSafe(b, a, dir, 2)){
                destroyer_two = new Destroyer(b, a, dir);
                m_pMap -> update(b, a, dir, 2, 'D');
                break;
            }
        }else{
            if (isSafe(a, b, dir, 2)){
                destroyer_two = new Destroyer(a, b, dir);
                m_pMap -> update(a, b, dir, 2, 'D');
                break;
            }
        }
    }
}

bool BattleShipApp::isSafe(int x, int y, bool direction, int size){
    if (m_pMap -> isSafe(x, y, direction, size)) return true;
    else return false;
}

void BattleShipApp::Play(){
    Init();
    arrangeShips();
    Render();
    gamePlay();
    Destroy();
}

void BattleShipApp::Render(){
    mvprintw(1, 1, "<< Battle Ship Game >>");

    m_pMap -> Draw();
    m_playerMap -> Draw();
    m_pStatPane -> Draw();
    m_pInputPane -> Draw();
    
    refresh();
    aircraft -> Draw(m_pMap -> getWindow());
    battleship -> Draw(m_pMap -> getWindow());
    cruiser -> Draw(m_pMap -> getWindow());
    destroyer_one -> Draw(m_pMap -> getWindow());
    destroyer_two -> Draw(m_pMap -> getWindow());
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