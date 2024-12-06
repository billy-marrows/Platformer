package javaidk;
public class Platformer{
private static Platformer platformer = null;
protected static final 
class Position {                          
private:
    double x;
    double y;
public:
    Position(double x, double y) {
        this.x = x;
        this.y = y;
    }
    double getX() {                 
        return this.x;
    }
    double getY() {
        return this.y;
    }
    void move(double x, double y) {
        this.x += x;
        this.y += y;
    }
    void setpos(double x, double y) {
        this.x = x;
        this.y = y;
    }
    void outpos() {                               
        printf("Позиция: %1.2lf %1.2lf  ", this.x, this.y);
    }
    void writepos() {
        double x, y;
        System.out.printf("Введите коориднаты: ");
        while (scanf("%lf %lf", &this->x, &this->y) != 2) {
            System.out.printf("Ошибка ввода.\n");
            while (getchar() != '\n');
        }
    }
}

class Player {
private:
Position position = new Position();
    int health;
    int ammo;
public:
    Player(double x, double y, int health, int ammo) {
        Position position(x, y)= new Position(;
        this.position = position;
        this.health = health;
        this.ammo = ammo;
    }
    Player(Position position, int health, int ammo) {
        this.position = position;
        this.health = health;
        this.ammo = ammo;
    }                                                   
    Position getPos() {                           //функции доступа к членам класса;
        return this.position;
    }
    int getHealth() {
        if (this.health < 1) printf("�?грок погиб!\n");
        return this.health;
    }
    int getAmmo() {
        if (this.ammo < 1) printf("Патроны игрока кончились!\n");
        return this.ammo;
    } 
    void outPlayer() {                             //вывод в консоль
        System.out.printf("�?нформация об игроке:   ");
        this.position.outpos();
        printf("Здоровье: %d  ", this.health);
        printf("Патроны:%d\n", this.ammo);
    }
    void addAmmo(int d) {                          //бизнес логика
        this.ammo += d;
    }
    void addHealth(int d) {
        this.health += d;
    }
    void movePlayer(int b)   {
        switch (b) {
        case(230):
            this.position.move(0, 1);
            break;
        case(228):
            this.position.move(-1, 0);
            break;
        case(235):
            this.position.move(0, -1);
            break;
        case(162):
            this.position.move(1, 0);
            break;
        }
        printf("Позиция игрока: %1.1lf %1.1lf\n", this.getPos().getX(), this.getPos().getY());
}
