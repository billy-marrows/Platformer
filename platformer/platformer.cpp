#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include<locale.h>
#define UP 235
#define LEFT 228
#define RIGHT 162
#define DOWN 230
class Position {
private:
    int x;
    int y;
public:
    Position() {}
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    void move(int x, int y) { 
        this->x += x;
        this->y += y;
    }
    void setpos(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void outpos() {
        printf("Позиция: %d %d  ", this->x, this->y);
    }
    void writepos() {
        printf("Введите координаты: ");
        int flag =  1;
        while (flag) {
            while (scanf("%d %d", &this->x, &this->y) != 2) {
                printf("Ошибка ввода.\n");
                while (getchar() != '\n');
            }
            if ((this->x >= 0) && (this->x < 19) && (this->y >= 0) && (this->y < 20)) flag = 0;
        }
    }
};

class Enemy {
private:
    Position position;
    int health;
public:
    Enemy() {};
    Enemy(int x, int y) {
        Position position(x, y);
        this->position = position;
        this->health = 1;
    }
    Enemy(Position position) {
        this->position = position;
        this->health = 1;
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
    }
    void takeDamage() {
        this->health--;
    }
    void writeEnemy() {
        this->position.writepos();
        printf("Введите здоровье: ");
        while (scanf("%d", &this->health) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
        printf("Новый враг готов!\n");
    }
    bool operator ==(Enemy enemy) {                      //разумное использование оператора this
        return ((this->position.getX() == enemy.position.getX()) && (this->position.getY() == enemy.position.getY()));
    }
};

class Platform {
private:
    Position position;
public:
    Platform() {};
    Platform(int x, int y) {  // Изменено на int
        this->position = Position(x,y);
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
    Item() {};           
    Item(int x, int y, int type) {
        Position position(x, y);
        this->position = position;
        this->type = type;
    }
    Item(Position position, int type) {
        this->position = position;
        this->type = type;
    }
    Position &getpos() {      
        return this->position;
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
        this->position.writepos();
        printf("Введите тип предмета: ");
        while (scanf("%d", &this->type) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
    }
    bool operator ==(Item item) {                          //разуменое использование оператора THIS
        return ((this->position.getX() == item.position.getX())&&(this->position.getY()==item.position.getY()));
    }

};


class Player {
private:
    Position position;
    int health;
public:
    Player() {}                         //конструкторы
    Player(int x, int y, int health) {
        Position position(x, y);
        this->position = position;
        this->health = health;

    }
    Player(Position position, int health, int ammo) {
        this->position = position;
        this->health = health;
    }
    Position getPos() {                           //функции доступа к членам класса
        return this->position;
    }
    int getHealth() {
        if (this->health < 1) printf("Игрок погиб!\n");
        return this->health;
    }
    void addHealth(int d) {
        this->health += d;
    }
    void movePlayer(int b) {
        switch (b) {
        case(UP):
            this->position.move(0, 1);
            break;
        case(LEFT):
            this->position.move(-1, 0);
            break;
        case(DOWN):
            this->position.move(0, -1);
            break;
        case(RIGHT):
            this->position.move(1, 0);
            break;
        }
    }
    void checkCollision(Enemy& enemy) {
        if ((this->position.getX() == enemy.getpos().getX()) && (this->position.getY() == enemy.getpos().getY())) {
            printf("Вы получили урон!\n");
            enemy.takeDamage();
            this->addHealth(-1);
        }
    }
    void checkCollision(Item* item) {
        if ((this->position.getX() == item->getpos().getX()) && (this->position.getY() == item->getpos().getY())) {
            item->getpos().setpos(-1,-1);
        }
    }
    void writePlayer() {                                //создание путём ввода через консоль
        printf("Создание игрока:\n");
        this->position.writepos();
        printf("Введите здоровье: ");
        while (scanf("%d", &this->health) != 1) {
            printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
        printf("Игрок готов!\n");
    }
    Player operator++(int) {                   //перегрузка постфиксного оператора "++"
        this->health++;
    }
    Player& operator++() {                    //перегрузка префиксного оператора "
        this->health++;
    }
    friend void outPlayer(Player player);     //сдружаем класс Player с функцией outPlayer
};

void outPlayer(Player player) {              //дружественная функция
    printf("Позиция игрока: %d %d   Здоровье: %d\n", player.position.getX(), player.position.getY(), player.health);
}
class Level {
private:
    std::string name;
    Player player;
    std::vector <Enemy> enemies;
    std::vector <Platform> platforms;
    std::vector <Item> items;
    bool win;
    char grid[20][20];
    static int completedTimes;        //статическая переменная
public:
    Level() {};           
    Level(std::string name, Player player, const std::vector<Enemy> enemies, const std::vector<Platform> platforms, const std::vector<Item> items) {
        this->name = name;
        this->player = player;
        this->enemies = enemies;
        this->platforms = platforms;
        this->items = items;
        this->win = false;
    }
    void outLevel() {                                       //вывод в консоль
        printf("Информация об уровне:\n  ");
        printf("  Название: %s\n  ", &name);
        outPlayer(this->player);
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
    void pickupItem(int x, int y) {
        Item pickedUpItem;
        for (Item item : this->items) {
            if ((item.getpos().getX() == x) && (item.getpos().getY() == y)) {
                pickedUpItem = item;
                items.erase(std::remove(items.begin(), items.end(), item), items.end());
                break;
            }
        }
        switch (pickedUpItem.getType()) {
        case(0):
            printf("Подобран предмет на здоровье.\n");
            this->player.addHealth(1);
            break;
        case(1):
            printf("Вы победили!\n");
            this->win = true;
            completedTimes++;
            printf("Всего пройдено %d уровней\n", completedTimes);
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
    void deleteEnemy(int x, int y) {
        Enemy enemyToDelete;
        for (Enemy enemy : this->enemies) {
            if ((enemy.getpos().getX() == x )&& (enemy.getpos().getY() == y)) {
                enemyToDelete = enemy;
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemyToDelete), enemies.end());
                break;
            }
        }

    }
    int getwin() {
        return this->win;
    }
    void displayName() {
        std::cout << this->name << std::endl;
    }
    Player* getPlayer() {
        return &this->player;
    }                      //этот метод возвращает адрес игрока
    std::vector<Item>& getItems() {
        return this->items;
    }
    std::vector<Enemy>& getEnemies() {
        return this->enemies;
    }
    std::vector<Platform> getPlatforms() {
        return this->platforms;
    }
    void writeLevel() {  
        this->player.writePlayer();
        Item it;
        Enemy en;
        Platform pl;
        std::vector<Item> items;
        std::vector<Enemy> enemies;
        std::vector<Platform> Platforms;
        printf("Введите название уровня: ");
        std::getline(std::cin, this->name);
        int choice = 1;
        printf("Создание предметов:\n");
        while (choice) {
            it.writeItem();
            items.push_back(it);
            printf("Добавить ещё предметов? 0 = нет, 1 = да ");
            scanf("%d", &choice);
            if (!choice) {
                int haswin = 0;
                for (Item item : items) {
                    if (item.getType() == 1) {
                        haswin++;
                    }
                }
                if (haswin == 0) {
                    printf("Уровень должен иметь хотя бы один предмет на победу!\n Тип предмета на победу - 1\n");
                    choice = 1;
                }
            }
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
    void renderGrid() {          //да простит меня боже за этот ужас
        char playGrid[20][20]{ {"*******************"}, {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"},  {"*******************"} };
        for (Enemy enemy : this->enemies) {
            if (enemy.getHealth() != 0) playGrid[enemy.getpos().getX()][enemy.getpos().getY()] = 'E';
        }
        for (Platform platform : this->platforms) {
            playGrid[platform.getpos().getX()][platform.getpos().getY()] = 'X';
        }
        for (Item item : this->items) {
            if (item.getType() == 1) playGrid[item.getpos().getX()][item.getpos().getY()] = 'W';
            else playGrid[item.getpos().getX()][item.getpos().getY()] = 'I';
        }
        playGrid[this->getPlayer()->getPos().getX()][this->getPlayer()->getPos().getY()] = 'P';
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                printf("%c", playGrid[j][i]);
                this->grid[j][i] = playGrid[j][i];
            }
            printf("\n");
        }
    }
    int movePlayer(int dest) {
        if (dest == 27) return 27;
        int x = this->getPlayer()->getPos().getX(),
            y = this->getPlayer()->getPos().getY();
        switch (dest) {
        case (UP):
            if (((y + 1) >= 0) && ((y + 1) < 20)) {
                if (this->grid[x][y + 1] == 'X')break;
                this->getPlayer()->movePlayer(UP);
            }break;
        case (LEFT):
            if (((x - 1) >= 0) && ((x - 1) < 20)) {
                if (this->grid[x-1][y] == 'X')break;
                this->getPlayer()->movePlayer(LEFT);
            }            break;
        case(DOWN):
            if (((y - 1) >= 0) && ((y - 1) < 20)) {
                if (this->grid[x][y - 1] == 'X')break;
                this->getPlayer()->movePlayer(DOWN);
            }
            break;
        case(RIGHT):
            if (((x + 1) >= 0) && ((x + 1) < 20)) {
                if (this->grid[x+1][y] == 'X')break;
                 this->getPlayer()->movePlayer(RIGHT);
            }
        }
    }
    void generateNewLevel() {
        int type;
        do {
            type = rand() % 2;
            this->items.push_back(Item(rand() % 20, rand() % 20, type));
        } while (type != 1);
        this->enemies.push_back(Enemy(rand() % 20, rand() % 20));
        this->platforms.push_back(Platform(rand() % 20, rand() % 20));
        this->name = "Levelname" + completedTimes;
        this->win = false;
    }
    void collectGarbage() {
        for (Item item : items) {
            if ((item.getpos().getX() < 0) || (item.getpos().getY() < 0) || (item.getpos().getX() > 20) || (item.getpos().getY() > 20)) {
                this->pickupItem(item.getpos().getX(), item.getpos().getY());
            }
        }
        for (Enemy enemy : enemies) {
            if (enemy.getHealth() < 1)
                this->deleteEnemy(enemy.getpos().getX(), enemy.getpos().getY());
        }
    }
    static int getCompletedTimes() { //пример статического метода
        return completedTimes;
    }
    Level operator+ (const Level& level) {       //перегрузка оператора +
        Level newlevel;
        newlevel.player = this->player;
        newlevel.name = this->name;
        newlevel.win = 0;
        for (Enemy enemigo : level.enemies) {
            newlevel.addEnemy(enemigo);
        }
        for (Enemy enemigo : this->enemies) {
            newlevel.addEnemy(enemigo);
        }
        for (Item item : level.items) {
            newlevel.addItem(item);
        }
        for (Item item : this->items) {
            newlevel.addItem(item);
        }
        for (Platform platform : level.platforms) {
            newlevel.addPlatform(platform);
        }
        for (Platform platform : this->platforms) {
            newlevel.addPlatform(platform);
        }
        return newlevel;
    }
    };
int Level::completedTimes = 0; //инициализация статической переменной

int main() {
    setlocale(LC_ALL, "rus");
    Player *pl = new Player(1, 2, 10);
    Enemy enemy(2, 2);
    std::vector<Enemy>enemies{ enemy };
    Position pos(3, 10);
    Platform platform(pos);
    std::vector <Platform> platforms{ platform };
    std::string name{ "level1" };
    Item* arritems;
    arritems = new Item[3]{ Item(1,3,1),Item(4,5,0),Item(7,8,0) };
    std::vector<Item> items;
    for (int i = 0; i < 3; i++) {
        items.push_back(arritems[i]);
    }
    Level level1(name,*pl, enemies, platforms, items);
    Level level;
    int menu = 0;
    while (true) {
        printf("Меню:\n1)Играть\n2)Ввести уровень с клавиатуры\n3)Выход\n");
        scanf("%d", &menu);
        if (menu == 1) {
            level = level1;
            if (level.getPlayer()->getHealth() == 0)level.getPlayer()->addHealth(1);
            int moveResult = 0;
            while (moveResult != 27) {
                if (level.getwin() == true)level.generateNewLevel();
                level.displayName();
                outPlayer(*level.getPlayer());
                level.renderGrid();
                moveResult = _getch();
                level.movePlayer(moveResult);
                for (Item& item : level.getItems()) {
                    Item* it = &item;
                    level.getPlayer()->checkCollision(it);
                }
                for (Enemy& enemy : level.getEnemies()) {
                    level.getPlayer()->checkCollision(enemy);
                }
                if (level.getPlayer()->getHealth() == 0) {
                    printf("Игра окончена!\n");
                    break;
                }
                level.collectGarbage();
            }
        }
        else if (menu == 2) {
            level1.writeLevel();
        }
        else if (menu == 3) break;
    }
    delete pl;
    delete[]arritems;
    return 0;
}