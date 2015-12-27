#include "Screen.h"

tour::Screen::Screen(IContext* context)
    : _context(context)
{
}

tour::Screen::~Screen()
{
    //dtor
}

void tour::Screen::addDrawing(std::string name, IDrawing* drawing, bool visible = true)
{
    if (_drawings.find(name) == _drawings.end())
        _drawings[name] = drawing;

    _drawings[name]->setActive(visible);
}
void tour::Screen::removeDrawing(std::string name)
{
    //_drawings.erase(name);
    if (_drawings.find(name) != _drawings.end())
        _drawings[name]->setActive(false);
}
void tour::Screen::requestOpposite(std::string name)
{
    std::string opposite = _context->getOppositeImage(name);
    addDrawing(opposite, _context->requestImage(opposite),true);
    _drawings[name]->setActive(false);
}
bool tour::Screen::drawingEvent(std::pair<std::string, IDrawing*> drawing, tour::TourUtil::EventType event)
{
    if (drawing.second->isActive())
    {
        char flag = drawing.second->getActions();
        if (drawing.second->hasFocus())
        {
            if (event == tour::TourUtil::EventType::LEFT_CLICK)
            {
                if (TourUtil::isFlagSet(flag, TourUtil::Action::SOUND))
                {
                    _context->switchSound();

                    requestOpposite(drawing.first);
                    return true;
                }
                else if (TourUtil::isFlagSet(flag, TourUtil::Action::GOTO_PLAY))
                {
                    _context->changeToScreen(Config::Screen::PLAY);
                }
                else if (TourUtil::isFlagSet(flag, TourUtil::Action::GOTO_HOME))
                {
                    _context->changeToScreen(Config::Screen::HOME);
                }
                else if (TourUtil::isFlagSet(flag, TourUtil::Action::GOTO_ABOUT))
                {
                    _context->changeToScreen(Config::Screen::ABOUT);
                }
            }

            else if (event == tour::TourUtil::EventType::MOUSE_MOVE && TourUtil::isFlagSet(flag, TourUtil::Action::MOUSE_OVER))
            {
                requestOpposite(drawing.first);
                return true;
            }
        }
        else
        {
            if (event == tour::TourUtil::EventType::MOUSE_MOVE && TourUtil::isFlagSet(flag, TourUtil::Action::MOUSE_EXIT))
            {
                requestOpposite(drawing.first);
                return true;
            }
        }
    }

    return false;
}

void tour::Screen::recalculate()
{
//    for (auto &d : _drawings)
//    {
//        IDrawing* drawing = d.second;
//        ALLEGRO_BITMAP* bitmap = drawing->getBitmap();
//        if (bitmap)
//        {
//            float aspect_ratio = al_get_video_aspect_ratio(_context->getVideo());
//            int w, h, x, y;
//            {
//                h = al_get_display_height(_context->getDisplay());
//                w = al_get_display_width(_context->getDisplay());
//                w = (int)(h * aspect_ratio);
//                if (w > al_get_display_width(_context->getDisplay()))
//                {
//                    w = al_get_display_width(_context->getDisplay());
//                    h = (int)(w / aspect_ratio);
//                }
//
//                x = drawing->getPoint().X * 1.0 * w/Config::SCREEN_WIDTH;
//                y = drawing->getPoint().Y * 1.0 * h/Config::SCREEN_HEIGHT;
//
//                drawing->moveTo(Point(x,y));
//                /*al_draw_scaled_bitmap(bitmap,
//                                      0,0,
//                                      Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
//                                      x, y, w, h, 0);
//                std::cout << w << std::endl;*/
//                /*
//                al_draw_bitmap(bitmap,
//                               drawing->getPoint().X, drawing->getPoint().Y, 0);
//                               */
//            }
//
//        }
//    }
}

void tour::Screen::reset()
{
    for (auto &drawing : _drawings)
    {
        // TODO
        // request opposite image
        if (drawing.second && drawing.second->hasFocus())
        {
            if (TourUtil::isFlagSet(drawing.second->getActions(), TourUtil::Action::MOUSE_EXIT))
            {
                requestOpposite(drawing.first);

                drawing.second->checkOver(Point(-100, -100));
            }
        }

    }
}
tour::IDrawing* tour::Screen::getDrawing(std::string name)
{
    return _drawings[name];
}

bool tour::Screen::checkEvents(ALLEGRO_EVENT& ev)
{
    if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)   //check if the mouse moved
    {
        for (auto &drawing : _drawings)
        {
            drawing.second->checkOver(Point(ev.mouse.x, ev.mouse.y));
            if (drawingEvent(drawing, tour::TourUtil::MOUSE_MOVE)) return true;
        }
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        for (auto &drawing : _drawings)
        {
            if (drawingEvent(drawing, tour::TourUtil::LEFT_CLICK)) return true;
        }
    }
    return false;
}
/*
    Desenha uma Image na tela de acordo com o identificador @name
*/
void tour::Screen::draw(Drawing* drawing, bool mustBeActive = true)
{
    if (drawing->isActive() || !mustBeActive)
    {
        ALLEGRO_BITMAP* bitmap = drawing->getBitmap();
//        if (bitmap)
//        {
//            float aspect_ratio = al_get_video_aspect_ratio(_context->getVideo());
//            int w, h, x, y;
//
//            //if (aspect_ratio > 0.0f)
//            {
//                /* Always make the video fit into the window. */
//                h = al_get_display_height(_context->getDisplay());
//                w = al_get_display_width(_context->getDisplay());
//                w = (int)(h * aspect_ratio);
//                if (w > al_get_display_width(_context->getDisplay()))
//                {
//                    w = al_get_display_width(_context->getDisplay());
//                    h = (int)(w / aspect_ratio);
//                }

//                x = drawing->getPoint().X * 1.0 * w/Config::SCREEN_WIDTH;
//                y = drawing->getPoint().Y * 1.0 * h/Config::SCREEN_HEIGHT;
//                al_draw_scaled_bitmap(bitmap,
//                                      0,0,
//                                      Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
//                                      x, y, w, h, 0);
//                std::cout << w << std::endl;

        al_draw_bitmap(bitmap,
                       drawing->getPoint().X, drawing->getPoint().Y, 0);

//            }

        //      }
    }
}

bool tour::Screen::isAnimating()
{
    return _isAnimating;
}
void tour::Screen::draw()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    _isAnimating = _context->video_display();

    for (auto &drawing : _drawings)
    {
        //std::cout << drawing.first << " ";
        //draw(drawing.second);

        draw((Drawing*)drawing.second);
        //std::cout<<std::endl;
    }
}
