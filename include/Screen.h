#ifndef SCREEN_H
#define SCREEN_H

#include <map>
#include <iostream>
#include <typeinfo>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_video.h>

#include "Drawing.h"
#include "TourUtil.hpp"
#include "IContext.h"

namespace tour
{
    class Screen
    {
    public:
        Screen(IContext* context);
        virtual ~Screen();

        virtual void draw();

        virtual bool checkEvents(ALLEGRO_EVENT& ev);

        void addDrawing(std::string name, IDrawing* drawing, bool visible);
        void removeDrawing(std::string name);
        IDrawing* getDrawing(std::string name);

        virtual void recalculate();
        virtual void reset();

        bool isAnimating();
    protected:
        std::map<std::string, IDrawing*> _drawings;
        IContext* _context;

        bool _isAnimating;

        void requestOpposite(std::string name);

        void draw(Drawing* drawing, bool mustBeActive);
        virtual bool drawingEvent(std::pair<std::string, IDrawing*> drawing, tour::TourUtil::EventType event);
    };
}
#endif // SCREEN_H
