/*
    UFSCar Summer Tour
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef PIECE_H
#define PIECE_H

#include <string>

namespace tour {
	/*
		Encapsula uma "Peça" do jogo,
		representada por um identificador inteiro
	*/
	class Piece {
	private:
	    std::string _path;
		std::string _name;
		int _frames;
	public:
	    Piece ();
		Piece (std::string path, std::string name, int frames);

        std::string getPath () const;
		std::string getName () const;
		int getFrames () const;

		bool operator ==(const Piece &b) const {
            return this->getPath() == b.getPath();
		}
	};
}

#endif
