/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "Piece.h"

tour::Piece::Piece()
    : Piece("", "", 0)
{
}

tour::Piece::Piece(std::string path, std::string name, int frames)
	: _path(path), _name(name), _frames(frames)
{
}
std::string tour::Piece::getPath() const {
	return _path;
}

std::string tour::Piece::getName() const {
	return _name;
}

int tour::Piece::getFrames() const {
	return _frames;
}
