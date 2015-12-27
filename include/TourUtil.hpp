#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#include <physfs.h>
#include <allegro5/allegro_physfs.h>

#include "Deque.hpp"
#include "Queue.hpp"
#include "Config.h"
#include "Piece.h"
#include "Drawing.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <utility>

namespace tour
{
//template <class T> class Queue;
class TourUtil
{
public:
    enum ErrorType
    {
        ALLEGRO=1, BITMAP, ADDON, TIMER, AUDIO
    };
    enum Sound
    {
        INTRO, PLAYING
    };
    enum Action
    {
        SOUND=(1<<1), MOUSE_OVER=(1<<2), MOUSE_EXIT=(1<<3), GOTO_HOME=(1<<4),
        GOTO_ABOUT=(1<<5), ON_DOWN_KEY=(1<<6), ON_UP_KEY=(1<<7), ON_RIGHT_KEY=(1<<8), ON_LEFT_KEY=(1<<9),
        CANT_COLLIDE=(1<<10), CANT_GO_OUT=(1<<11), ATTACH=(1<<12), CAN_MOVE=(1<<13), IMPOSSIBLE_GAME=(1<<14),
        GOTO_PLAY=(1<<0)
    };
    enum EventType
    {
        MOUSE_MOVE, LEFT_CLICK, DOWN_KEY, UP_KEY, RIGHT_KEY, LEFT_KEY
    };
    enum Animation
    {
        NONE, GO_UP, GO_DOWN, GO_TO_STACK, GO_TO_QUEUE, GO_TO_OUTPUT, STACK_TO_OUTPUT,
        QUEUE_TO_OUTPUT, QUEUE_TO_STACK, MOVE_WAGONS
    };
    static bool isFlagSet (int bitmask, TourUtil::Action action)
    {
        return (bitmask & action) == action;
    };

    static void printError (std::string message)
    {
        fprintf(stderr, message.c_str());
    }
    /*
        Muda o path-working-directory para o local do executável,
        permitindo o uso de relative-paths para acessar os arquivos do jogo

        Source: https://www.allegro.cc/forums/thread/614268
    */
    static void setResourceArchive()
    {
        // Get current working directory.
        ALLEGRO_PATH *al_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

        // Switch to directory in which application was run from.
        al_append_path_component(al_path, "./data");
        al_change_directory(al_path_cstr(al_path, '/'));

        // Remove path from memory, as the new directory has been reached.
        al_destroy_path(al_path);

        //PHYSFS_init(NULL);
        // if(!PHYSFS_init(NULL))
        //     std::cout << "failed initializing" << std::endl;
        //
        // // Attempt to read contents of data.dat.
        // //if(!PHYSFS_mount(Config::systemPaths["dataFile"], "./", 1))
        // if(!PHYSFS_mount("/data.zip", "/", 1))
        //     std::cout << al_get_current_directory() << ": failed mounting file path" << std::endl;

        // All future loading calls will read from data.dat.
        //al_set_physfs_file_interface();
    }
};
}

#endif // UTIL_HPP
