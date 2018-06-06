#include "BattleShipApp.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>

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
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(7, COLOR_WHITE, COLOR_CYAN);
    init_pair(8, COLOR_RED, COLOR_BLACK);

    m_pMap = new BattleShipMap();
    m_playerMap = new Player();
    m_pStatPane = new StatPane(30, 5, 30, 7);
    m_pInputPane = new InputPane(30, 17, 30, 5);
    
}

void BattleShipApp::arrangeShips(){
    srand((unsigned int)time(NULL));
    //Aircraft
    bool dir = rand() % 2;
    int a = rand() % 4;
    int b = rand() % 8;
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
        a = rand() % 5;
        b = rand() % 8;
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
        a = rand() % 6;
        b = rand() % 8;
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
        a = rand() % 7;
        b = rand() % 8;
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
        a = rand() % 7;
        b = rand() % 8;
        if (dir){
            if (isSafe(b, a, dir, 2)){
                destroyer_two = new Destroyer(b, a, dir);
                m_pMap -> update(b, a, dir, 2, 'E');
                break;
            }
        }else{
            if (isSafe(a, b, dir, 2)){
                destroyer_two = new Destroyer(a, b, dir);
                m_pMap -> update(a, b, dir, 2, 'E');
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
    int turn = 0;
    for(int i = 0;i< 10;i++){
        Init();
        arrangeShips();
        Render();
        gamePlay();
        turn += m_pStatPane -> getTurn();
        usleep(1000000);
        Destroy();
    }
    turn /= 10;
    string temp = to_string(turn);
    m_pInputPane -> Draw();
    m_pInputPane -> Draw(' ', ' ', "Average Turn: " + temp);
    getch();
}

void BattleShipApp::Render(){
    mvprintw(1, 1, "<< Battle Ship Game >>");

    m_pMap -> Draw();
    m_playerMap -> Draw();
    m_pStatPane -> Draw(0, 0, 0, 0);
    m_pInputPane -> Draw();
    
    refresh();
    aircraft -> Draw(m_pMap -> getWindow());
    battleship -> Draw(m_pMap -> getWindow());
    cruiser -> Draw(m_pMap -> getWindow());
    destroyer_one -> Draw(m_pMap -> getWindow());
    destroyer_two -> Draw(m_pMap -> getWindow());
}

bool BattleShipApp::isFinished(){
    return aircraft -> isDestroyed() && battleship -> isDestroyed() && 
    cruiser -> isDestroyed() && destroyer_one -> isDestroyed() && 
    destroyer_two -> isDestroyed();
}


void BattleShipApp::gamePlay(){
    srand((unsigned int)time(NULL));
    bool check[8][8] = {{0, }};
    while (!isFinished()){
        char row, col;
        // usleep(50000);
        while (1){
            int temp = rand() % 8;
            int temp_2 = rand() % 8;
            if (check[temp][temp_2] == 0){
                check[temp][temp_2] = 1;
                row = temp + 65;
                col = temp_2 + 49;
                break;
            }
        }
        m_pInputPane -> Draw();
        m_pInputPane -> Draw(row);
        std::string s = m_pMap -> attack((int)row - 65, (int)col - 49);
        if (s == "hit"){
            std::string p = m_playerMap -> attack((int)row - 65, (int)col - 49);
            if (p == "hit"){
                char c = m_pMap -> getData((int)row - 65, (int)col - 49);
                char temp;
                switch (c){
                    case 'A':
                        if (!aircraft-> isDestroyed()){
                            aircraft -> attacked();
                            m_pStatPane -> turnPass();
                            m_playerMap -> update((int)row - 65, (int)col - 49, 'H');
                            if (aircraft -> isDestroyed()){
                                aircraft -> Draw(m_playerMap -> getWindow());
                                m_pInputPane -> Draw(row, col, "Aircraft Destroyed");
                            }else{
                                m_pInputPane -> Draw(row, col, s);
                            }
                        }
                        break;
                    case 'B':
                        if (!battleship -> isDestroyed()){
                            battleship -> attacked();
                            m_pStatPane -> turnPass();
                            m_playerMap -> update((int)row - 65, (int)col - 49, 'H');
                            if (battleship -> isDestroyed()){
                                battleship -> Draw(m_playerMap -> getWindow());
                                m_pInputPane -> Draw(row, col, "BattleShip Destroyed");
                            }else{
                                m_pInputPane -> Draw(row, col, s);
                            }
                        }
                        break;
                    case 'C':
                        if (!cruiser -> isDestroyed()){
                            cruiser -> attacked();
                            m_pStatPane -> turnPass();
                            m_playerMap -> update((int)row - 65, (int)col - 49, 'H');
                            if (cruiser -> isDestroyed()){
                                cruiser -> Draw(m_playerMap -> getWindow());
                                m_pInputPane -> Draw(row, col, "Cruiser Destroyed");
                            }else{
                                m_pInputPane -> Draw(row, col, s);
                            }
                        }
                        break;
                    case 'D':
                        if (!destroyer_one -> isDestroyed()){
                            destroyer_one -> attacked();
                            m_pStatPane -> turnPass();
                            m_playerMap -> update((int)row - 65, (int)col - 49, 'H');
                            if (destroyer_one -> isDestroyed()){
                                destroyer_one -> Draw(m_playerMap -> getWindow());
                                m_pInputPane -> Draw(row, col, "Destroyer Destroyed");
                            }else{
                                m_pInputPane -> Draw(row, col, s);
                            }
                        }
                        break;
                    case 'E':
                        if (!destroyer_two -> isDestroyed()){
                            destroyer_two -> attacked();
                            m_pStatPane -> turnPass();
                            m_playerMap -> update((int)row - 65, (int)col - 49, 'H');
                            if (destroyer_two -> isDestroyed()){
                                destroyer_two -> Draw(m_playerMap -> getWindow());
                                m_pInputPane -> Draw(row, col, "Destroyer Destroyed");
                            }else{
                                m_pInputPane -> Draw(row, col, s);
                            }
                        }
                        break;
                }
            }else{
                m_pInputPane -> Draw(row, col, "try-again");
                m_pStatPane -> turnPass();
            }
        }
        else{
            if (m_playerMap -> getData(int(row) - 65, int(col) - 49) == 'M'){
                m_pInputPane -> Draw(row, col, "try-again");
                m_pStatPane -> turnPass();
            }else{
                m_pStatPane -> turnPass();
                m_playerMap -> update((int)row - 65, (int)col - 49, 'M');
                m_pInputPane -> Draw(row, col, s);
            }
        }
        if (aircraft -> isDestroyed()){
            aircraft -> Draw(m_playerMap -> getWindow());
        }
        if (battleship -> isDestroyed()){
            battleship -> Draw(m_playerMap -> getWindow());
        }
        if (cruiser -> isDestroyed()){
            cruiser -> Draw(m_playerMap -> getWindow());
        }
        if (destroyer_one -> isDestroyed()){
            destroyer_one -> Draw(m_playerMap -> getWindow());
        }
        if (destroyer_two -> isDestroyed()){
            destroyer_two -> Draw(m_playerMap -> getWindow());
        }
        m_pStatPane -> Draw(aircraft -> isDestroyed(), battleship -> isDestroyed(), 
        cruiser -> isDestroyed(), destroyer_one -> isDestroyed() && destroyer_two -> isDestroyed());
    }
}

void BattleShipApp::Destroy(){
    // getch();
    // m_pInputPane -> Draw();
    // m_pInputPane -> Draw('G', 'G', "Good Game!");
    // getch();
    endwin();
    delete m_pMap;
}