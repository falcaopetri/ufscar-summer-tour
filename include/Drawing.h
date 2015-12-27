#ifndef DRAWING_H
#define DRAWING_H

#include "IDrawing.h"

namespace tour {
    class Drawing : public IDrawing
    {
        public:
            Drawing(Point point, ALLEGRO_BITMAP* bitmap, int actions, bool isactive);
            virtual ~Drawing();

            virtual ALLEGRO_BITMAP* getBitmap() override;
            virtual void destroy() override;
            /*
                Setta _hasFocus para true caso a posição @param (mouse_x, mouse_y)
                esteja em cima da imagem
            */
            virtual void checkOver(Point p) override;

            virtual bool checkCollision(IDrawing* d) override;

            virtual int getActions() override;

            virtual void move(Point p) override;
            virtual void moveTo(Point p) override;

            virtual int getWidth() override;
            virtual int getHeight() override;
        private:
            ALLEGRO_BITMAP* _bitmap;
    };
}
#endif // DRAWING_H
