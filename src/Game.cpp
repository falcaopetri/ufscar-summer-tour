/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Game.h"

Game::Game()
{
    populateTree();
    _currentNode = _tree;
}
bool Game::isCorrect()
{
    return _isCorrect;
}
void Game::populateTree()
{
    _tree = BTUtil::buildTree(Config::TreeDescription, Config::TreeCount, Config::TreeNodeNull);
}

void Game::newGame()
{
    _currentNode = _tree;
    generateTarget();
    _hasFinished = false;
}
std::string Game::getCurrent()
{
    if (_currentNode)
        return _currentNode->getValue();
    else
        return "";
}
std::string Game::getTarget()
{
    if (_target)
        return _target->getValue();
    else
        return "";
}
Game::~Game()
{
    delete _tree;
}
void Game::generateTarget()
{
    _target = _tree;
    srand(time(NULL));
    while (!BTUtil::isLeaf(_target)) {
        bool goToLeft = rand() % 2;
        if (goToLeft) {
            TreeNode<std::string>* tmp = BTUtil::leftSubtree(_target);

            if (tmp == nullptr) {
                goToLeft = false;
            }
            else {
                _target = tmp;
            }
        }

        if (!goToLeft) {
            _target = BTUtil::rightSubtree(_target);
        }
    }
}
bool Game::finishGame()
{
    _isCorrect = (_currentNode == _target);
    _hasFinished = true;

    return true;
}
std::string Game::getLeft()
{
    TreeNode<std::string>* left = BTUtil::leftSubtree(_currentNode);
    if (left)
        return left->getValue();
    else
        return "";
}
std::string Game::getRight()
{
    TreeNode<std::string>* right = BTUtil::rightSubtree(_currentNode);
    if (right)
        return right->getValue();
    else
        return "";
}

void Game::navigateToLeft()
{
    TreeNode<std::string>* left = BTUtil::leftSubtree(_currentNode);
    if (left)
        _currentNode = left;

    if (BTUtil::isLeaf(left))
        finishGame();
}
void Game::navigateToRight()
{
    TreeNode<std::string>* right = BTUtil::rightSubtree(_currentNode);
    if (right)
        _currentNode = right;


    if (BTUtil::isLeaf(right))
        finishGame();
}

bool Game::hasFinished()
{
    return _hasFinished;
}
