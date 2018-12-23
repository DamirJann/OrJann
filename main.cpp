#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int hight = 10;
const int width = 10;

#define KEY_UP 'W'
#define KEY_DOWN 'S'
#define KEY_LEFT 'A'
#define KEY_RIGHT 'D'
#define ESCAPE 27


struct character{
    int Y;
    int X;
};
void check_move(character&, character, char**);
void movement(int&, character&, char **);
void print_field(char **);
char get_direction();


int main() {
    ifstream cin_file("input.txt");
    ofstream cout_file("output.txt");
    int i, j;
    character hero = {0,0};
    // СОЗДАНИЕ ДВУМЕРНОГО МАССИВА
    char **field = new char* [hight];
    for (i = 0; i < hight; i++){
        field[i] = new char [width];
    }

    // ЗАПОЛНЕНИЕ МАССИВА
    for (i = 0; i < hight; i++){
        for (j = 0; j < width; j++){
            cin_file >> field[i][j];
        }
    }
    // СЧИТЫВАНИЕ ПЕРЕДВИЖЕНИЙ
    bool not_escape = true;
    while(not_escape){
        print_field(field);
        int direction = get_direction();
        not_escape = (direction != ESCAPE);
        if (not_escape) {
            movement(direction, hero, field);
            system("cls");
        }
    }

    return 0;
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

void check_move(character& old_rotate, character new_rotate, char **field){

    // ОБРАБОТКА ВЫХОДА ЗА ГРАНИЦУ КАРТЫ
    switch (new_rotate.X){
        case -1:
            new_rotate.X = width - 1;
            break;
        case width:
            new_rotate.X = 0;
            break;
        default:
            break;
    }

    switch (new_rotate.Y){
        case -1:
            new_rotate.Y = hight - 1;
            break;
        case hight:
            new_rotate.Y = 0;
            break;
        default:
            break;
    }

    if (field[new_rotate.Y][new_rotate.X] == '_'){
        field[new_rotate.Y][new_rotate.X] = '!';
        field[old_rotate.Y][old_rotate.X] = '_';
        old_rotate = new_rotate;
    }
}
void movement(int& direction, character& hero, char **field){
    switch (direction) {
        case KEY_LEFT:
            check_move(hero, {hero.Y, hero.X - 1}, field);
            break;

        case KEY_RIGHT:
            check_move(hero, {hero.Y, hero.X + 1}, field);
            break;

        case KEY_UP:
            check_move(hero, {hero.Y - 1, hero.X}, field);
            break;

        case KEY_DOWN:
            check_move(hero, {hero.Y + 1, hero.X}, field);
            break;

        default:
            break;
    }
}

void print_field(char **field){
    for (int i = 0; i < hight; i++){
        cout << endl;
        for (int j = 0; j < width; j++){
            cout << field[i][j];
        }
    }
}