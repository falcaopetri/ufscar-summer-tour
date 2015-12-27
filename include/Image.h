/*
    UFSCar Summer Tour
    ED - 2015/1
    UFSCar - S�o Carlos
*/
#ifndef IMAGE_H
#define IMAGE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

namespace tour {
    /*
        Classe para encapsular uma ALLEGRO_BITMAP junto com
        sua posi��o na tela (_x, _y) e m�todos para verificar
        se a imagem est� sobre o foco do mouse
    */
    class Image {
    private:
        bool _hasFocus;
        int _x, _y;
        int _width, _height;

        ALLEGRO_BITMAP* _bitmap;
    public:
        Image();
        Image(int x, int y, ALLEGRO_BITMAP* bitmap);

        ALLEGRO_BITMAP* getBitmap();

        int getX();
        int getY();
        /*
            Setta _hasFocus para true caso a posi��o @param (mouse_x, mouse_y)
            esteja em cima da imagem
        */
        void checkOver(int mouse_x, int mouse_y);
        /*
            Retorna _hasFocus
        */
        bool hasFocus();
    };
}

#endif
