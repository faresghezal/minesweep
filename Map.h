#ifndef MAP_H
#define MAP_H
//in map.h we have class plus some function declaration

//newpage is an inline function that clear the screen
void newpage();
//main screen allow the possibility to change configuration exit or play
class player{
protected:
    int diff;
public:
  player();
//playagain offer the possibility to play another round after loss or win of previous one
int playagain();
//depending on x writestate increment your winning or losing score
void writestate(int x);
//difficulty allow you to change difficulty setting
int difficulty();
//state shows the number of wins or losses according to each difficulty
void states();

};

//class map represent the game map it include the necessary function for the game
class Map:player {
  private:
    int d;
    int numberofbomb;
    char **Map1;
    char **Map2;
public:
    Map();
    ~Map();
    void create();
    int introduction();
    void draw();
    int check(int x ,int y);
    int endgame();
    void play();
};
#endif
