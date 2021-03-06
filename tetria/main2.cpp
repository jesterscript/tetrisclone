/*!
 * \mainpage A tetris clone written in c++
 * \author Doğa Ünal & Berat Sevindik
 * \version 1.0
 * \section compile_sec Compilation 
 * After installing SFML library run this command on a unix terminal : "g++ -std=c++11 main2.cpp -o -lsfml-graphics -lsfml-window -lsfml-system Tetris".
 * As an alternative way,by creating a SFML project in CodeBlock IDE,this project can be run.
 */


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

