#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

const int hight = 4;
const int width = 4;


struct character{
    int X;
    int Y;
};
bool check(int X, int Y, char**);
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

    // ЗАПОЛНЕНИЕ МАССИВА
    for (i = 0; i < hight; i++){
        for (j = 0; j < width; j++){
            cin_file >> field[i][j];
        }
    }


    // СЧИТЫВАНИЕ ПЕРЕДВИЖЕНИЙ
    while (true){
        char direction;
        cin >> direction;
        movement(direction, hero, field);
        system("cls");
        print_field(field);
        //cout << endl << endl;

    }


    return 0;
}


bool check(int Y, int X, char **field){
    if ((X < 0) || (X >= width) || (Y < 0) || (Y >= hight) || (field[Y][X] != '_')){
        return false;
    }
    else{
        return true;
    }
}
void movement(char& direction, character& hero, char **field){
    switch (direction){
        case 'a':
            if (check(hero.Y, hero.X-1, field)){
                field[hero.Y][hero.X] = '_';
                field[hero.Y][hero.X-1] = '!';
                hero.X--;
            }
            break;

        case 'd':
            if (check(hero.Y, hero.X+1, field)){
                field[hero.Y][hero.X] = '_';
                field[hero.Y][hero.X+1] = '!';
                hero.X++;
            }
            break;

        case 'w':
            if (check(hero.Y-1, hero.X, field)){
                field[hero.Y][hero.X] = '_';
                field[hero.Y-1][hero.X] = '!';
                hero.Y--;
            }
            break;

        case 's':
            if (check(hero.Y+1, hero.X, field)){
                field[hero.Y][hero.X] = '_';
                field[hero.Y+1][hero.X] = '!';
                hero.Y++;
            }
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