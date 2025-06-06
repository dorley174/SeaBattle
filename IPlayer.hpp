#include <bits/stdc++.h>
#ifndef IPLAYER_HPP_
#define IPLAYER_HPP_

using namespace std;

// Интерфейс для MyPlayer и RandomPlayer: их будущие методы и функции
struct IPlayer {
    virtual vector<vector<char> > create() {};
    virtual pair<int, int> shot() {};
    virtual int opponent_shot(pair<int, int> p) {};
    virtual void get_shot_res(int res) {};
    virtual string team_name() {};
};

#endif
