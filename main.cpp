// Основной файл и движок игры
#include <bits/stdc++.h>
#include "Game.hpp"
#include "PlayerRandom.hpp"
#include "MyPlayer.hpp"

int main() {
    MyPlayer p1;        // Твой игрок
    PlayerRandom p2;    // Рандомно стреляющий игрок
    Game game;          // Создание игровой сессии
    game.game(p1, p2);  // Запуск игры
}
