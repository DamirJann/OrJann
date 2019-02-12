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
#include <random>
#include <cstdlib>
using namespace std;

char HERO_CHAR('!');

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
#define WALL_CHAR '#'
#define BUSH_CHAR ' '
#define SPACE_CHAR '_'
#define DESTINATION_CHAR 'O'


#define ESCAPE 27
#define ENTER 13

#define WALL 999999
#define INFINITY 888888

void Print_text_between_lines(string text){
    for (int i = 0; i < text.size(); i++){
        cout << '-';
    }
    cout << endl << text << endl;
    for (int i = 0; i < text.size(); i++){
        cout << '-';
    }
    cout << endl;
}

struct point{
    int Y;
    int X;

};


char Read_direction(){
    char tmp_direction;
    int i = getch();
    if (i == 224) {
        i = getch();
        switch (i)
        {
            case 72:
                tmp_direction = 'W';
                break;
            case 80:
                tmp_direction = 'S';
                break;
            case 75:
                tmp_direction = 'A';
                break;
            case 77:
                tmp_direction = 'D';
                break;
            default:
                break;
        }
    } else {

        i = toupper(i);
        switch(i){
            case 'Ф':
                i = 'A';
            case 'В':
                i = 'D';
            case 'Ц':
                i = 'W';
            case 'Ч':
                i = 'X';
        }
        tmp_direction = i;
    }

    return tmp_direction;
}


