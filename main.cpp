#include <iostream>
#include <fstream>
using namespace std;

const int hight = 4;
const int width = 4;

void movement(char& );

struct character{
    int X;
    int Y;
};


int main() {
    ifstream cin("input.txt");
    char field[hight][hight];
    int i, j;
    character hero = {1,1};

    // ЗАПОЛНЕНИЕ МАССИВА
    for (i = 0; i < hight; i++){
        for (j = 0; j < width; j++){
            cin >> field[i][j];
        }
    }

    // СЧИТЫВАНИЕ ПЕРЕДВИЖЕНИЙ
    while (true){
        char direction;
        cin >> direction;
        system("cls");
        print_field();
    }


    return 0;
}


void movement(char& direction, character hero){
    switch (direction){
        case 'A':
            if (check(hero.X-1, hero.Y)){

            }

            break;
        case 'B':
            break;
        case 'C':
            break;
        case 'D':
            break;

    }

}