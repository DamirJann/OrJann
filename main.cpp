#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
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
bool check_move(point&, point, char**, int, int);
bool movement(int&, point&, char **, int, int);

void print_field(char **, int, int);
void print_field(int **, int, int);

char get_direction();

void Lee_algorithm(int **, char **, queue<point>&, int, int, int);

bool new_level(int&, int); // Создаёт новую карту, также возвращает false, если была нажата кнопка ESCAPE



int main() {

    int score = 0;
    int level_number = 1;
    while (new_level(score, level_number)){
        level_number++;
    }
    return 0;
}



bool new_level(int& score, int level_number) {
    ifstream cin_file("score.txt");
    int i, j;
    int best_score;
    int hight = 20, width = 20;

    point hero,
            destination_point,
            start_point;
    int hero_steps = 0;

    // УЗНАЕМ ЛУЧШИЙ СЧЁТ И ЗАКРЫВАЕМ ПОТОК
    cin_file >> best_score;
    cin_file.close();


    cout << "The level is loading" << endl;
    // СОЗДАНИЕ ДВУМЕРНОГО МАССИВА КАРТЫ И КОЛИЧЕСТВА ШАГОВ ДО КЛЕТОК
    char **field = new char* [hight];
    int **step_field = new int* [hight];
    for (i = 0; i < hight; i++){
        field[i] = new char [width];
        step_field[i] = new int [width];
    }
    srand(time(NULL));

    // ЗАПОЛНЕНИЕ МАССИВА
    for (i = 0; i < hight; i++){
        //srand(time(NULL));
        for (j = 0; j < width; j++){
            // С ВЕРОЯТНОСТЬЮ 1/3 СТАВИТСЯ '#'
            //srand(time(NULL));
            if (rand()%9 < 4){
                field[i][j] = '#';
            }
            else{
                field[i][j] = '_';
            }
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

    // ПОИСК МЕСТА ДЛЯ ПЕРСОНАЖА
    bool flag = true;
    while (flag){
        srand(time(NULL));
        int x = rand()%width;
        int y = rand()%hight;
        if (field[y][x] == '_'){
            field[y][x] = '!';
            step_field[y][x] = 0;
            flag = false;
            hero = {y, x};
            start_point = hero;
        }
    }

    // ЗАПУСК АЛГОРИТМА ЛИ и объявление вектора вызовов
    queue<point> call_queue;
    call_queue.push(hero);
    Lee_algorithm(step_field, field, call_queue, hight, width, 1);
    //print_field(step_field, hight, width);

    // ПОИСК МЕСТА ДЛЯ КЛАДА

    flag = true;
    while (flag){
        srand(time(NULL));
        int x = rand()%width;
        srand(time(NULL));
        int y = rand()%hight;
        if ((field[y][x] == '_') && (step_field[y][x] != INFINITY)){
            field[y][x] = 'X';
            flag = false;
            destination_point = {y, x};
        }
    }

    system("cls");

    // СЧИТЫВАНИЕ ПЕРЕДВИЖЕНИЙ
    bool not_escape = true;
    bool not_destination = true;
    while(not_escape && not_destination){

        // ВЫВОДИМ ТЕКУЩИЙ И ЛУЧШИЙ СЧЁТ
        cout << "Your score is " << score << endl;
        cout << "The best score " << best_score << endl;
        cout << "Level " << level_number << endl;
        if (score > best_score) {
            best_score = score;
        }

        // ВЫВОДИМ СОСТОЯНИЕ КАРТЫ НА ТЕКУЩИЙ МОМЕНТ
        print_field(field, hight, width);
        int direction = get_direction();
        not_escape = (direction != ESCAPE);
        if (not_escape) {
            if (movement(direction, hero, field, hight, width)){
                hero_steps++;
            }
            system("cls");
        }
        if ((hero.X == destination_point.X) && (hero.Y == destination_point.Y)){
            cout << "The best way containe - " << step_field[destination_point.Y][destination_point.X] << " steps" << endl;
            cout << "You did - " << hero_steps << " steps" << endl;
            not_destination = false;
            score+= step_field[destination_point.Y][destination_point.X] - hero_steps + 10;

        }
    }
    field[start_point.Y][start_point.X] = '0';
    print_field(field, hight, width);

    ofstream cout_file("score.txt");
    cout_file << best_score;
    cout_file.close();
    system("pause");
    return not_escape;
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





// ГОВОРИТ БЫЛО ЛИ ПЕРЕМЕЩЕНИЕ, ЕСЛИ ДА, ТО ОТМЕЧАЕТ ЕГО НА КАРТЕ
bool check_move(point& old_rotate, point new_rotate, char **field, int hight, int width){

    // ОБРАБОТКА ВЫХОДА ЗА ГРАНИЦУ КАРТЫ
    corect_coordinates(new_rotate, hight, width);

    if (field[new_rotate.Y][new_rotate.X] != '#'){
        field[new_rotate.Y][new_rotate.X] = '!';
        field[old_rotate.Y][old_rotate.X] = '_';
        old_rotate = new_rotate;
        return true;
    }
    return false;
}
bool movement(int& direction, point& hero, char **field, int hight, int width){
    bool was_movement = false;
    switch (direction) {
        case KEY_LEFT:
            was_movement = check_move(hero, {hero.Y, hero.X - 1}, field, hight, width);
            break;

        case KEY_RIGHT:
            was_movement = check_move(hero, {hero.Y, hero.X + 1}, field, hight, width);
            break;

        case KEY_UP:
            was_movement = check_move(hero, {hero.Y - 1, hero.X}, field, hight, width);
            break;

        case KEY_DOWN:
            was_movement = check_move(hero, {hero.Y + 1, hero.X}, field, hight, width);
            break;
        default:
            break;
    }
    return was_movement;
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