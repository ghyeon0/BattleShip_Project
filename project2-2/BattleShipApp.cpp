#include "BattleShipApp.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <vector>
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
    int min = 65;
    int max = 0;
    for(int i = 0;i< 10;i++){
        Init();
        arrangeShips();
        Render();
        gamePlay();
        if (m_pStatPane -> getTurn() < min){
            min = m_pStatPane -> getTurn();
        }
        if (m_pStatPane -> getTurn() > max){
            max = m_pStatPane -> getTurn();
        }
        turn += m_pStatPane -> getTurn();
        usleep(1000000);
        Destroy();
    }
    turn /= 10;
    string temp = to_string(turn);
    m_pInputPane -> Draw();
    m_pInputPane -> Draw(' ', ' ', "Min Turn: " + to_string(min));
    getch();
    m_pInputPane -> Draw();
    m_pInputPane -> Draw(' ', ' ', "Max Turn: " + to_string(max));
    getch();
    m_pInputPane -> Draw();
    m_pInputPane -> Draw(' ', ' ', "Average Turn: " + temp);
    getch();
    endwin();
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
    int check[8][8] = {{0, }};
    while (!isFinished()){
        char row, col;
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
        string b = Attack(row, col);
        usleep(150000);
        if (b == "hit"){
            stack<vector<char> > st;
            vector<char> temp1;
            temp1.push_back(row + 1);
            temp1.push_back(col);
            temp1.push_back('S');
            st.push(temp1);
            vector<char> temp2;
            temp2.push_back(row);
            temp2.push_back(col + 1);
            temp2.push_back('E');
            st.push(temp2);
            vector<char> temp3;
            temp3.push_back(row - 1);
            temp3.push_back(col);
            temp3.push_back('N');
            st.push(temp3);
            vector<char> temp4;
            temp4.push_back(row);
            temp4.push_back(col - 1);
            temp4.push_back('W');
            st.push(temp4);
            int cnt = 0;
            while (!isFinished() && !st.empty()){
                vector<char> vec = st.top();
                st.pop();
                if (vec[0] >= 'A' && vec[0] <= 'H' && vec[1] >= '1' && vec[1] <= '8'){
                    string flag = Attack(vec[0], vec[1]);
                    usleep(150000);
                    check[int(vec[0]) - 65][int(vec[1]) - 49] = 1;
                    if (flag == "hit"){
                        if (vec[2] == 'N'){
                            vector<char> temp;
                            temp.push_back(vec[0] - 1);
                            temp.push_back(vec[1]);
                            temp.push_back('N');
                            st.push(temp);
                        }
                        else if (vec[2] == 'S'){
                            vector<char> temp;
                            temp.push_back(vec[0] + 1);
                            temp.push_back(vec[1]);
                            temp.push_back('S');
                            st.push(temp);
                        }
                        else if (vec[2] == 'W'){
                            vector<char> temp;
                            temp.push_back(vec[0]);
                            temp.push_back(vec[1] - 1);
                            temp.push_back('W');
                            st.push(temp);
                        }else{
                            vector<char> temp;
                            temp.push_back(vec[0]);
                            temp.push_back(vec[1] + 1);
                            temp.push_back('E');
                            st.push(temp);
                        }
                        cnt++;
                    }else if (flag == "destroyed"){
                        cnt = 0;
                        break;
                    }else if (flag == "miss" && cnt > 0){
                        if (vec[2] == 'N'){
                            while (cnt > 0){
                                cnt--;
                                vec[0]++;
                            }
                            vector<char> temp;
                            temp.push_back(vec[0] + 1);
                            temp.push_back(vec[1]);
                            temp.push_back('S');
                            st.push(temp);
                        }else if (vec[2] == 'S'){
                            while (cnt > 0){
                                cnt--;
                                vec[0]--;
                            }
                            vector<char> temp;
                            temp.push_back(vec[0] - 1);
                            temp.push_back(vec[1]);
                            temp.push_back('N');
                            st.push(temp);
                        }else if (vec[2] == 'W'){
                            while (cnt > 0){
                                cnt--;
                                vec[1]++;
                            }
                            vector<char> temp;
                            temp.push_back(vec[0]);
                            temp.push_back(vec[1] + 1);
                            temp.push_back('E');
                            st.push(temp);
                        }
                        else if (vec[2] == 'E'){
                            while (cnt > 0){
                                cnt--;
                                vec[1]--;
                            }
                            vector<char> temp;
                            temp.push_back(vec[0]);
                            temp.push_back(vec[1] - 1);
                            temp.push_back('W');
                            st.push(temp);
                        }
                    }
                }
            }
        }
    }
}

string BattleShipApp::Attack(char row, char col){
    m_pInputPane -> Draw();
    string flag = "miss";
    std::string s = m_pMap -> attack((int)row - 65, (int)col - 49);
    if (s == "hit"){
        std::string p = m_playerMap -> attack((int)row - 65, (int)col - 49);
        if (p == "hit"){
            flag = "hit";
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
                            flag = "destroyed";
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
                            flag = "destroyed";
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
                            flag = "destroyed";
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
                            flag = "destroyed";
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
                            flag = "destroyed";
                        }else{
                            m_pInputPane -> Draw(row, col, s);
                        }
                    }
                    break;
            }
        }else{
            m_pInputPane -> Draw(row, col, "try-again");
            flag = "try-again";
        }
    }
    else{
        if (m_playerMap -> getData(int(row) - 65, int(col) - 49) == 'M'){
            m_pInputPane -> Draw(row, col, "try-again");
            flag = "try-again";
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
    return flag;
}

void BattleShipApp::Destroy(){
    // getch();
    // m_pInputPane -> Draw();
    // m_pInputPane -> Draw('G', 'G', "Good Game!");
    // getch();
    endwin();
    delete m_pMap;
}