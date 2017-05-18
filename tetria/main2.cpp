#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "Gamer.h"


TetrisBoard* TetrisBoard::instance = 0;//assigning  static instance to null.
int TetrisBoard::tableAsNumbers[30][20] = {0};//fill the static array with zeros.
PiecePusher* PiecePusher::_instance = 0;


int main()
{
    Game * g = new Game();


    return 0;
}

