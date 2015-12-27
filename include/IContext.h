#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <iostream>
#include <map>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <allegro5/allegro.h>

#include <allegro5/allegro_image.h>

#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro_video.h>

#include <stdexcept>

#include "Drawing.h"
//#include "Screen.h"
#include "Config.h"
#include "Game.h"

namespace tour {
    class Screen;

    class IContext
    {
        public:
            IContext() {}
            virtual ~IContext() {}

            virtual void switchSound() = 0;
            virtual std::string getOppositeImage(std::string name) = 0;
            virtual tour::IDrawing* requestImage(std::string name) = 0;

            virtual ALLEGRO_FONT* getFont() {
                return _font;
            }

            Game& getGame() {
                return _game;
            }

            ALLEGRO_VIDEO* getVideo() {
                return _video;
            }
            ALLEGRO_DISPLAY* getDisplay() {
                return _display;
            }

            virtual bool loadNewVideo() = 0;
            //virtual void startPlaying() = 0;
            virtual void changeToScreen(Config::Screen screenID) = 0;
            virtual bool video_display() = 0;
        protected:
            virtual void setSound(TourUtil::Sound sound) = 0;

            std::map<int, tour::Screen*> screens;
            Game _game;
            ALLEGRO_VIDEO* _video = nullptr;
        ALLEGRO_DISPLAY* _display = nullptr;

            ALLEGRO_FONT* _font = nullptr;

            virtual tour::Screen* getScreen(Config::Screen screenID) = 0;
    };
}
#endif // ICONTEXT_H