class object {
private:
    point rotation;
    double score;
    int movement_count, healthbar, level_number;
    char direction = INFINITY;
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // КОНСТРУКТОР ИНИЦИАЛИЗАЦИИ
    object() : score(0), movement_count(0),
               healthbar(3), level_number(0),
               direction(INFINITY) {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЫДАЁТ СЧЁТ
    double Get_score() const {
        return score;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ОБНУЛЯЕТ СЧЁТЧИК ШАГОВ
    void Initializate_movement_count() {
        movement_count = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ЗДОРОВЬЕ
    int Get_healthbar() const {
        return healthbar;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ НАПРАВЛЕНИЕ ДВИЖЕНИЯ
    char Get_direction() const {
        return direction;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ КОЛИЧЕСТВО СДЕЛАННЫХ ШАГОВ
    int Get_movement_count() const {
        return movement_count;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ КОЛИЧЕСТВО СДЕЛАННЫХ ШАГОВ
    void Inc_movement_count() {
        movement_count++;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНКРЕМЕНТИРУЕТ level_number
    void Inc_level() {
        level_number++;
    }

    // ИНКРЕМЕНТИРУЕТ level_number
    void Change_rotation(point new_rotation) {
        rotation = new_rotation;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // УБИРАЕТ ОДНУ ЖИЗНЬ
    void Dec_health() {
        healthbar--;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ level_number
    int Get_level_number() const {
        return level_number;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ ПОЛОСКУ ЖИЗНИ
    string Print_healthbar() const {
        string result("");
        for (int i = 0; i < healthbar; i++) {
            result += '*';
        }
        return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МЕНЯЕТ СЧЁТ
    void Change_score(int best_way) {
        score += ((best_way - movement_count)*1.956132145 + level_number * 0.1074645546) * 1.10141211646546 +
                 2 * 1.46741346546515156487;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВОЗВРАЩАЕТ МЕСТОПОЛОЖЕНИЕ ИГРОКА
    point Get_rotation() const {
        return rotation;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ПРИСВАИВАЕТ ЗНАЧЕНИЕ direction, вызывая Read_direction
    void Init_direction() {
        direction = Read_direction();
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
        return ((map[coordinate.Y][coordinate.X] != SPACE_CHAR) && (map[coordinate.Y][coordinate.X] != WALL_CHAR) && (map[coordinate.Y][coordinate.X] != BUSH_CHAR));
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

            map[old_coordinate.Y][old_coordinate.X] = 'S';
            map[destination.Y][destination.X] = 'F';

            for (int i = 0; i < hight; i++){
                for (int j = 0; j < width; j++){
                    if (map[i][j] == '+') {

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

        if (map[new_rotate.Y][new_rotate.X] != WALL_CHAR){

            if (map[new_rotate.Y][new_rotate.X] != BUSH_CHAR){
                map[new_rotate.Y][new_rotate.X] = HERO_CHAR;
            }

            if (map[hero.Get_rotation().Y][hero.Get_rotation().X] != BUSH_CHAR){
                map[hero.Get_rotation().Y][hero.Get_rotation().X] = SPACE_CHAR;
            }
            hero.Change_rotation({new_rotate.Y, new_rotate.X});
            return true;
        }
        return false;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ РАСПЛОЖЕНИЯ КЛАДА
    void Init_destination(const object hero){
        int count = 0, max_distance = -1;
        while (count != 40) {

            int x = rand() % width;
            int y = rand() % hight;

            if ((distance_map[y][x] != WALL) && (distance_map[y][x] != INFINITY) && (x != hero.Get_rotation().X || y != hero.Get_rotation().Y)) {
                count++;
                if (distance_map[y][x] > max_distance) {
                    destination = {y, x};
                    max_distance = distance_map[y][x];
                }
            }
        }

        map[destination.Y][destination.X] = DESTINATION_CHAR;


    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ РАСПЛОЖЕНИЯ ИГРОКА
    void Init_hero(object& hero) {
        bool flag = true;
        while (flag) {
            int x = rand() % width;
            int y = rand() % hight;
            if (map[y][x] == SPACE_CHAR) {
                map[y][x] = HERO_CHAR;
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
            if (distance_map[y][x] == INFINITY) exit(228);
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
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // СОЗДАНИЕ КУСТВОВ
    void Create_bushes(int count, point bush){

        map[bush.Y][bush.X] = BUSH_CHAR;

        if (count == 0){
            return;
        }
        else{

            bool is_near(false);

            if ((map[Get_correct_coordinates({bush.Y-1, bush.X}).Y][Get_correct_coordinates({bush.Y-1, bush.X}).X] == SPACE_CHAR) && ((rand()%100) <10)){
                bush = Get_correct_coordinates({bush.Y-1, bush.X});
                is_near = true;
            }
            else if ((map[Get_correct_coordinates({bush.Y+1, bush.X}).Y][Get_correct_coordinates({bush.Y+1, bush.X}).X] == SPACE_CHAR) && ((rand()%100) < 20)){
                bush = Get_correct_coordinates({bush.Y+1, bush.X});
                is_near = true;
            }
            else if ((map[Get_correct_coordinates({bush.Y, bush.X+1}).Y][Get_correct_coordinates({bush.Y, bush.X+1}).X] == SPACE_CHAR) && ((rand()%100) < 30)){
                bush = Get_correct_coordinates({bush.Y, bush.X+1});
                is_near = true;
            }
            else if ((map[Get_correct_coordinates({bush.Y, bush.X-1}).Y][Get_correct_coordinates({bush.Y, bush.X-1}).X] == SPACE_CHAR) && ((rand()%100) <40)){
                bush = Get_correct_coordinates({bush.Y+1, bush.X});
                is_near = true;
            }

            if (is_near == false){
                while (map[bush.Y][bush.X] != SPACE_CHAR) {
                    bush.Y = rand() % hight;
                    bush.X = rand() % width;
                }
            }

            Create_bushes(count-1, bush);
        }


    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
                    case WALL_CHAR:
                        distance_map[i][j] = WALL;
                        break;
                    case SPACE_CHAR:
                        distance_map[i][j] = INFINITY;
                        break;
                    case BUSH_CHAR:
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
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ ЛАБИРИНТА ДВОИЧНЫМ СПОСОБОМ
    void Fill_bineary_maze() {

        int i, j, direction;
        for (i = 0; i < hight; i++){
            for (j = 0; j < width; j++){
                map[i][j] = WALL_CHAR;
            }
        }
        for (j = 0; j < width; j++) {
            map[0][j] = SPACE_CHAR;
        }
        for (i = 0; i < hight; i++) {
            map[i][width-1] = SPACE_CHAR;
        }

        for (i = 1; i < hight; i++){
            for (j = 0; j < width - 1; j++){
                direction = rand() % 2;
                if (direction == 0){
                    map[i-1][j] = SPACE_CHAR;
                }
                else{
                    map[i][j+1] = SPACE_CHAR;
                }
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИНИЦИАЛИЗАЦИЯ ЛАБИРИНТА С ПОМОЩЬЮ SIDEWINDER
    void Fill_sidewinder_maze() {

        int i, j;
        bool carve;


        for (i = 0; i < hight; i++) {
            for (j = 0; j < width; j++) {
                map[i][j] = WALL_CHAR;
            }
        }


        for (i = 0; i < hight; i++){
            vector<point> cells = {{i, 0}};
            int set_start = 0;
            int a;
            while (cells[cells.size()-1].X + 1 != width){

                if (rand()% 2 == 1){
                    map[cells[cells.size()-1].Y][cells[cells.size()-1].X + 1] = SPACE_CHAR;
                    cells.push_back({cells[cells.size()-1].Y, cells[cells.size()-1].X + 1});
                }
                else{
                    int tmp = set_start + rand() % (cells.size()-set_start);
                    if (cells[tmp].Y != 0){
                        map[cells[tmp].Y-1][cells[tmp].X] = SPACE_CHAR;
                    }
                    cells.push_back({cells[cells.size()-1].Y, cells[cells.size()-1].X + 1});
                }
                set_start++;
            }
        }



    }



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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



class game{
private:
    int level_size_hight, level_size_width;
    double best_score, last_score, worse_score;
    bool not_escape, end_of_game;
    object hero;

public:
    game(): level_size_hight(5), level_size_width(7), last_score(0), not_escape(true), end_of_game(false) {
        ifstream cin_score("score.txt");
        cin_score >> best_score >> worse_score;
        cin_score.close();
    }

    void Launch_new_game(){

        while(not_escape && (hero.Get_healthbar() != 0) && (end_of_game == false)) {

            cout << "Level is loading...";
            level new_level;
            if (hero.Get_level_number() % 3 == 0) level_size_hight += 2;
            if (hero.Get_level_number() % 2 == 0) level_size_width += 5;


            new_level.Create_map(level_size_hight, level_size_width);
            new_level.Fill_sidewinder_maze();
            //new_level.Create_bushes(int(new_level.Get_hight()*new_level.Get_width()*0.21),{rand()%new_level.Get_hight(),rand()%new_level.Get_width()});
            new_level.Create_distance_map();
            new_level.Init_hero(hero);
            new_level.Lee_algorithm(0, NULL, hero);
            new_level.Init_destination(hero);
            hero.Inc_level();
            hero.Initializate_movement_count();
            system("cls");

            while ((not_escape) && (hero.Get_healthbar() != 0) &&((hero.Get_rotation().Y != new_level.Get_destination().Y) ||
                                                                   (hero.Get_rotation().X != new_level.Get_destination().X))){
                cout << "Level " << hero.Get_level_number() << "\n\n";
                cout << "Your score: " << setprecision(4) << setw(4) << fixed <<setfill('0') << left << hero.Get_score()
                     << " (" << showpos << setprecision(4) << setw(4) << fixed << setfill('0') << left  << hero.Get_score() - last_score << " - for last level)" << endl << noshowpos;
                cout << "The best score: " << best_score << endl;
                cout << "The worse score: " << worse_score << endl;
                cout << "You did: " << hero.Get_movement_count() << " steps" << endl;
                cout << "The best way: " << new_level.Get_the_best_way() << " steps"  << endl;
                cout << "Life: " << hero.Print_healthbar() << endl;
                new_level.Print_map();

                hero.Init_direction();
                not_escape = (hero.Get_direction() != ESCAPE);
                if (new_level.Was_movement(hero)) {
                    hero.Inc_movement_count();
                }
                else if ((hero.Get_direction() == 'A' ) || (hero.Get_direction() == 'D') ||
                         (hero.Get_direction() == 'S') || (hero.Get_direction() == 'W')){
                    hero.Dec_health();
                }

                system("cls");
            }


            last_score = hero.Get_score(); // Запоминаем старое значение.

            if ((hero.Get_healthbar() != 0) && (not_escape == true)){    // ЕСЛИ УРОВЕНЬ НЕ БЫЛ ПРЕЖДЕВРЕМЕННО ЗАВЕРШЁН И ПЕРСОНАЖ НЕ УМЕР, ТО МЕНЯЕМ СЧЁТ
                hero.Change_score(new_level.Get_the_best_way());
            }

            // ИЗМЕНЯЕМ МАКСИМАЛЬНЫЙ И МИНИМАЛЬНЫЙ СЧЁТ
            if (hero.Get_score() > best_score){
                best_score = hero.Get_score();
            }
            if (hero.Get_score() < worse_score){
                worse_score = hero.Get_score();
            }


            if (hero.Get_level_number() == 14){
                end_of_game = true;
            }

            if (hero.Get_healthbar() == 0 ){
                Print_text_between_lines("I Know, It's Over...");
            }
            else {
                if (not_escape == true && (end_of_game == false)) {
                    Print_text_between_lines("To move on to the next level press enter");
                }
                else{
                    Print_text_between_lines("To return to menu press enter");
                }
            }

            if (end_of_game == true) {
                cout << "You passed the game!!" << "\n\n";
            }
            cout << "Level " << hero.Get_level_number() << endl;
            cout << "Your score:" << setprecision(4) << setw(4) << fixed <<setfill('0') << left << hero.Get_score()
                 << " (" << showpos << setprecision(4) << setw(4) << fixed << setfill('0') << left  << hero.Get_score() - last_score << " - for this level)" << endl << noshowpos;
            cout << "The best score:" << best_score << endl;
            cout << "You did: " << hero.Get_movement_count() << " steps" << endl;
            cout << "The best way contains: " << new_level.Get_the_best_way() << " steps"  << endl;
            cout << "Life: " << hero.Print_healthbar() << endl;

            new_level.Pave_direction({new_level.Get_destination().Y, new_level.Get_destination().X}, hero);
            new_level.Print_map();
            cout << endl;
            if (hero.Get_healthbar() == 0 ){
                cout << endl;
                cout << "* Press enter to exit";
            }

            while (getch() != ENTER);
            system("cls");

        }


        ofstream cout_score("score.txt");
        cout_score << best_score << ' ' << worse_score;
        cout_score.close();
    }
};


class main_menu{

private:
    enum class MAIN_MENU  {NEW_GAME, HEROES, RESULTS, EXIT};
    enum class HERO_MENU{MAN_MANIFESTO, DIAMOND_DOG, YARDBIRD, CAPITALIST, BIRDMAN, BANKIR, BLUEBIRD, BACK_TO_MENU};
    enum class RESULT_MENU{RESET_SCORE, BACK_TO_MENU};
    enum class RESET_MENU{NO, YES};
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // КОНСТРУКТОР, ИНИЦИАЛИЗИРУЮЙИЙ HERO_CHAR
    main_menu(){
        HERO_MENU chosen_hero;
        ifstream cin_hero("hero.txt");
        char hero_id;
        cin_hero >> hero_id;
        chosen_hero = Get_hero_id(hero_id);
        Change_HERO_CHAR(chosen_hero);
        cin_hero.close();
        srand(time(NULL));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ДЕСТРУКТОР
    ~main_menu(){
        int hero_id;
        ifstream cin_hero("hero.txt");
        cin_hero >> hero_id;
        cin_hero.close();
        Get_hero_id(HERO_CHAR);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ЗАПУСКАЕТ ГЛАВНОЕ МЕНЮ
    void Launch_menu() {

        bool not_exit(true);
        MAIN_MENU chosen_elem(MAIN_MENU::NEW_GAME);
        while (not_exit) {

            Print_text_between_lines("OrJann");


            if (chosen_elem == MAIN_MENU::NEW_GAME) {
                cout << '~';
            }
            cout << "New game" << endl;

            if (chosen_elem == MAIN_MENU::HEROES) {
                cout << '~';
            }
            cout << "Heroes" << endl;


            if (chosen_elem == MAIN_MENU::RESULTS) {
                cout << '~';
            }
            cout << "Results" << endl;

            if (chosen_elem == MAIN_MENU::EXIT) {
                cout << '~';
            }
            cout << "Exit";


            char direction = Read_direction();

            system("cls");

            if (direction == 'W') {
                if (chosen_elem == MAIN_MENU::NEW_GAME){
                    chosen_elem = MAIN_MENU::EXIT;
                }
                else {
                    chosen_elem = static_cast<MAIN_MENU>(static_cast<int>(chosen_elem) - 1);
                }
            }


            if (direction == 'S') {
                if (chosen_elem == MAIN_MENU::EXIT){
                    chosen_elem = MAIN_MENU::NEW_GAME;
                }
                else {
                    chosen_elem = static_cast<MAIN_MENU>(static_cast<int>(chosen_elem) + 1);
                }
            }


            if (direction == ENTER) {
                switch (chosen_elem) {

                    case (MAIN_MENU::NEW_GAME):{
                        game new_game;
                        new_game.Launch_new_game();
                        break;
                    }
                    case (MAIN_MENU::HEROES):{
                        Launch_heroes_menu();
                        break;
                    }
                    case (MAIN_MENU::RESULTS):{
                        Launch_Results_menu();
                        break;
                    }
                    case (MAIN_MENU::EXIT):{
                        not_exit = false;
                    }

                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    void Launch_heroes_menu(){
        HERO_MENU chosen_hero(static_cast<HERO_MENU>(Get_hero_id(HERO_CHAR))),
                arrow(HERO_MENU::MAN_MANIFESTO);
        bool not_escape(true);
        char direction('8');

        while (direction != ESCAPE) {

            Print_text_between_lines("Heroes");

            if (arrow == HERO_MENU::MAN_MANIFESTO) cout << '~';

            cout << "Man-manifesto(!)";
            if (chosen_hero == HERO_MENU::MAN_MANIFESTO) cout << " <-";

            cout << endl;

            if (arrow == HERO_MENU::DIAMOND_DOG) cout << '~';
            cout << "Diamond dog(@)";

            if (chosen_hero == HERO_MENU::DIAMOND_DOG) cout << " <-";

            cout << endl;

            if (arrow == HERO_MENU::YARDBIRD) cout << '~';
            cout << "Yardbird(^)";

            if (chosen_hero == HERO_MENU::YARDBIRD) cout << " <-";

            cout << endl;


            if (arrow == HERO_MENU::CAPITALIST) cout << '~';
            cout << "Capitalist($)";

            if (chosen_hero == HERO_MENU::CAPITALIST) cout << " <-";

            cout << endl;


            if (arrow == HERO_MENU::BIRDMAN) cout << '~';
            cout << "Birdman(>)";

            if (chosen_hero == HERO_MENU::BIRDMAN) cout << " <-";

            cout << endl;


            if (arrow == HERO_MENU::BANKIR) cout << '~';
            cout << "Bankir(%)";

            if (chosen_hero == HERO_MENU::BANKIR) cout << " <-";

            cout << endl;



            if (arrow == HERO_MENU::BLUEBIRD) cout << '~';
            cout << "Bluebird(<)";

            if (chosen_hero == HERO_MENU::BLUEBIRD) cout << " <-";

            cout << "\n\n";

            if (arrow == HERO_MENU::BACK_TO_MENU) cout << '~';
            cout << "Back to menu";

            direction = Read_direction();
            switch (direction){
                case 'W':
                    if (arrow == HERO_MENU::MAN_MANIFESTO){
                        arrow = HERO_MENU::BACK_TO_MENU;
                    }
                    else {
                        arrow = static_cast<HERO_MENU>(static_cast<int>(arrow) - 1);
                    }
                    break;
                case 'S':
                    if (arrow == HERO_MENU::BACK_TO_MENU){
                        arrow = HERO_MENU::MAN_MANIFESTO;
                    }
                    else {
                        arrow = static_cast<HERO_MENU>(static_cast<int>(arrow) + 1);
                    }
                    break;
                case ENTER:
                    if (arrow == HERO_MENU::BACK_TO_MENU){
                        direction = ESCAPE;
                    }
                    else{
                        chosen_hero = arrow;
                        Change_HERO_CHAR(chosen_hero);

                        ofstream cout_hero("hero.txt");
                        cout_hero << static_cast<int>(Get_hero_id(HERO_CHAR));
                        cout_hero.close();
                    }
                    break;
            }

            system("cls");
        }


    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИЗМЕНЯЕТ КОНСТАНТУ HERO_CHAR
    void Change_HERO_CHAR(HERO_MENU chosen_hero){
        switch  (chosen_hero){
            case HERO_MENU::MAN_MANIFESTO:
                HERO_CHAR = '!';
                break;
            case HERO_MENU::DIAMOND_DOG:
                HERO_CHAR = '@';
                break;
            case HERO_MENU::YARDBIRD:
                HERO_CHAR = '^';
                break;
            case HERO_MENU::CAPITALIST:
                HERO_CHAR = '$';
                break;
            case HERO_MENU::BIRDMAN:
                HERO_CHAR = '>';
                break;
            case HERO_MENU::BANKIR:
                HERO_CHAR = '%';
                break;
            case HERO_MENU::BLUEBIRD:
                HERO_CHAR = '<';
                break;
            default:
                exit(228);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ИЗМЕНЯЕТ КОНСТАНТУ HERO_CHAR
    HERO_MENU Get_hero_id(char hero_char){
        switch  (hero_char){
            case '!':
                return HERO_MENU::MAN_MANIFESTO;
            case '@':
                return HERO_MENU::DIAMOND_DOG;
            case '^':
                return HERO_MENU::YARDBIRD;
            case '$':
                return HERO_MENU::CAPITALIST;
            case '>':
                return HERO_MENU::BIRDMAN;
            case '%':
                return HERO_MENU::BANKIR;
            case '<':
                return HERO_MENU::BLUEBIRD;
            default:
                exit(1);
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    void Launch_Results_menu(){
        double best_score, worst_score, chosen_hero;
        RESULT_MENU arrow(RESULT_MENU::RESET_SCORE);
        bool not_back(true);
        char direction;

        while (not_back) {

            ifstream cin_score("score.txt");
            cin_score >> best_score >> worst_score;
            cin_score.close();

            Print_text_between_lines("Results");
            cout << "Best score: " << best_score << endl;
            cout << "Worst score: " << worst_score << "\n\n";

            if (arrow == RESULT_MENU::RESET_SCORE) cout << '~';
            cout << "Reset score" << endl;
            if (arrow == RESULT_MENU::BACK_TO_MENU) cout << '~';
            cout << "Back to menu" << endl;

            direction = Read_direction();

            switch (direction) {
                case 'W':
                    if (arrow == RESULT_MENU::RESET_SCORE){
                        arrow = RESULT_MENU::BACK_TO_MENU;
                    }
                    else{
                        arrow = static_cast<RESULT_MENU>(static_cast<int>(arrow) - 1);
                    }
                    break;
                case 'S':
                    if (arrow == RESULT_MENU::BACK_TO_MENU){
                        arrow = RESULT_MENU::RESET_SCORE;
                    }
                    else{
                        arrow = static_cast<RESULT_MENU>(static_cast<int>(arrow) + 1);
                    }
                    break;
                case ENTER:
                    bool not_answer(true);
                    RESET_MENU reset_arrow(RESET_MENU::NO);

                    if (arrow == RESULT_MENU::RESET_SCORE) {

                        while (not_answer) {
                            int chosen_direction;
                            system("cls");
                            Print_text_between_lines("Results");
                            cout << "Do you really want to do it?" << "\n\n";
                            if (reset_arrow == RESET_MENU::NO) cout << "~";
                            cout << "No" << endl;
                            if (reset_arrow == RESET_MENU::YES) cout << "~";
                            cout << "Yes";

                            chosen_direction = Read_direction();

                            switch (chosen_direction) {
                                case 'W':
                                    if (reset_arrow == RESET_MENU::NO){
                                        reset_arrow = RESET_MENU::YES;
                                    }
                                    else{
                                        reset_arrow = static_cast<RESET_MENU>(static_cast<int>(reset_arrow) - 1);
                                    }
                                    break;
                                case 'S':
                                    if (reset_arrow == RESET_MENU::YES){
                                        reset_arrow = RESET_MENU::NO;
                                    }
                                    else{
                                        reset_arrow = static_cast<RESET_MENU>(static_cast<int>(reset_arrow) + 1);
                                    }
                                    break;
                                case ENTER:
                                    if (reset_arrow == RESET_MENU::YES) {
                                        // ОБНУЛЯЕМ СЧЁТ
                                        ofstream cout_score("score.txt");
                                        cout_score << "0 0 ";
                                        cout_score.close();
                                    }
                                    not_answer = false;
                                    break;
                            }
                        }

                    }
                    else if (arrow == RESULT_MENU::BACK_TO_MENU){
                        not_back = false;
                    }
                    break;
            }

            system("cls");
        }
    }
};


int main() {
    main_menu menu;
    menu.Launch_menu();
    return 0;
}
