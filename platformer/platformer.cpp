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
    Position() {}       
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
    void writepos() {
        double x, y;
        printf("Введите коориднаты: ");
        while (scanf("%lf %lf", &this->x, &this->y) != 2) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
    }
};

class Player {
private:
    Position position;
    int health;
    int ammo;
public:
    Player() {}                         //конструкторы
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
    Position getPos() {                           //функции доступа к членам класса
        return this->position;
    }
    int getHealth() {
        if (this->health < 1) printf("Игрок погиб!\n");
        return this->health;
    }
    int getAmmo() {
        if (this->ammo < 1) printf("Патроны игрока кончились!\n");
        return this->ammo;
    } 
    void outPlayer() {                             //вывод в консоль
        printf("Информация об игроке:   ");
        this->position.outpos();
        printf("Здоровье: %d  ", this->health);
        printf("Патроны:%d\n", this->ammo);
    }
    void addAmmo(int d) {                          //бизнес логика
        this->ammo += d;
    }
    void addHealth(int d) {
        this->health += d;
    }
    void movePlayer(int b)   {
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
    void writePlayer() {                                //создание путём ввода через консоль
        printf("Создание игрока:\n");
        this->position.writepos();
        printf("Введите здоровье: ");
        while (scanf("%d", &this->health) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
        printf("Введите патроны: ");
        while (scanf("%d",&this->ammo) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
        printf("Игрок готов!\n");
    }
};
class Enemy {                                          
private:
    Position position;
    int health;
    int type;
public:                                                
    Enemy() {};
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
    Position getpos() {
        return this->position;
    }
    int getHealth() {
        return this->health;
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
    void writeEnemy() {
        this->position.writepos();
        printf("Введите здоровье: ");
        while (scanf("%d", &this->health) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
        printf("Введите тип: ");
        while (scanf("%d", &this->type) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
        printf("Новый враг готов!\n");
    }
};
class Platform {
private:
    Position position;
public:
    Platform() {};
    Platform(double x, double y) {
        Position position(x, y);
        this->position = position;
    }
    Platform(Position position) {
        this->position = position;
    }
    Position getpos() {
        return this->position;
    }
    void outPlatform() {
        printf("Информация о платформе: ");
        this->position.outpos();
        printf("\n");
    }
    void writePlatform() {
        this->position.writepos();
        printf("Платформа готова!\n");
    }
};
class Item {
private:
    Position position;
    int type;
public:
    Item() {};                                       //конструкторы
    Item(double x, double y, int type) {
        Position position(x, y);
        this->position = position;
        this->type = type;
    }
    Item(Position position, int type) {
        this->position = position;
        this->type = type;
    }           
    Position getpos() {                             //команды для доступа к членам этого класса
        return this->position;
    }
    int getType() {
        return this->type;
    }
    void outItem() {                                 //вывод в консоль
        printf("Информация о предмете:");
        this->position.outpos();
        printf("Тип: %d\n", this->type);
    }
    void writeItem() {                                 //создание предмета путём ввода из консоли
        this->position.writepos();
        printf("Введите тип предмета: ");
        while (scanf("%d", &this->type) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
    }
};
class Level {
private:
    char name[20];
    Player player;
    std::vector <Enemy> enemies;
    std::vector <Platform> platforms;
    std::vector <Item> items;
    bool win;
public: 
    Level() {};                               //конструкторы
    Level(char name[20], Player player, const std::vector<Enemy> enemies, const std::vector<Platform> platforms, const std::vector<Item> items) {
        strcpy(this->name,name);
        this->player = player;
        this->enemies = enemies;
        this->platforms = platforms;
        this->items = items;
        this->win = false;
    }
    void outLevel() {                                       //вывод в консоль
        printf("Информация об уровне:\n  ");
        printf("  Название: %s\n  ", &name);
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
    void pickupItem(Item item) {                       //бизнес логика
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
    char *getName(){                   //команды для доступа к членам этого класса
        return this->name;
    }
    Player *getPlayer() {                      
        return &this->player;
    }
    std::vector<Item> getItems() {
        return this->items;
    }
    std::vector<Enemy> getEnemies() {
        return this->enemies;
    }
    std::vector<Platform> getPlatforms() {
        return this->platforms;
    }
    bool getwin() {
        return this->win;
    }
    void writeLevel() {         //создание уровня путём ввода из консоли
        char name[20];
        this->player.writePlayer();
        Item it;
        Enemy en;
        Platform pl;
        std::vector<Item> items;
        std::vector<Enemy> enemies;
        std::vector<Platform> Platforms;
        printf("Введите название уровня: ");
        while (scanf("%20s", name) != 1) {
            printf("Попробуйте ещё раз.\n");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');
        int choice = 1;
        printf("Создание предметов:\n");
        while (choice) {
            it.writeItem();
            items.push_back(it);
            printf("Добавить ещё предметов? 0 = нет, 1 = да ");
            scanf("%d", &choice);
        }
        while (getchar() != '\n');
        choice = 1;
        printf("Создание врагов:\n");
        while (choice) {
            en.writeEnemy();
            enemies.push_back(en);
            printf("Добавить ещё врагов? 0 = нет, 1 = да");
            scanf("%d", &choice);
        }
        while (getchar() != '\n');
        choice = 1;
        printf("Создание платформ:\n");
        while (choice) {
            pl.writePlatform();
            platforms.push_back(pl);
            printf("Добавить ещё платформ? 0 = нет, 1 = да");
            scanf("%d", &choice);
        }
        this->items = items;
        this->enemies = enemies;
        this->platforms = platforms;
    }
};


int main() {
    setlocale(LC_ALL, "RUS");
    Player* pl;
    pl = new Player(1.5, 2, 10, 50);     //этот указатель будет удалён оператором delete вместе с содержимым
    Enemy enemy(-1, -1, 3, 1);
    std::vector<Enemy>enemies{ enemy };
    Position pos(0, -1);
    Platform platform(pos);
    std::vector <Platform> platforms{ platform };
    char name[20]{ "LevelName" };

    //работа с динамическим массивом объектов
    Item* arritems;
    arritems = new Item[3]{ Item(1,2,1),Item(4,5,2),Item(7,8,0) };          //этот указатель тоже будет удалён оператором delete
    std::vector<Item> items;
    for (int i = 0; i < 3; i++) {
        items.push_back(arritems[i]);
    }
    Level level(name, *pl, enemies, platforms, items);
    printf("Вывод параметров уровня, созданного внутри программы с помощью динамических переменных (и не только):\n");
    level.outLevel();

    printf("\nВвод с консоли нового объекта класса Item:\n");
    Item it;
    it.writeItem();

    printf("\nРабота функций вывода и бизнес-логики:\n");
    printf("Нажимайте WASD для передвижения, Esc для выхода.\n");
    int b = 0;
    while (b != 27) {
        b = _getch();
        level.getPlayer()->movePlayer(b);
    }
    printf("\nТест команды добавления патронов:\n");
    printf("Количество патронов игрока: %d\n", level.getPlayer()->getAmmo());
    level.getPlayer()->addAmmo(-50);
    printf("Количество патронов игрока после отнимания 50 штук: %d\n", level.getPlayer()->getAmmo());
    printf("\nТест команды сбора предметов:\n");
    level.pickupItem(level.getItems()[0]);
    level.pickupItem(level.getItems()[1]);
    printf("\nТест команд по добавлению элементов внутри уровня:\n");
    level.addItem(it);
    level.addPlatform(Platform(0, 0.5));
    level.addEnemy(Enemy(pos, 1, 2));
    printf("\nПо сравнению с предыдущим выведенным уровнем в этот был добавлен дополнительный враг, платформа и предмет (предмет, написанный вами)\n");
    printf("а у игрока изменилось расположение на зафиксированное после нажатия ESC\n");
    level.outLevel();

    printf("Работа с динамическим массивом переменнных:\n");
    printf("Динамически создаётся массив из трёх врагов которым наносится урон до момента приравнивания его к нулю.\n");
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
    printf("Создание уровня путём ввода через консоль:\n");
    Level lev;
    lev.writeLevel();
    printf("Вывод параметров полученного уровня в консоль:\n");
    lev.outLevel();

    delete pl;
    delete[] arritems;
    return 0;
}
