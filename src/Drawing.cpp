#include "Drawing.h"
tour::Drawing::Drawing(Point point, ALLEGRO_BITMAP* bitmap, int actions, bool isactive = true)
    : IDrawing(point, actions, isactive)
{
    _bitmap = bitmap;
}

tour::Drawing::~Drawing()
{
    //dtor
}
/*
bool tour::Drawing::isActive() {
    return _isActive;
}

void tour::Drawing::setActive(bool isactive) {
    _isActive = isactive;
}*/
bool tour::Drawing::checkCollision(IDrawing* d) {
    Point p = d->getPoint();
    /*std::cout << "(" << getPoint().X << "x" << getPoint().Y << ")-"
                << "(" << getPoint().X + getWidth() << "x" << getPoint().Y + getHeight() << ")x"
                << "(" << p.X << "x" << p.Y << ")-"
                << "(" << p.X + d->getWidth() << "x" << p.Y + d->getHeight() << ")" << std::endl;
    //if (getPoint().Y >= 0) {
    bool a = (getPoint().X > p.X + d->getWidth() - 1);
    bool b =(getPoint().Y > p.Y + d->getHeight() - 1);
    //std::cout << "BBBB(" << getPoint().Y << "x" << p.Y + d->getHeight() << ")-"
    bool c = (p.X > getPoint().X + getWidth() - 1);
    bool dd = (p.Y > getPoint().Y + getHeight() - 1);*/
    return !((getPoint().X > p.X + d->getWidth() - 1) || // is b1 on the right side of b2?
        (getPoint().Y > p.Y + d->getHeight() - 1) || // is b1 under b2?
        (p.X > getPoint().X + getWidth() - 1) || // is b2 on the right side of b1?
        (p.Y > getPoint().Y + getHeight() - 1));   // is b2 under b1?
    /*}
    else {
        return !((getPoint().X > p.X + d->getWidth() - 1) || // is b1 on the right side of b2?
            (getPoint().Y <= p.Y + d->getHeight() - 1) || // is b1 under b2?
            (p.X > getPoint().X + getWidth() - 1) || // is b2 on the right side of b1?
            (p.Y <= getPoint().Y + getHeight() - 1));   // is b2 under b1?
    }*/

    //return _x <= d->getX() && d->getX() <= _x + getWidth() &&
      //      _y <= d->getY() && d->getY() <= _y + getHeight();
}
int tour::Drawing::getWidth()
{
    return al_get_bitmap_width(_bitmap);
}

void tour::Drawing::destroy() {
    if (_bitmap) al_destroy_bitmap(_bitmap);
    _bitmap = nullptr;
}
int tour::Drawing::getHeight()
{
    return al_get_bitmap_height(_bitmap);
}

int tour::Drawing::getActions()
{
    return _actions;
}

void tour::Drawing::move(Point p) {
    std::cout << "(" << _point.X << ", " << _point.Y << ")" << "\t\t";

    //_point += p;
    _point.X += p.X;
    _point.Y += p.Y;

    std::cout << "(" << _point.X << ", " << _point.Y << ")" << std::endl;
}
void tour::Drawing::moveTo(Point p) {
    _point = p;
}
void tour::Drawing::checkOver(Point p)
{
    if(getPoint().X <= p.X && p.X <= getPoint().X + getWidth() &&
            getPoint().Y <= p.Y && p.Y <= getPoint().Y + getHeight())
    {
        _hasFocus = true;
    }
    else
    {
        _hasFocus = false;
    }
}

ALLEGRO_BITMAP* tour::Drawing::getBitmap()
{
    return _bitmap;
}

