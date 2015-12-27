#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <Screen.h>

namespace tour
{
    class PlayScreen : public Screen
    {
    public:
        PlayScreen(IContext* context);
        virtual ~PlayScreen();

        bool checkEvents(ALLEGRO_EVENT& ev) override;


        virtual void draw() override;

        virtual void recalculate() override;
        virtual void reset() override;
    protected:
        bool drawingEvent(std::pair<std::string, IDrawing*> drawing, tour::TourUtil::EventType event) override;
    private:
        bool canMove(IDrawing* d);

        bool _moving;
        int count = 0;

        int _stackCounter;

    };
}
#endif // PLAYSCREEN_H
