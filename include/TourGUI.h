#ifndef RAILSGUI_H
#define RAILSGUI_H

#include "IContext.h"
#include "Screen.h"
#include "PlayScreen.h"
#include "TourUtil.hpp"

namespace tour
{
    class TourGUI : public IContext
    {
    public:
        TourGUI();
        ~TourGUI();

        void initAllegro();
        void loop();
        void shutdown();

        //virtual void startPlaying();

        int exitCode();

        virtual void switchSound();
        virtual std::string getOppositeImage(std::string name);
        virtual tour::IDrawing* requestImage(std::string name);
        virtual bool loadNewVideo();
    protected:
    private:
        virtual bool video_display();
        virtual void setSound(TourUtil::Sound sound);

        int _exitCode;

        int _currentVideoFrames;

        ALLEGRO_EVENT_QUEUE* _eventQueue = nullptr;
        ALLEGRO_TIMER* _timerDrawing = nullptr;
        ALLEGRO_TIMER* _timerPlaying = nullptr;
        ALLEGRO_TIMER* _timerAnimation = nullptr;
        ALLEGRO_SAMPLE* _musicIntro = nullptr;
        ALLEGRO_SAMPLE* _musicPlaying = nullptr;
        ALLEGRO_SAMPLE_ID _musicId;

        ALLEGRO_BITMAP* _bitmap = nullptr;

        TourUtil::Sound _currentSound;
        Screen* _currentScreen = nullptr;

        std::map<std::string, IDrawing*> systemImages;

        // CHANGE - TODO
        bool soundOn = false;
        bool isPlayingSound = false;
        bool showQuestionImage = false;
        bool gameAnswer = true;
        bool redraw = true;
        bool doexit = false;
        bool abortGameFlag = false;
        int animate = 1;
        bool fullscreen = false;

        bool playedIntroOnce = false;

        int status = 0;

        Screen* getScreen(Config::Screen screenID);
        void changeToScreen(Config::Screen screenID);

        void raiseError(std::string message, TourUtil::ErrorType type);

        void addImageToScreen(std::string name, Config::Screen screen, bool visible);
        void removeImageFromScreen(std::string name, Config::Screen screen);
        bool loadSystemImage (std::string name, int xPos, int yPos, int actions, bool isactive);

        void addPiece();
        void resetPositions();
    };
}
#endif // RAILSGUI_H
