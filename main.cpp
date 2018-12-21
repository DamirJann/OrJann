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

struct character{
    int Y;
    int X;
};
void check(character&, character, char**);
void movement(char&, character&, char **);
void print_field(char **);


int main() {
    ifstream cin_file("input.txt");
    int i, j;
    character hero = {0,0};

    // СОЗДАНИЕ ДВУМЕРНОГО МАССИВА
    char **field = new char* [hight];
    for (i = 0; i < hight; i++){
        field[i] = new char [width];
    }

    // ЗАПОЛНЕНИЕ МАССИВАd
    for (i = 0; i < hight; i++){
        for (j = 0; j < width; j++){
            cin_file >> field[i][j];
        }
    }


    // СЧИТЫВАНИЕ ПЕРЕДВИЖЕНИЙ
    while (true){
        char direction;

        print_field(field);
        direction = toupper(getch());
        //cin >> direction;
        movement(direction, hero, field);
        system("cls");
        //cout << endl << endl;

    }


    return 0;
}


void check(character& old_rotate, character new_rotate, char **field){

    if ((new_rotate.X >= 0) && (new_rotate.X < width) && (new_rotate.Y >= 0) && (new_rotate.Y < hight) && (field[new_rotate.Y][new_rotate.X] == '_')){
        field[new_rotate.Y][new_rotate.X] = '!';
        field[old_rotate.Y][old_rotate.X] = '_';
        old_rotate = new_rotate;

    }
}
void movement(char& direction, character& hero, char **field){
    switch (direction) {
        case KEY_LEFT:
            check(hero, {hero.Y, hero.X - 1}, field);
            break;

        case KEY_RIGHT:
            check(hero, {hero.Y, hero.X + 1}, field);
            break;

        case KEY_UP:
            check(hero, {hero.Y - 1, hero.X}, field);
            break;

        case KEY_DOWN:
            check(hero, {hero.Y + 1, hero.X}, field);
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