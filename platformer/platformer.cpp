#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
struct Position {
    float x;
    float y;
};
struct Player {
    Position position;
    int health;
    int ammo;
    int score;
};
struct Enemy {
    Position position;
    int health;
    char type;
    int scoreForKill;
};
struct Platform {
    Position position;
};
struct Item {
    Position position;
    char type;
};
struct Level {
    Player player;
    std::vector <Enemy> enemies;
    std::vector <Platform> platforms;
    std::vector <Item> items;
};

int main()
{
    std::cout << "Hello World!\n";
}


