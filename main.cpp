#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <queue>
#include <cstdlib>
using namespace std;

#define KEY_UP 'W'
#define KEY_DOWN 'S'
#define KEY_LEFT 'A'
#define KEY_RIGHT 'D'
#define ESCAPE 27
#define WALL 99999999
#define INFINITY 8888888

class object {
public:
    int Y;
    int X;
    int movement_count = 0;
    char direction = 'a';
public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВВОД НАПРАВЛЕНИЯ И ИНИЦИАЛИЗАЦИЯ direction
    void Read_direction() {
        int i = getch();
        if (i == 224) {
            i = getch();
            switch (i)
                {
                case 72:
                    direction = 'W';
                    break;
                case 80:
                    direction = 'S';
                    break;
                case 75:
                    direction = 'A';
                    break;
                case 77:
                    direction = 'D';
                    break;
                default:
                    break;
                }
        } else {
            direction = toupper(i);
        }
    }
};
struct point{
    int Y;
    int X;
};







class level{

public:







    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕНЯЕТ СЧЁТ
    double  Get_score(){
        return (hero.movement_count+0.0)/distance_map[destination.Y][destination.X]*1.4;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ГЕРОЯ
    object& Get_hero(){
        return hero;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ПОЛОЖЕНИЕ КЛАДА
    object& Get_destination(){
        return destination;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫПОЛНЯЕТ ПЕРЕДВИЖЕНИЕ
    bool Check_move(point new_rotate){

        // ОБРАБОТКА ВЫХОДА ЗА ГРАНИЦУ КАРТЫ
        Correct_coordinates(new_rotate);

        if (map[new_rotate.Y][new_rotate.X] != '#'){
            map[new_rotate.Y][new_rotate.X] = '!';
            map[hero.Y][hero.X] = '_';
            hero.Y = new_rotate.Y;
            hero.X = new_rotate.X;
            return true;
        }
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // БЫЛО ЛИ ПЕРЕДВИЖЕНИЕ, ЕСЛИ ДА ТО ОНО ВЫПОЛНЯЕТСЯ
    bool Was_movement() {
        bool was_movement = false;
        switch (hero.direction) {
            case KEY_LEFT:
                was_movement = Check_move({hero.Y, hero.X - 1});
                break;

            case KEY_RIGHT:
                was_movement = Check_move({hero.Y, hero.X + 1});
                break;

            case KEY_UP:
                was_movement = Check_move({hero.Y - 1, hero.X});
                break;

            case KEY_DOWN:
                was_movement = Check_move({hero.Y + 1, hero.X});
                break;
            default:
                break;
        }
        return was_movement;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ РАСПЛОЖЕНИЯ ИГРОКА
    void Init_hero(){
            bool flag = true;
            while (flag){
                srand(time(NULL));
                int x = rand() % width;
                int y = rand() % hight;
                if (map[y][x] == '_') {
                    map[y][x] = '!';
                    distance_map[y][x] = 0;
                    flag = false;
                    hero = {y, x};
                }
            }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ РАСПЛОЖЕНИЯ КЛАДА
    void Init_destination(){
        bool flag = true;
        while (flag){
            srand(time(NULL));
            int x = rand() % width;
            int y = rand() % hight;
            if ((distance_map[y][x] != WALL) && (distance_map[y][x] != INFINITY) && (x != hero.X || y != hero.Y)) {
                map[y][x] = 'X';
                flag = false;
                destination = {y, x};
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // АЛГОРИТМ ЛИ
    void Lee_algorithm(int weawe_count, queue<point>* call_queue){

        if (weawe_count == 0){
            call_queue = new(queue<point>);
            call_queue->push({hero.Y, hero.X});
        }

        int count = call_queue->size();


        while (count != 0){

            // КООРДИНАТЫ РАССМАТРИВАЕМОГО ЯДРА
            int x = call_queue->front().X;
            int y = call_queue->front().Y;
            point p;

            distance_map[y][x] = min(weawe_count, distance_map[y][x]);

            p = {y - 1, x};
            if (Check(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            p = {y + 1, x};
            if (Check(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            p = {y, x - 1};
            if (Check(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            p = {y, x + 1};
            if (Check(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            call_queue->pop();
            count--;
        }

        if (!call_queue->empty()) {
            Lee_algorithm(weawe_count + 1, call_queue);
        }

        if (weawe_count == 0){
            delete call_queue;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕТОД ВОЗРАЩАЕТ FALSE, ЕСЛИ КООРДИНАТЫ НЕКОРРЕКТНЫ.
    bool Check(point p){
        Correct_coordinates(p);
        if (distance_map[p.Y][p.X] == INFINITY)
            return true;
        else
            return false;

    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕНЯЕТ КООРДИНАТЫ, ЕСЛИ ОНИ НЕКОРРЕКТНЫ.
    void Correct_coordinates(point& p){
        if (p.X == -1) p.X = width-1;
        if (p.X == width) p.X = 0;

        if (p.Y == -1) p.Y = hight-1;
        if (p.Y == hight) p.Y = 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // СОЗДАНИЕ map
    void Create_map(int hight, int width){

        this->hight = hight;
        this->width = width;

        map = new char* [this->hight];
        for ( int i = 0; i < this->hight; i++){
            map[i] = new char [this->width];
        }

    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // СОЗДАНИЕ И ИНИЦИАЛИЗИРОВАНИЕ distance_map
    void Create_distance_map(){

        distance_map = new int* [hight];
        for ( int i = 0; i < hight; i++){
            distance_map[i] = new int [width];
        }

        for ( int i = 0; i < hight; i++){
            for (int j = 0; j < width; j++){
                switch (map[i][j]){
                case '#':
                    distance_map[i][j] = WALL;
                    break;
                case '_':
                    distance_map[i][j] = INFINITY;
                    break;
                default:
                    distance_map[i][j] = 0;
                    break;
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ ЛАБИРИНТА
    void Fill_bineary_maze() {

        int i, j,
            direction;

        for (i = 0; i < hight; i++){
            for (j = 0; j < width; j++){
                map[i][j] = '#';
            }
        }
        for (j = 0; j < width; j++) {
            map[0][j] == '_';
        }
        for (i = 0; i < hight; i++) {
            map[i][width-1] == '_';
        }

        for (i = 1; i < hight; i++){
        //    srand(time(NULL));
            for (j = 0; j < width - 1; j++){
                direction = rand() % 2;
                if (direction == 0){
                    map[i-1][j] = '_';
                }
                else{
                    map[i][j+1] = '_';
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫВОД КАРТЫ
    void Print_map() {
        for (int i = 0; i < hight; i++) {
            cout << endl;
            for (int j = 0; j < width; j++) {
                cout << map[i][j];
            }
        }
        cout << endl;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫВОД КАРТЫ РАССТОЯНИЙ
    void Print_distance_map(){
        for (int i = 0; i < hight; i++) {
            cout << endl;
            for (int j = 0; j < width; j++) {
                cout << distance_map[i][j] << ' ';
            }
        }
        cout << endl;
    }


private:
    char ** map;
    int hight,
        width;
    int ** distance_map;
    object hero = {INFINITY, INFINITY},
           destination = {INFINITY, INFINITY};
};


int main() {

    bool not_escape = true;
    double score = 0,
        best_score = 0;
    int level_number = 0;
    // ОТКРЫВАЕМ ПОТОК, СЧИТЫВАЕМ ЛУЧШИЙ СЧЁТ, ЗАКРЫВАЕМ ЕГО
    ifstream cin_score("score.txt");
    cin_score >> best_score;
    cin_score.close();

    while(not_escape){

        cout << "Level is loading...";
        level new_level;
        new_level.Create_map(20, 50);
        new_level.Fill_bineary_maze();
        new_level.Create_distance_map();
        new_level.Init_hero();
        new_level.Lee_algorithm(0, NULL);
        new_level.Init_destination();
        level_number++;

        system("cls");

        while ((not_escape) && ((new_level.Get_hero().Y != new_level.Get_destination().Y) || (new_level.Get_hero().X != new_level.Get_destination().X)))
        {
            cout << "Level " << level_number << endl << endl;
            cout << "Your score is " << score << endl;
            cout << "The best score " << best_score << endl;
            cout << "You did " << new_level.Get_hero().movement_count << " steps" << endl;
            new_level.Print_map();

            new_level.Get_hero().Read_direction();
            not_escape = (new_level.Get_hero().direction != ESCAPE);
            if (new_level.Was_movement()){
                new_level.Get_hero().movement_count++;
            }

            system("cls");
         }

         score += new_level.Get_score();
         if (score > best_score) {
             best_score = score;
         }

    }
    cout << "You passed " << level_number << " levels" << endl;
    cout << "Your score is " << score << endl;;
    cout << "The best score is " << best_score << endl;
    cout << '\n';
    ofstream cout_score("score.txt");
    cout_score << best_score;
    cout_score.close();
    system("pause");
    return 0;
}
