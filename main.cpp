#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <queue>
using namespace std;

#define KEY_UP 'W'
#define KEY_DOWN 'S'
#define KEY_LEFT 'A'
#define KEY_RIGHT 'D'
#define ESCAPE 27
#define WALL 9
#define INFINITY 8

struct point{
    int Y;
    int X;
};

void corect_coordinates(point&, int, int);
void check_move(point&, point, char**, int, int);
void movement(int&, point&, char **, int, int);

void print_field(char **, int, int);
void print_field(int **, int, int);

char get_direction();


void Lee_algorithm(int **, char **, queue<point>&, int, int, int);




int main() {
    ifstream cin_file("input.txt");
    ofstream cout_file("output.txt");
    int i, j;
    int hight = 30;
    int width = 20;
    point hero = {0,0};

    // СОЗДАНИЕ ДВУМЕРНОГО МАССИВА КАРТЫ И КОЛИЧЕСТВА ШАГОВ ДО КЛЕТОК
    char **field = new char* [hight];
    int **step_field = new int* [hight];
    for (i = 0; i < hight; i++){
        field[i] = new char [width];
        step_field[i] = new int [width];
    }

    // ЗАПОЛНЕНИЕ МАССИВА
    for (i = 0; i < hight; i++){
        for (j = 0; j < width; j++){
            cin_file >> field[i][j];
            switch (field[i][j]){
                case '#':
                    step_field[i][j] = WALL;
                    break;
                case '_':
                    step_field[i][j] = INFINITY;
                    break;
                default:
                    step_field[i][j] = 0;
                    break;
            }
        }
    }


    // ЗАПУСК АЛГОРИТМА ЛИ и объявление вектора вызовов
    queue<point> call_queue;
    call_queue.push({0, 0});
    Lee_algorithm(step_field, field, call_queue, hight, width, 1);
    // print_field(step_field, hight, width);


    // СЧИТЫВАНИЕ ПЕРЕДВИЖЕНИЙ
    bool not_escape = true;
    while(not_escape){
        print_field(field, hight, width);
        int direction = get_direction();
        not_escape = (direction != ESCAPE);
        if (not_escape) {
            movement(direction, hero, field, hight, width);
            system("cls");
        }
    }

    return 0;
}





void corect_coordinates(point& p, int hight, int width){
    if (p.X == -1) p.X = width-1;
    if (p.X == width) p.X = 0;

    if (p.Y == -1) p.Y = hight-1;
    if (p.Y == hight) p.Y = 0;
}

bool check(int  ** step_field, int hight, int width, point p){
    corect_coordinates(p, hight, width);
    if (step_field[p.Y][p.X] == INFINITY )
        return true;
    else
        return false;

}

char get_direction(){
    int i = getch();

    if (i == 224) {
        i = getch();
        switch (i) {
            case 72:
                return 'W';
                break;

            case 80:
                return 'S';
                break;

            case 75:
                return 'A';
                break;

            case 77:
                return 'D';
                break;

            default:
                break;
        }
    }
    else{
      return toupper(i);
    }


}






void check_move(point& old_rotate, point new_rotate, char **field, int hight, int width){

    // ОБРАБОТКА ВЫХОДА ЗА ГРАНИЦУ КАРТЫ
    corect_coordinates(new_rotate, hight, width);

    if (field[new_rotate.Y][new_rotate.X] == '_'){
        field[new_rotate.Y][new_rotate.X] = '!';
        field[old_rotate.Y][old_rotate.X] = '_';
        old_rotate = new_rotate;
    }
}
void movement(int& direction, point& hero, char **field, int hight, int width){
    switch (direction) {
        case KEY_LEFT:
            check_move(hero, {hero.Y, hero.X - 1}, field, hight, width);
            break;

        case KEY_RIGHT:
            check_move(hero, {hero.Y, hero.X + 1}, field, hight, width);
            break;

        case KEY_UP:
            check_move(hero, {hero.Y - 1, hero.X}, field, hight, width);
            break;

        case KEY_DOWN:
            check_move(hero, {hero.Y + 1, hero.X}, field, hight, width);
            break;

        default:
            break;
    }
}

void print_field(char **field, int hight, int width){
    for (int i = 0; i < hight; i++){
        cout << endl;
        for (int j = 0; j < width; j++){
            cout << field[i][j];
        }
    }
}

void print_field(int **massive, int hight, int width){
    for (int i = 0; i < hight; i++){
        cout << endl;
        for (int j = 0; j < width; j++){
            cout << massive[i][j];
        }
    }
}

void Lee_algorithm(int ** step_field, char ** field, queue<point>& call_queue, int hight, int width, int weawe_count){


    int count = call_queue.size();

    while (count != 0) {


        // КООРДИНАТЫ РАССМАТРИВАЕМОГО ЯДРА
        int x = call_queue.front().X;
        int y = call_queue.front().Y;
        point p;

        p = {y-1, x};
        if (check(step_field, hight, width, p) == true) {
            corect_coordinates(p, hight, width);
            call_queue.push(p);
            step_field[p.Y][p.X] = weawe_count;
        }

        p = {y+1, x};
        if (check(step_field, hight, width, p) == true) {
            corect_coordinates(p, hight, width);
            call_queue.push(p);
            step_field[p.Y][p.X] = weawe_count;
        }

        p = {y, x-1};
        if (check(step_field, hight, width, p) == true) {
            corect_coordinates(p, hight, width);
            call_queue.push(p);
            step_field[p.Y][p.X] = weawe_count;
        }

        p = {y, x+1};
        if (check(step_field, hight, width, p) == true) {
            corect_coordinates(p, hight, width);
            call_queue.push(p);
            step_field[p.Y][p.X] = weawe_count;
        }

        call_queue.pop();
        count--;
    }

    if (!call_queue.empty()){
        Lee_algorithm(step_field, field, call_queue, hight, width, weawe_count+1);
    }


}