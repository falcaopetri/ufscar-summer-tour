#ifndef IDRAWING_H
#define IDRAWING_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include <iostream>
#include "Point.h"
namespace tour {
    class IDrawing
    {
        public:
            IDrawing(Point point, int actions, bool isactive);
            virtual ~IDrawing();

            /*
                Setta _hasFocus para true caso a posição @param (mouse_x, mouse_y)
                esteja em cima da imagem
            */
            virtual void checkOver(Point p) = 0;

            virtual bool checkCollision(tour::IDrawing* d) = 0;

            virtual int getActions() = 0;

            virtual int getWidth() = 0;
            virtual int getHeight() = 0;

            tour::Point getPoint();


            virtual ALLEGRO_BITMAP* getBitmap() = 0;

            virtual void destroy() = 0;

            bool hasFocus();
            bool isActive();
            void setActive(bool isactive);

            virtual void move(Point p) = 0;
            virtual void moveTo(Point p) = 0;

            void addActions(unsigned int acts);
            void removeActions(unsigned int acts);
         protected:
         	tour::Point _point;

         	bool _hasFocus = false;
         	bool _isActive = false;

         	unsigned int _actions = 0;
    };
}
#endif // DRAWING_H
