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
    double getX() {
        return this->x;
    }
    double getY() {
        return this->y;
    }
    void move(double x, double y) {
        this->x += x;
        this->y += y;
    }
    void setpos(double x, double y) {
        this->x = x;
        this->y = y;
    }
    void outpos() {
        printf("Позиция: %1.2lf %1.2lf  ", this->x, this->y);
    }
};
class Player {
private:
    Position position;
    int health;
    int ammo;
public:
    Player() {};
    Player(double x, double y, int health, int ammo) {
        Position position(x, y);
        this->position = position;
        this->health = health;
        this->ammo = ammo;
    }
    Player(Position position, int health, int ammo) {
        this->position = position;
        this->health = health;
        this->ammo = ammo;
    }

    int getHealth() {
        if (this->health < 1) printf("Игрок погиб!\n");
        return this->health;
    }
    int getAmmo() {
        if (this->ammo < 1) printf("Патроны игрока кончились!\n");
        return this->ammo;
    }
    void outPlayer() {
        printf("Информация об игроке:   ");
        this->position.outpos();
        printf("Здоровье: %d  ", this->health);
        printf("Патроны:%d\n", this->ammo);
    }
    void addAmmo(int d) {
        this->ammo += d;
    }
    void addHealth(int d) {
        this->health += d;
    }
    Position getPos() {
        return this->position;
    }
    void movePlayer(int b)   {//230 228 235 162
        switch (b) {
        case(230):
            this->position.move(0, 1);
            break;
        case(228):
            this->position.move(-1, 0);
            break;
        case(235):
            this->position.move(0, -1);
            break;
        case(162):
            this->position.move(1, 0);
            break;
        }
        printf("Позиция игрока: %1.1lf %1.1lf\n", this->getPos().getX(), this->getPos().getY());
    }
};
class Enemy {
private:
    Position position;
    int health;
    char type;
public:
    Enemy();
    Enemy(double x, double y, int health, int type) {
        Position position(x, y);
        this->position = position;
        this->health = health;
        this->type = type;
    }
    Enemy(Position position, int health, int type) {
        this->position = position;
        this->health = health;
        this->type = type;
    }
    void outEnemy() {
        printf("Информация о враге:  ");
        this->position.outpos();
        printf("Здоровье: %d  ", this->health);
        printf("Тип:%d\n", this->type);
    }
    void takeDamage() {
        printf("Ой! ");
        this->health--;
        if (this->health == 0) printf("Я погиб!\n");
    }
    int getHealth() {
        return this->health;
    }
    double getX() {
        return this->position.getX();
    }
    double getY() {
        return this->position.getY();
    }
};
class Platform {
private:
    Position position;
public:
    Platform();
    Platform(double x, double y) {
        Position position(x, y);
        this->position = position;
    }
    Platform(Position position) {
        this->position = position;
    }
    void outPlatform() {
        printf("Информация о платформе: ");
        this->position.outpos();
        printf("\n");
    }
};
class Item {
private:
    Position position;
    int type;
public:
    Item() {};
    Item(double x, double y, int type) {
        Position position(x, y);
        this->position = position;
        this->type = type;
    }
    Item(Position position, int type) {
        this->position = position;
        this->type = type;
    }
    int getType() {
        return this->type;
    }
    void outItem() {
        printf("Информация о предмете:");
        this->position.outpos();
        printf("Тип: %d\n", this->type);
    }
    void writeItem() {
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
        this->position.setpos(x, y);
        this->type = type;
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
    Level();
    Level(Player player, const std::vector<Enemy> enemies, const std::vector<Platform> platforms, const std::vector<Item> items) {
        this->player = player;
        this->enemies = enemies;
        this->platforms = platforms;
        this->items = items;
        this->win = false;
    }
    void outLevel() {
        printf("Информация об уровне:\n  ");
        this->player.outPlayer();
        for (Enemy enemy : this->enemies) {
            printf("  ");
            enemy.outEnemy();
        }
        for (Platform platform : this->platforms) {
            printf("  ");
            platform.outPlatform();
        }
        for (Item item : this->items) {
            printf("  ");
            item.outItem();
        }
        if (this->win == true) {
            printf("  Уровень пройден.\n\n");
        }
        else printf("  Уровень не пройден.\n\n");
    }
    void pickupItem(Item item) {
        printf("Подобран предмет ");
        switch (item.getType()) {
        case(0):
            printf("на здоровье.\n");
            this->player.addHealth(1);
            break;
        case(1):
            printf("на патроны.\n");
            this->player.addAmmo(50);
            break;
        case(2):
            printf("на победу.\n");
            this->win = true;
            break;
        }
    }
    void addItem(Item item) {
        this->items.push_back(item);
    }
    void addPlatform(Platform platform) {
        this->platforms.push_back(platform);
    }
    void addEnemy(Enemy enemy) {
        this->enemies.push_back(enemy);
    }
    Player *getPlayer() {
        return &this->player;
    }
    std::vector<Item> getItems() {
        return this->items;
    }
};


int main() {
    setlocale(LC_ALL, "RUS");

    Player* pl;
    pl = new Player(1.5, 2, 10, 50);
    Enemy enemy(-1, -1, 3, 1);
    std::vector<Enemy>enemies{ enemy };
    Position pos(0, -1);
    Platform platform(pos);
    std::vector <Platform> platforms{ platform };

    //работа с динамическим массивом объектов
    Item* arritems;
    arritems = new Item[3]{ Item(1,2,1),Item(4,5,2),Item(7,8,0) };
    std::vector<Item> items;
    for (int i = 0; i < 3; i++) {
        items.push_back(arritems[i]);
    }
    Level level(*pl, enemies, platforms, items);
    level.outLevel();

    //функция ввода с консоли
    Item it;
    it.writeItem();

    //функции вывода и бизнес-логика
    int b = 0;
    while (b != 27) {
        b = _getch();
        level.getPlayer()->movePlayer(b);
    }

    printf("Тест команды добавления патронов:\n");
    printf("%d\n", level.getPlayer()->getAmmo());
    level.getPlayer()->addAmmo(-50);
    printf("%d\n", level.getPlayer()->getAmmo());
    printf("Тест команды сбора предметов:\n");
    level.pickupItem(level.getItems()[0]);
    level.pickupItem(level.getItems()[1]);
    printf("\nТест команд по добавлению элементов внутри уровня:\n");
    level.addItem(it);
    level.addPlatform(Platform(0, 0.5));
    level.addEnemy(Enemy(pos, 1, 2));
    level.outLevel();

    //работа с массивом динамических объектов
    Enemy* enemigos[3];
    enemigos[0] = new Enemy(1, 1, 1, 1);
    enemigos[1] = new Enemy(1, 2, 2, 1);
    enemigos[2] = new Enemy(-1, 0, 5, 1);
    for (int i = 0; i < 3; i++) {
        while (enemigos[i]->getHealth() != 0) {
            enemigos[i]->takeDamage();
        }
    }
    for (int i = 0; i < 3; i++) {
        enemigos[i]->outEnemy();
    }

    delete pl;
    delete[] arritems;
    return 0;
}
