#include <bits/stdc++.h>
#include "IPlayer.hpp"

using namespace std;



struct MyPlayer:  public IPlayer {
    vector<vector<char> > field;
    vector<vector<char> > enemy;
    vector<int> dx = {1, 1, 1, -1, -1, -1, 0, 0, 0};
    vector<int> dy = {1, 0, -1, 1, 0, -1, 1, 0, -1};
    pair<int, int> last_shot = {-1, -1};
    int dk = 9;

    MyPlayer() = default;

    bool check(int x, int y) {
        return x >= 0 && x < 10 && y >= 0 && y < 10;
    }

    bool check_empty(int x, int y) {
        return check(x, y) && field[x][y] == '.' || !check(x, y);
    }

    bool create_ship(int x1, int y1, int x2, int y2){
        if (x2 < x1) swap(x1, x2);
        if (y2 < y1) swap(y1, y2);
        for (int i = x1; i <= x2; i++) {
            for(int j = y1; j <= y2; j++) {
                if (!check(i, j)) return false;
                for (int k = 0; k < dk; k++) {
                    if (!check_empty(i + dx[k], j + dy[k])) {
                        return false;
                    }
                }
            }
        }

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                field[i][j] = 'X';
            }
        }

        return true;
    }

     vector<vector<char> > create() {
        field.resize(10, vector<char>(10, '.'));
        enemy.resize(10, vector<char>(10, '.'));
        int x, y;
        x = (rand() % 8) + 1;
        if (rand() % 2) {
            if (rand() % 2) {
                if (x + 4 > 10) create_ship(x, 0, x - 3, 0);
                else create_ship(x, 0, x + 3, 0);
            } else {
                if (x + 4 > 10) create_ship(x, 9, x - 3, 9);
                else create_ship(x, 9, x + 3, 9);
            }
        } else {
            if (rand() % 2) {
                if (x + 4 > 10) create_ship(0, x, 0, x - 3);
                else create_ship(0, x, 0, x + 3);
            } else {
                if (x + 4 > 10) create_ship(9, x, 9, x - 3);
                else create_ship(9, x, 9, x + 3);
            }
        }

        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 2 + k; i++) {
                bool f = false;
                int x = rand() % 10;
                int y = rand() % 10;
                if (rand() % 2) {
                    if (rand() % 2) {
                        f = create_ship(x, y, x + 2 - k, y);
                    } else {
                        f = create_ship(x, y, x, y + 2 - k);
                    }
                } else {
                    if (rand() % 2) {
                        f = create_ship(x, y, x + 2 - k, y);
                    } else {
                        f = create_ship(x, y, x, y + 2 - k);
                    }
                }
                if (!f) i--;
            }
        }


        return field;
    }

     void kill(int x, int y) {
        int x1 = x, x2 = x, y1 = y, y2 = y;
        while(x1 > 0 && enemy[x1 - 1][y1] == 'P') x1--;
        while(x2 < 9 && enemy[x2 + 1][y1] == 'P') x2++;
        while(y1 > 0 && enemy[x1][y1 - 1] == 'P') y1--;
        while(y2 < 9 && enemy[x1][y2 + 1] == 'P') y2++;

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                for (int k = 0; k < dk; k++) {
                    if (check(i + dx[k], j + dy[k]) && enemy[i + dx[k]][j + dy[k]] == '.') {
                        enemy[i + dx[k]][j + dy[k]] = '*';
                    }
                }
            }
        }
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                enemy[i][j] = 'K';
            }
        }
    }

      void get_shot_res(int res){
        if (res == 0) {
            enemy[last_shot.first][last_shot.second] = '*';
        } else
        if (res == 1) {
            enemy[last_shot.first][last_shot.second] = 'X';
        } else {
            enemy[last_shot.first][last_shot.second] = 'X';
            kill(last_shot.first, last_shot.second);
        }
    }


     pair<int, int> shot(){

        last_shot = {rand() % 10, rand() % 10};
        return last_shot;
    }

     int opponent_shot(pair<int, int> p){
        int x = p.first;
        int y = p.second;
        if (field[x][y] != 'X') {
            return 0;
        }
        field[x][y] = 'P';
        int x1 = x, x2 = x, y1 = y, y2 = y;
        while(x1 > 0 && field[x1 - 1][y1] == 'P') x1--;
        while(x2 < 9 && field[x2 + 1][y1] == 'P') x2++;
        while(y1 > 0 && field[x1][y1 - 1] == 'P') y1--;
        while(y2 < 9 && field[x1][y2 + 1] == 'P') y2++;

        for (int k = 0; k < dk; k++) {
            if (check(x1 + dx[k], y1 + dy[k]) && field[x1 + dx[k]][y1 + dy[k]] == 'X') {
                return 1;
            }
            if (check(x2 + dx[k], y2 + dy[k]) && field[x2 + dx[k]][y2 + dy[k]] == 'X') {
                return 1;
            }
        }

        return 2;

        //0 - �� �����
        //1 - �����
        //2 - ����
    }

     string team_name(){
        return "My Player";
    }

};
