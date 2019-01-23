#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <queue>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <vector>
using namespace std;



#define HORIZONTAL_WAY 205
#define VERTICAL_WAY 186
#define LEFT_DOWN_WAY 201
#define LEFT_UP_WAY 200
#define DOWN_LEFT_WAY 188
#define UP_LEFT_WAY 187
#define RIGHT_UP_WAY 188
#define RIGHT_DOWN_WAY 187
#define UP_RIGHT_WAY 201
#define DOWN_RIGHT_WAY 200





#define KEY_UP 'W'
#define KEY_DOWN 'S'
#define KEY_LEFT 'A'
#define KEY_RIGHT 'D'
#define ESCAPE 27
#define WALL 99999999
#define INFINITY 8888888



struct point{
    int Y;
    int X;

};


class object {
private:
    point rotation;
    int score, movement_count,
        healthbar, level_number;
    char direction = INFINITY;
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // КОНСТРУКТОР ИНИЦИАЛИЗАЦИИ
    object(): score(0), movement_count(0),
              healthbar(3), level_number(0),
              direction(INFINITY) {}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫДАЁТ СЧЁТ
    double  Get_score() const{
        return score;
     }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ОБНУЛЯЕТ СЧЁТЧИК ШАГОВ
    void Initializate_movement_count(){
        movement_count = 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ЗДОРОВЬЕ
    int Get_healthbar() const{
        return healthbar;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ НАПРАВЛЕНИЕ ДВИЖЕНИЯ
    char Get_direction() const{
        return direction;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ КОЛИЧЕСТВО СДЕЛАННЫХ ШАГОВ
    int Get_movement_count() const{
        return movement_count;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ КОЛИЧЕСТВО СДЕЛАННЫХ ШАГОВ
    void Inc_movement_count(){
        movement_count++;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНКРЕМЕНТИРУЕТ level_number
    void  Inc_level(){
        level_number++;
    }
    // ИНКРЕМЕНТИРУЕТ level_number
    void  Change_rotation(point new_rotation){
        rotation = new_rotation;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // УБИРАЕТ ОДНУ ЖИЗНЬ
    void  Dec_health(){
        healthbar--;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ level_number
    int  Get_level_number() const{
        return level_number;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ПОЛОСКУ ЖИЗНИ
    string  Print_healthbar() const{
        string result("");
        for (int i = 0; i < healthbar; i++){
            result += '*';
        }
        return result;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕНЯЕТ СЧЁТ
    void Change_score(int best_way){
      score += (best_way-movement_count)*1.10141211646546+2*1.46741346546515156487;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ МЕСТОПОЛОЖЕНИЕ ИГРОКА
    point Get_rotation() const{
        return rotation;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


class level{
private:
    int hight, width;
    vector<vector<char>> map;
    vector<vector<int>> distance_map;
    point destination;

public:
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗИРУЮЩИЙ КОНСТРУКТОР
    level(): destination({INFINITY, INFINITY}),
             map({}), distance_map({}) {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ПРОКЛАДЫВАЕТ НАИЛУЧШЙ МАРШРУТ
    bool Mark_point_in_direction(point old_coordinate,point new_coordinate, const object hero){

        Correct_coordinates(new_coordinate);

        if (distance_map[old_coordinate.Y][old_coordinate.X]-1 == distance_map[new_coordinate.Y][new_coordinate.X]){

            Pave_direction(new_coordinate, hero);
            return true;
        }
        return false;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ПРОВЕРЯЕТ, СТОИТ ЛИ ЭТОТ sign В ПОЗИЦИИ point
    bool Is_this_sign(point coordinate) const{
        return ((map[coordinate.Y][coordinate.X] != '_') && (map[coordinate.Y][coordinate.X] != '#'));
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ПРОЛОЖИТЬ НАИЛУЧШИЙ МАРШРУТ
    void Pave_direction(point old_coordinate, const object hero){

        map[old_coordinate.Y][old_coordinate.X] = '+';

        // ЛИШЬ ОДНА КЛЕТКА БУДЕТ ОТМЕЧЕНА
        if (Mark_point_in_direction(old_coordinate, {old_coordinate.Y+1, old_coordinate.X}, hero));
            else
        if (Mark_point_in_direction(old_coordinate, {old_coordinate.Y-1, old_coordinate.X}, hero));
            else
        if (Mark_point_in_direction(old_coordinate, {old_coordinate.Y, old_coordinate.X+1}, hero));
            else
        if (Mark_point_in_direction(old_coordinate, {old_coordinate.Y, old_coordinate.X-1}, hero));

        if (distance_map[old_coordinate.Y][old_coordinate.X] == 0){

            for (int i = 0; i < hight; i++){
                for (int j = 0; j < width; j++){
                    if (map[i][j] == '+') {


                        map[old_coordinate.Y][old_coordinate.X] = 'S';
                        map[destination.Y][destination.X] = 'F';

                        if (Is_this_sign(Get_correct_coordinates({i-1, j})) && Is_this_sign(Get_correct_coordinates({i+1, j}))){
                            map[i][j] = VERTICAL_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i, j-1})) && Is_this_sign(Get_correct_coordinates({i, j+1}))){
                            map[i][j] = HORIZONTAL_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i, j+1})) && Is_this_sign(Get_correct_coordinates({i+1, j}))) {
                            map[i][j] = LEFT_DOWN_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i, j+1})) && Is_this_sign(Get_correct_coordinates({i-1, j}))){
                            map[i][j] = LEFT_UP_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i-1, j})) && Is_this_sign(Get_correct_coordinates({i+1, j}))){
                            map[i][j] = DOWN_LEFT_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i+1, j})) && Is_this_sign(Get_correct_coordinates({i-1, j}))){
                            map[i][j] = UP_LEFT_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i, j-1})) && Is_this_sign(Get_correct_coordinates({i-1, j}))){
                            map[i][j] = RIGHT_UP_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i, j-1})) && Is_this_sign(Get_correct_coordinates({i+1, j}))) {
                            map[i][j] = RIGHT_DOWN_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i+1, j})) && Is_this_sign(Get_correct_coordinates({i-1, j}))){
                            map[i][j] = UP_RIGHT_WAY;
                        } else
                        if (Is_this_sign(Get_correct_coordinates({i-1, j})) && Is_this_sign(Get_correct_coordinates({i+1, j}))){
                            map[i][j] = DOWN_RIGHT_WAY;
                        }







                    }

                }
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ПОЛУЧИТЬ РЕЗУЛЬТАТЫ
    int  Get_the_best_way() const{
        return distance_map[destination.Y][destination.X];
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ШИРИНУ КАРТЫ
    int  Get_width() const{
        return width;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ШИРИНУ КАРТЫ
    int  Get_hight() const{
        return hight;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ПОЛОЖЕНИЕ КЛАДА
    point Get_destination() const{
        return destination;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // БЫЛО ЛИ ПЕРЕДВИЖЕНИЕ, ЕСЛИ ДА ТО ОНО ВЫПОЛНЯЕТСЯ. В ДРУГОМ СЛУЧАЧЕ ОТНИМАЕТ ЖИЗНБ
    bool Was_movement(object& hero) {
        bool was_movement = false;
        switch (hero.Get_direction()) {
            case KEY_LEFT:
                was_movement = Check_move({hero.Get_rotation().Y, hero.Get_rotation().X - 1}, hero);
                break;

            case KEY_RIGHT:
                was_movement = Check_move({hero.Get_rotation().Y, hero.Get_rotation().X + 1}, hero);
                break;

            case KEY_UP:
                was_movement = Check_move({hero.Get_rotation().Y - 1, hero.Get_rotation().X}, hero);
                break;

            case KEY_DOWN:
                was_movement = Check_move({hero.Get_rotation().Y + 1, hero.Get_rotation().X}, hero);
                break;
            default:
                break;
        }
        return was_movement;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫПОЛНЯЕТ ПЕРЕДВИЖЕНИЕ
    bool Check_move(point new_rotate, object& hero){

        // ОБРАБОТКА ВЫХОДА ЗА ГРАНИЦУ КАРТЫ
        Correct_coordinates(new_rotate);

        if (map[new_rotate.Y][new_rotate.X] != '#'){
            map[new_rotate.Y][new_rotate.X] = '!';
            map[hero.Get_rotation().Y][hero.Get_rotation().X] = '_';
            hero.Change_rotation({new_rotate.Y, new_rotate.X});
            return true;
        }
        return false;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ РАСПЛОЖЕНИЯ КЛАДА
    void Init_destination(const object hero){
        bool flag = true;
        while (flag){
            srand(time(NULL));
            int x = rand() % width;
            int y = rand() % hight;
            if ((distance_map[y][x] != WALL) && (distance_map[y][x] != INFINITY) && (x != hero.Get_rotation().X || y != hero.Get_rotation().Y)) {
                map[y][x] = 'X';
                flag = false;
                destination = {y, x};
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ РАСПЛОЖЕНИЯ ИГРОКА
    void Init_hero(object& hero) {
        bool flag = true;
        while (flag) {
            srand(time(NULL));
            int x = rand() % width;
            int y = rand() % hight;
            if (map[y][x] == '_') {
                map[y][x] = '!';
                distance_map[y][x] = 0;
                flag = false;
                hero.Change_rotation({y, x});
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // АЛГОРИТМ ЛИ
    void Lee_algorithm(int weawe_count, queue<point>* call_queue, const object hero){

        if (weawe_count == 0){
            call_queue = new(queue<point>);
            call_queue->push({hero.Get_rotation().Y, hero.Get_rotation().X});
        }

        int count = call_queue->size();


        while (count != 0){

            // КООРДИНАТЫ РАССМАТРИВАЕМОГО ЯДРА
            int x = call_queue->front().X;
            int y = call_queue->front().Y;
            point p;

            distance_map[y][x] = min(weawe_count, distance_map[y][x]);

            p = {y - 1, x};
            if (Is_correct_coordinates(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            p = {y + 1, x};
            if (Is_correct_coordinates(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            p = {y, x - 1};
            if (Is_correct_coordinates(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            p = {y, x + 1};
            if (Is_correct_coordinates(p) == true) {
                Correct_coordinates(p);
                call_queue->push(p);
            }

            call_queue->pop();
            count--;
        }

        if (!call_queue->empty()) {
            Lee_algorithm(weawe_count + 1, call_queue, hero);
        }

        if (weawe_count == 0){
            delete call_queue;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕТОД ВОЗРАЩАЕТ FALSE, ЕСЛИ КООРДИНАТЫ НЕКОРРЕКТНЫ.
    bool Is_correct_coordinates(point p){
        Correct_coordinates(p);
        if (distance_map[p.Y][p.X] == INFINITY)
            return true;
        else
            return false;

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕНЯЕТ КООРДИНАТЫ, ЕСЛИ ОНИ НЕКОРРЕКТНЫ.
    void Correct_coordinates(point& p){
        if (p.X == -1) p.X = width-1;
        if (p.X == width) p.X = 0;

        if (p.Y == -1) p.Y = hight-1;
        if (p.Y == hight) p.Y = 0;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ИСПРАВЛЕННЫЕ КООРДИНАТЫ, ЕСЛИ ОНИ НЕКОРРЕКТНЫ.
    point Get_correct_coordinates(point p){
        if (p.X == -1) p.X = width-1;
        if (p.X == width) p.X = 0;

        if (p.Y == -1) p.Y = hight-1;
        if (p.Y == hight) p.Y = 0;

        return p;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // СОЗДАНИЕ map
    void Create_map(int hight, int width){

        this->hight = hight;
        this->width = width;

        map.resize(hight);
        for (int i = 0; i < hight; i++){
            map[i].resize(width);
        }

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // СОЗДАНИЕ И ИНИЦИАЛИЗИРОВАНИЕ distance_map
    void Create_distance_map(){

        distance_map.resize(hight);
        for (int i = 0; i < hight; i++){
            distance_map[i].resize(width);
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
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ ЛАБИРИНТА ДВОИЧНЫМ СПОСОБОМ
    void Fill_bineary_maze() {

        int i, j,
                direction;
        srand(time(NULL));
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
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ ЛАБИРИНТА С ПОМОЩЬЮ SIDEWINDER
    void Fill_sidewinder_maze() {

        int i, j;
        bool carve;

        srand(time(NULL));

        for (i = 0; i < hight; i++) {
            for (j = 0; j < width; j++) {
                map[i][j] = '#';
            }
        }


        for (i = 0; i < hight; i++){
            vector<point> cells = {{i, 0}};
            int set_start = 0;
            int a;
            while (cells[cells.size()-1].X + 1 != width){

                if (rand()%2 == 1){
                    map[cells[cells.size()-1].Y][cells[cells.size()-1].X + 1] = '_';
                    cells.push_back({cells[cells.size()-1].Y, cells[cells.size()-1].X + 1});
                }
                else{
                    int tmp = set_start + rand() % (cells.size()-set_start);
                    if (cells[tmp].Y != 0){
                        map[cells[tmp].Y-1][cells[tmp].X] = '_';
                    }
                    cells.push_back({cells[cells.size()-1].Y, cells[cells.size()-1].X + 1});
                }
                set_start++;
            }
        }



    }



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫВОД КАРТЫ
    void  Print_map() {
        for (int i = 0; i < hight; i++) {
            cout << endl;
            for (int j = 0; j < width; j++) {
                cout << map[i][j];
            }
        }
        cout << endl;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
};









int main() {

    bool not_escape = true;

    object hero; // ОБЪЕКТ ПЕРСОНАЖ
    double best_score = 0,
           old_score = 0;

    int level_size_w = 7,
        level_size_h = 5;
    // ОТКРЫВАЕМ ПОТОК, СЧИТЫВАЕМ ЛУЧШИЙ СЧЁТ, ЗАКРЫВАЕМ ЕГО
    ifstream cin_score("score.txt");
    cin_score >> best_score;
    cin_score.close();

    while(not_escape && (hero.Get_healthbar() != 0)) {

        cout << "Level is loading...";
        level new_level;
        if (hero.Get_level_number() % 3 == 0) level_size_h += 3;
        if (hero.Get_level_number() % 2 == 0) level_size_w += 3;


        new_level.Create_map(level_size_h, level_size_w);
        new_level.Fill_sidewinder_maze();
        new_level.Create_distance_map();
        new_level.Init_hero(hero);
        new_level.Lee_algorithm(0, NULL, hero);
        new_level.Init_destination(hero);
        hero.Inc_level();
        hero.Initializate_movement_count();
        system("cls");

        while ((not_escape) && (hero.Get_healthbar() != 0) && ((hero.Get_rotation().Y != new_level.Get_destination().Y) ||
                                                               (hero.Get_rotation().X != new_level.Get_destination().X))){
            cout << "Level " << hero.Get_level_number() << endl;
            cout << "Your score is " << setprecision(3) << setw(3) << fixed <<setfill('0') << left << hero.Get_score()
                              << " (" << showpos << setprecision(3) << setw(3) << fixed << setfill('0') << left  << hero.Get_score() - old_score << " - for last level)" << endl << noshowpos;
            cout << "The best score " << best_score << endl;
            cout << "You did " << hero.Get_movement_count() << " steps" << endl;
            cout << "The best way containe " << new_level.Get_the_best_way() << " steps"  << endl;
            cout << "Life: " << hero.Print_healthbar() << endl;
            new_level.Print_map();

            hero.Read_direction();
            not_escape = (hero.Get_direction() != ESCAPE);
            if (new_level.Was_movement(hero)) {
                hero.Inc_movement_count();
            }
            else{
                hero.Dec_health();
            }

            system("cls");
        }

        new_level.Pave_direction({new_level.Get_destination().Y, new_level.Get_destination().X}, hero);
        new_level.Print_map();
        cout << endl;
        //cout << "\nTo move on to the next level press any kye"<< endl;
        system("pause");
        system("cls");

         old_score = hero.Get_score(); // Запоминаем старое значение.

         hero.Change_score(new_level.Get_the_best_way());
         if (hero.Get_score() > best_score){
             best_score = hero.Get_score();
         }


    }


    if (hero.Get_healthbar() == 0){
        cout << "You are dead" << endl;
        for (int i = 0; i < 25; i++){
            cout << '-';
        }
        cout << endl;
    }

    cout << "You passed " << hero.Get_level_number() << " levels" << endl;
    cout << "Your score is " << hero.Get_score() << endl;
    cout << "The best score is "  << best_score << endl;
    cout << '\n';
    ofstream cout_score("score.txt");
    cout_score << best_score;
    cout_score.close();
    system("pause");
    return 0;
}
