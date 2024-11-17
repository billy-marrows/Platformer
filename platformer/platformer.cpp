#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include<locale.h>

struct Position {
    double x;
    double y;
};
struct Player {
    Position position;
    int health;
    int ammo;
};
struct Enemy {
    Position position;
    int health=1;
    char type;
};
struct Platform {
    Position position;
};
struct Item {
    Position position;
    int type;
};
struct Level {
    char name[20];
    Player player;
    std::vector <Enemy> enemies;
    std::vector <Platform> platforms;
    std::vector <Item> items;
    bool win = false;
};

//бизнес логика

void movePlayer(Player &player, int b) {
    switch (b) {
    case(230):
        player.position.y+=1;
        break;
    case(228):
        player.position.x-=1;
        break;
    case(235):
        player.position.y-=1;
        break;
    case(162):
        player.position.x+=1;
        break;
    }
}
void addPlatform(Level &level,Platform platform) {
    level.platforms.push_back(platform);
}
void addEnemy(Level &level, Enemy enemy) {
    level.enemies.push_back(enemy);
}
void addItem(Level& level, Item item) {
    level.items.push_back(item);
}
void pickupItem(Level &level, Player &player, Item &item) {
    printf("Подобран предмет ");
    switch (item.type) {
    case(0):
        printf("на здоровье.\n");
        player.health++;
        break;
    case(1):
        printf("на патроны.\n");
        player.ammo += 50;
        break;
    case(2):
        printf("на победу.\n");
        level.win = true;
        break;
    }
}
void touchEnemy(Player &player, Enemy &enemy) {
    printf("Игрок получил урон!\n");
    player.health--;
}

//вывод информации

void outPlatform(Platform &platform) {
    printf("Позиция платформы: %1.2f %1.2f\n", platform.position.x, platform.position.y);
}
void outItem(Item &item) {
    printf("Информация о предмете: ");
    printf("%1.2f %1.2f ", item.position.x, item.position.y);
    printf("%d\n", item.type);  
}
void outPlayer(Player &player) {
    printf("Информация об игроке: ");
    printf("%1.2f %1.2f ", player.position.x, player.position.y);
    printf("%1d ", player.health);
    printf("%3d\n", player.ammo);
}
void outEnemy(Enemy &enemy) {
    printf("Информация о враге:\n");
    printf("%1.2f %1.2f ", enemy.position.x, enemy.position.y);
    printf("%1d", enemy.health);
    printf("%1d\n", enemy.type);
}
void outLevel(Level &level) {
    printf("Информация об уровне:\n");
    printf("%s\n", level.name);
    outPlayer(level.player);
    for (Enemy enemy : level.enemies) {
        outEnemy(enemy);
    }
    for (Platform platform : level.platforms) {
        outPlatform(platform);
    }
    for (Item item : level.items) {
        outItem(item);
    }
    if (level.win == true) {
        printf("Уровень пройден.\n");
    }
    else printf("Уровень не пройден.\n");
}

// Функции инициализации 

Player initPlayer(double x, double y, int health, int ammo) {
    Player player;
    Position position{ x,y };
    player.position = position;
    player.health = health;
    player.ammo = ammo;
    return player;
}
Enemy initEnemy(double x, double y, char type, int health) {
    Enemy enemy;
    Position position{ x,y };
    enemy.position = position;
    enemy.type = type;
    enemy.health = health;
    return enemy;
}
Platform initPlatform(double x, double y) {
    Platform platform;
    Position position{ x,y };
    platform.position = position;
    return platform;
}
Item initItem(double x, double y, int type) {
    Item item;
    Position position{ x,y };
    item.position = position;
    item.type = type;
    return item;
}
Level initLevel(const char *name,Player &player, const std::vector<Enemy>& enemies, const std::vector<Platform>& platforms, const std::vector<Item>& items) {
    Level level;
    strcpy(level.name, name);
    level.player = player;
    level.enemies = enemies;
    level.platforms = platforms;
    level.items = items;
    level.win = false;
    return level;
}

//функции ввода через консоль
Player writePlayer() {
    double x, y;
    int health, ammo;
    printf("Создание игрока:\n");
    printf("Введите позицию игрока: ");
    while (scanf("%lf %lf", &x, &y) != 2) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    printf("Введите количество здоровья: ");
    while (scanf("%d", &health) != 1) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    printf("Введите количество патронов: ");
    while (scanf("%d", &ammo) != 1) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    return initPlayer(x, y, health, ammo);
}
Enemy writeEnemy() {
    double x, y;
    int health,type;
    printf("Создание врага:\n");
    printf("Введите позицию врага: ");
    while (scanf("%lf %lf", &x, &y) != 2) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    printf("Введите здоровье: ");
    while (scanf("%d", &health) != 1) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    printf("Введите тип:  ");
    while (scanf("%d", &type) != 1) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return initEnemy(x, y, type,health);
}
Platform writeplatform() {
    double x, y;
    printf("Введите позицию предмета:  ");
    while (scanf("%lf %lf", &x,&y) != 2) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return initPlatform(x, y);
}
Item writeItem() {
    double x, y;
    int type;
    printf("Создание предмета:\n");
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
    while (getchar() != '\n');
    return initItem(x, y, type);
}
Level writeLevel() {    
    char name[20];
    Player player;
    std::vector<Item> items;
    std::vector<Enemy> enemies;
    std::vector<Platform> platforms;
    printf("Создание уровня:  \n");
    printf("Введите название уровня: ");
    while (scanf("%s", name) != 1) {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    player = writePlayer();
    bool a = 1;
    while (a == 1) {
        items.push_back(writeItem());
        printf("Хотите добавить ещё предметов? 1 - да, 0 - нет");
        scanf("%d", &a);
        while (getchar() != '\n');
    }
    a = 1;
    while (a == 1) {
        platforms.push_back(writeplatform());
        printf("Хотите добавить ещё платформу? 1 - да, 0 - нет");
        scanf("%d", &a);
        while (getchar() != '\n');
    }
    a = 1;
    while (a == 1) {
        enemies.push_back(writeEnemy());
        printf("Хотите добавить ещё врагов? 1 - да, 0 - нет");
        scanf("%d", &a);
        while (getchar() != '\n');
    }
    return initLevel(name, player, enemies, platforms, items);
}
int main() {
    setlocale(LC_ALL, "RUS");

    //тест функций инициализации и "статических" переменных
    Player player = initPlayer(0, 0, 3, 50);
    Enemy enemy = initEnemy(1.0, 1.0, 1, 3);
    Platform platform = initPlatform(2.0, 2.0);
    Item item = initItem(3.0, 3.0, 1);
    std::vector<Enemy> enemies = { enemy };
    std::vector<Platform> platforms = { platform };
    std::vector<Item> items = { item };
    Level level = initLevel("levelname",player, enemies, platforms, items);
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
    addEnemy(level,initEnemy(1,1,1,3));
    outLevel(level);
    return 0;
}

