/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Image.h"

tour::Image::Image()
{ }

tour::Image::Image(int x, int y, ALLEGRO_BITMAP* bitmap)
    : _x(x), _y(y)
{
    _hasFocus = false;
    _bitmap = bitmap;
    _width = al_get_bitmap_width(bitmap);
    _height = al_get_bitmap_height(bitmap);
}

void tour::Image::checkOver(int x, int y)
{
    if(_x <= x && x <= _x + _width &&
            _y <= y && y <= _y + _height)
    {
        _hasFocus = true;
    }
    else
    {
        _hasFocus = false;
    }
}

int tour::Image::getX()
{
    return _x;
}

int tour::Image::getY()
{
    return _y;
}

ALLEGRO_BITMAP* tour::Image::getBitmap()
{
    return _bitmap;
}

bool tour::Image::hasFocus()
{
    return _hasFocus;
}
