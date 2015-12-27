/*
    UFSCar Summer Tour
    ED - 2015/1
    UFSCar - São Carlos
*/

#ifndef GAME_H
#define GAME_H

#include "Config.h"

#include "TreeNode.hpp"
#include "BTUtil.hpp"

#include "TourUtil.hpp"

#include <iostream>

using namespace tour;

namespace tour
{
class Game
{
private:
    TreeNode<std::string>* _tree;
    TreeNode<std::string>* _currentNode;

    TreeNode<std::string>* _target;

    bool _isCorrect;
    bool _hasFinished;


    void generateTarget();

    void populateTree();
public:
    Game();
    ~Game();

    std::string getCurrent();
    std::string getTarget();

    std::string getLeft();
    std::string getRight();

    void navigateToLeft();
    void navigateToRight();

    bool hasFinished();
    bool isCorrect();

    /*
    	Prepara o Game para um novo jogo
    */
    void newGame();

    /*
    	Encerra o jogo, validando se ele já tinha chegado ao final
    	e adicionando a pontuação do jogador, se for o caso
    */
    bool finishGame();
};
}

#endif
