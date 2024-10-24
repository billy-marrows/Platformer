#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include<locale.h>
class Position {
private:
    double x;
    double y;
public:
    Position() {};
    Position(double x, double y) {
        this->x = x;
        this->y = y;
    }
    void addX(double a) {
        this->x += a;
    }
    void addY(double a) {
        this->y += a;
    }
    double getY() {
        return this->y;
    }
    double getX() {
        return this->x;
    }
    void setPos(double x, double y) {
        this->x = x;
        this->y = y;
    }
};
class Player {
private:
    Position position;
    int health;
    int ammo;
public:
    Player(double x, double y, int health, int ammo) {
        this->position = Position(x, y);
        this->health = health;
        this->ammo = ammo;
    }
    Player();
    void puthere(double x, double y) {
        this->position.setPos(x, y);
    }
    int getHealth() {
        return health;
    }
    int getAmmo() {
        return ammo;
    }
    void movePlayer(int b) {
        switch (b) {
        case(230):
            this->position.addY(1);
            break;
        case(228):
            this->position.addX(-1);
            break;
        case(235):
            this->position.addY(-1);
            break;
        case(162):
            this->position.addX(1);
            break;
        }
    }
    void outPlayer() {
        printf("Информация об игроке: ");
        printf("%1.2f %1.2f ", this->position.getX(),this->position.getY());
        printf("%1d ", this->getHealth());
        printf("%3d\n", this->getAmmo());
    }
    void touchEnemy() {
        printf("Игрок получил урон!\n");
        this->health--;
    }
    void getHealed(int d) {
        this->health+=d;
    }
    void addAmmo(int d) {
        this->ammo += d;
    }
};
class Enemy {
private:
    Position position;
    int health;
    int type;
public:
    Enemy(double x, double y, int health, int type) {
        this->position.setPos(x, y);
        this->health = health;
        this->type = type;
    }
    void outEnemy() {
            printf("Информация о враге:\n");
            printf("%1.2f %1.2f ", this->position.getX(),this->position.getY());
            printf("%1d", this->health);
            printf("%1d\n", this->type);
    }
    int getType() {
        return this->type;
    }
};

class Platform {
private:
    Position position;
public:
    Platform(double x, double y) {
        this->position.setPos(x, y);
    }
    void outPlatform() {
        printf("Позиция платформы: %1.2f %1.2f\n", this->position.getX(), this->position.getY());
    }
    double getPlatformX() {
        return this->position.getX();
    }
    double getPlatformY() {
        return this->position.getY();
    }
};

class Item {
private:
    Position position;
    int type;
public:
    Item(double x, double y, int type) {
        this->position.setPos(x, y);
        this->type = type;
    }
    int getType() {
        return this->type;
    }
    void outItem() {
        printf("Информация о предмете:\n");
        printf("Позиция предмета: %1.2lf %1.2lf\n", this->position.getX(), this->position.getY());
        printf("Тип: %d\n", this->getType());
    }
};

class Level {
private:
    Player player;
    std::vector <Enemy> enemies;
    std::vector <Platform> platforms;
    std::vector <Item> items;
    bool win;
public:
    Level(Player& player, const std::vector<Enemy>& enemies, const std::vector<Platform>& platforms, const std::vector<Item>& items) {
        this->player = player;
        this->enemies = enemies;
        this->platforms = platforms;
        this->items = items;
        this->win = false;
    };
    void addPlatform(Platform platform) {
        this->platforms.push_back(platform);
    }
    void addItem(Item item) {
        this->items.push_back(item);
    }
    void addEnemy(Enemy enemy) {
        this->enemies.push_back(enemy);
    }
    void outLevel() {
        printf("Информация об уровне:\n");
        this->player.outPlayer();
        for (Enemy enemy : this->enemies) {
            enemy.outEnemy();
        }
        for (Platform platform : this->platforms) {
            platform.outPlatform();
        }
        for (Item item : this->items) {
            item.outItem();
        }
        if (this->win == true) {
            printf("Уровень пройден.\n");
        }
        else printf("Уровень не пройден.\n");
    }

    void pickupItem(Item &item) {
        printf("Подобран предмет!\n");
        switch (item.getType()) {
        case(0):
            this->player.getHealed(1);
            break;
        case(1):
            this->player.addAmmo(50);
            break;
        case(2):
            this->win = true;
            break;
        }
    }
};


Item writeItem() {
    double x, y;
    int type;
    printf("Введите позицию предмета: ");
    while (scanf("%lf %lf", &x, &y) != 2) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    printf("Введите тип предмета: ");
    while (scanf("%d", &type) != 1) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    return initItem(x, y, type);
}

int main() {
    setlocale(LC_ALL, "RUS");

    //тест функций инициализации и "статических" переменных
    Player player = initPlayer(0, 0, 3, 50);
    Enemy enemy = initEnemy(1.0, 1.0, 0);
    Platform platform = initPlatform(2.0, 2.0);
    Item item = initItem(3.0, 3.0, 1);
    std::vector<Enemy> enemies = { enemy };
    std::vector<Platform> platforms = { platform };
    std::vector<Item> items = { item };
    Level level = initLevel(player, enemies, platforms, items);
    outLevel(level);

    //работа с динамическим массивом переменных и ввод с консоли
    Item* itemsDyna;
    itemsDyna = (Item*)malloc(3 * sizeof(Item));
    for (int i = 0; i < 3; i++) {
        *(itemsDyna + i) = writeItem();
    }

    //функции вывода и бизнес-логика
    int b = 0;
    while (b != 27) {
        b = _getch();
        movePlayer(level.player, b);
        outPlayer(level.player);
    }
    for (int i = 0; i < 3; i++) {
        addItem(level, *(itemsDyna + i));
    }
    touchEnemy(level.player, level.enemies[0]);
    pickupItem(level, level.player, level.items[0]);
    outPlayer(level.player);
    addPlatform(level,initPlatform(1.5,1.5));
    addEnemy(level,initEnemy(1,1,3));
    outLevel(level);
    return 0;
}

