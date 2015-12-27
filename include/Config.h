/*
    UFSCar Summer Tour
    ED - 2015/1
    UFSCar - São Carlos
*/
#ifndef CONFIG_H
#define CONFIG_H

#include "List.hpp"
#include "Piece.h"

#include <string>
#include <map>

namespace tour {
	class Config{
	public:
        static const char* windowTitle;

        static const int PositionIncrement;
        static std::map<std::string, char*> systemPaths;
        static std::map<std::string, tour::Piece> places;

        static const float FPS;

		static const int SCREEN_WIDTH;
		static const int SCREEN_HEIGHT;

        static const int TreeCount;
        static const std::string TreeNodeNull;
        static std::string TreeDescription[][3];

		enum Screen {
			HOME, PLAY, ABOUT, PLAY_OFF, PLAY_END
		};

	};
}
#endif
