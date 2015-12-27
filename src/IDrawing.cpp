#include "IDrawing.h"

tour::IDrawing::IDrawing(Point p, int actions, bool isactive)
    : _point(p), _actions(actions), _isActive(isactive)
{
    _hasFocus = false;
}
tour::IDrawing::~IDrawing() {

}

tour::Point tour::IDrawing::getPoint()
{
    return _point;
}

bool tour::IDrawing::hasFocus() {
    return _hasFocus;
}
void tour::IDrawing::addActions(unsigned int acts) {
    _actions |= acts;
}
void tour::IDrawing::removeActions(unsigned int acts) {
    _actions = _actions & ~acts;
}

bool tour::IDrawing::isActive() {
    return _isActive;
}

void tour::IDrawing::setActive(bool isactive) {
    _isActive = isactive;
}
