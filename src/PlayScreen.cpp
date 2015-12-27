#include "PlayScreen.h"

tour::PlayScreen::PlayScreen(IContext* context)
    : tour::Screen::Screen(context)
{
    _moving = false;
    _isAnimating = false;
}

tour::PlayScreen::~PlayScreen()
{
    //dtor
}

void tour::PlayScreen::reset()
{
    Screen::reset();

    _stackCounter = 0;


    _drawings["correctAnswer"]->setActive(false);
    _drawings["incorrectAnswer"]->setActive(false);

    _moving = false;
}
bool tour::PlayScreen::checkEvents(ALLEGRO_EVENT& ev)
{
    if (Screen::checkEvents(ev))
    {
        return true;
    }
    if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        switch(ev.keyboard.keycode)
        {

        case ALLEGRO_KEY_LEFT:
            if (!isAnimating() && !_context->getGame().hasFinished())
            {
                _context->getGame().navigateToLeft();
                _context->loadNewVideo();
                _isAnimating = true;
            }

            return true;
            break;
        case ALLEGRO_KEY_RIGHT:
            if (!isAnimating() && !_context->getGame().hasFinished())
            {
                _context->getGame().navigateToRight();
                _context->loadNewVideo();
                _isAnimating = true;
            }
            return true;
            break;
        }
    }

    return false;
}
void tour::PlayScreen::draw()
{
    Screen::draw();

    ALLEGRO_COLOR tc = al_map_rgba_f(1, 1, 1, 0);
    ALLEGRO_COLOR bc = al_map_rgba_f(0.5, 0.5, 0.5, 0);

    float aspect_ratio = 1;//al_get_video_aspect_ratio(_context->getVideo());
    int w, h, x, y;
    h = al_get_display_height(_context->getDisplay());
    w = al_get_display_width(_context->getDisplay());
    w = (int)(h * aspect_ratio);
    if (w > al_get_display_width(_context->getDisplay()))
    {
        w = al_get_display_width(_context->getDisplay());
        h = (int)(w / aspect_ratio);
    }

    ALLEGRO_FONT* font = _context->getFont();
    const char* target = Config::places[_context->getGame().getTarget()].getName().c_str();
    const char* current = Config::places[_context->getGame().getCurrent()].getName().c_str();

    int targetWidth = al_get_text_width(font, target);
    int currentWidth = al_get_text_width(font, current);

    al_draw_textf(font, bc, (w-currentWidth)/2, 500* 1.0 * h/Config::SCREEN_HEIGHT, 0,
                  "%s", current);

    al_draw_textf(font, tc, (w-targetWidth)/2, 10* 1.0 * h/Config::SCREEN_HEIGHT, 0,
                  "%s", target);
    if (!isAnimating() && !_context->getGame().hasFinished())
    {
        const char* left = Config::places[_context->getGame().getLeft()].getName().c_str();
        const char* right = Config::places[_context->getGame().getRight()].getName().c_str();

        int leftWidth = al_get_text_width(font, left);
        int rightWidth = al_get_text_width(font, right);

        if (rightWidth <= leftWidth) {
            al_draw_textf(font, tc, 10*1.0 * w/Config::SCREEN_WIDTH, 550* 1.0 * h/Config::SCREEN_HEIGHT, 0,
                      "%s", left);
        }else {
            al_draw_textf(font, tc, 0.5*(rightWidth-leftWidth) + 10*1.0 * w/Config::SCREEN_WIDTH, 550* 1.0 * h/Config::SCREEN_HEIGHT, 0,
                      "%s", left);
        }


        al_draw_textf(font, tc, (1152-rightWidth)*1.0 * w/Config::SCREEN_WIDTH, 550* 1.0 * h/Config::SCREEN_HEIGHT, 0,
                      "%s", right);
    }

    if (_context->getGame().hasFinished())
    {
        if (_context->getGame().isCorrect())
        {
            // correct
            _drawings["correctAnswer"]->setActive(true);
        }
        else
        {
            // not correct
            _drawings["incorrectAnswer"]->setActive(true);
        }
    }
}
void tour::PlayScreen::recalculate()
{

}
bool tour::PlayScreen::canMove(IDrawing* d)
{

    if (TourUtil::isFlagSet(d->getActions(), TourUtil::Action::CANT_COLLIDE))
    {
        for (auto &drawing : _drawings)
        {
            if (drawing.second == d || !drawing.second->isActive())
                continue;

            if ( TourUtil::isFlagSet(drawing.second->getActions(), TourUtil::Action::CANT_COLLIDE))
            {
                if (d->checkCollision(drawing.second))
                    return false;
            }
        }
    }

    return true;
}

bool tour::PlayScreen::drawingEvent(std::pair<std::string, IDrawing*> drawing, tour::TourUtil::EventType event)
{
    if (Screen::drawingEvent(drawing, event))
        return true;


    return false;
}
