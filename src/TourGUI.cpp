#include "TourGUI.h"

tour::TourGUI::TourGUI()
{
    //ctor
    status = 12;
}

tour::TourGUI::~TourGUI()
{
}
bool tour::TourGUI::loadNewVideo()
{
    if (_video)
        al_close_video(_video);

    std::string place = _game.getCurrent();
    Piece p = Config::places[place];
    _video = al_open_video(p.getPath().c_str());
    if(!_video)
    {
        std::cout << p.getPath() << std::endl;
        raiseError("failed to create video!\n", TourUtil::ErrorType::ALLEGRO);
    }

    _currentVideoFrames = p.getFrames();

    al_register_event_source(_eventQueue, al_get_video_event_source(_video));
    al_start_video(_video, al_get_default_mixer());


    if (playedIntroOnce && place == "ru")
    {
        std::cout << al_seek_video(_video, 10) << std::endl;
        _currentVideoFrames = 5;
    }
    else
    {
        playedIntroOnce = true;
    }
    return true;
}
bool tour::TourGUI::video_display()
{
    if (!_video)
        return false;

    /* Videos often do not use square pixels - Adjust this to fit your target bitmap dimensions.
     */
    float scale = 1.2;
    /* Get the currently visible frame of the video, based on clock
     * time.
     */
    ALLEGRO_BITMAP *frame = al_get_video_frame(_video);
    int w, h, x, y;
    ALLEGRO_COLOR tc = al_map_rgba_f(0, 0, 0, 0.5);
    ALLEGRO_COLOR bc = al_map_rgba_f(0.5, 0.5, 0.5, 0.5);
    double p;

    if (!frame)
        return false;

    float sw = al_get_bitmap_width(frame);
    float sh = al_get_bitmap_height(frame);
    float dw = scale * al_get_video_scaled_width(_video);
    float dh = scale * al_get_video_scaled_height(_video);
    /* Display the frame. */
    al_draw_scaled_bitmap(frame, 0, 0,
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame), 0, 0,
                          scale * al_get_video_scaled_width(_video),
                          scale * al_get_video_scaled_height(_video), 0);

    if (_currentVideoFrames)
        _currentVideoFrames--;

    return _currentVideoFrames != 0;
}

void tour::TourGUI::changeToScreen(Config::Screen screenID)
{
    if (screenID == Config::Screen::PLAY)
    {
        if (_currentScreen)
            _currentScreen->reset();

        _currentScreen = getScreen(screenID);
    }
    else if (screenID == Config::Screen::ABOUT)
    {
        _currentScreen = getScreen(screenID);
    }
    else if (screenID == Config::Screen::HOME)
    {
        if (_currentScreen == getScreen(screenID))
            _exitCode = 1;

        setSound(TourUtil::Sound::INTRO);
        if (_currentScreen)
            _currentScreen->reset();

        resetPositions();
        if (!_game.hasFinished())
        {
            _game.finishGame();
        }
        _game.newGame();
        if (_currentScreen != getScreen(Config::Screen::ABOUT))
            loadNewVideo();

        _currentScreen = getScreen(screenID);
    }
}

Screen* tour::TourGUI::getScreen(Config::Screen screenID)
{
    if (screens[screenID] == nullptr)
    {
        if (screenID == Config::Screen::PLAY)
        {
            screens[screenID] = new PlayScreen(this);
        }
        else
        {
            screens[screenID] = new Screen(this);
        }
    }

    return screens[screenID];
}

void tour::TourGUI::raiseError(std::string message, TourUtil::ErrorType type)
{
    TourUtil::printError(message.c_str());
    _exitCode = type;
    shutdown();
    throw std::runtime_error(message);
}

/*
Carrega uma imagem utilizada pelo jogo, cujo path encontra-se
em Config::imagesPaths
*/
bool tour::TourGUI::loadSystemImage (std::string name, int xPos, int yPos, int actions, bool isactive = true)
{
    if (systemImages[name] == nullptr)
    {
        Drawing* d = new Drawing(Point(xPos, yPos), al_load_bitmap(Config::systemPaths[name]), actions, isactive);

        if(d->getBitmap() == nullptr)
        {
            raiseError("failed to load " + name + " image", TourUtil::ErrorType::BITMAP);
            return false;
        }

        systemImages[name] = d;
    }
    else
    {
        systemImages[name]->removeActions(0x11111111);
        systemImages[name]->addActions(actions);
        systemImages[name]->moveTo(Point(xPos, yPos));
        systemImages[name]->setActive(isactive);
    }

    // TODO

    return true;
}
void tour::TourGUI::addImageToScreen(std::string name, Config::Screen screen, bool visible = true)
{
    if (systemImages.find(name) != systemImages.end())
    {
        getScreen(screen)->addDrawing(name, systemImages[name], visible);
    }
}
void tour::TourGUI::removeImageFromScreen(std::string name, Config::Screen screen)
{
    getScreen(screen)->removeDrawing(name);
}

void tour::TourGUI::setSound(TourUtil::Sound sound)
{
    if (sound != _currentSound)
    {
        _currentSound = sound;
        if (isPlayingSound)
        {
            switchSound();
            switchSound();
        }
    }
}
void tour::TourGUI::switchSound()
{
    if (!soundOn)
    {
        if (!isPlayingSound)
        {
            if (_currentSound == TourUtil::Sound::INTRO)
            {
                al_play_sample(_musicIntro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &_musicId);
            }
            else if (_currentSound == TourUtil::Sound::PLAYING)
            {
                al_play_sample(_musicPlaying, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &_musicId);
            }
            soundOn = isPlayingSound = true;
        }
    }
    else
    {
        if (isPlayingSound)
        {
            al_stop_sample(&_musicId);
            soundOn = isPlayingSound = false;
        }
    }
}

std::string tour::TourGUI::getOppositeImage(std::string name)
{
    if (name[name.length()-1] == 'F')
    {
        name.replace(name.end()-1, name.end(), "N");
    }
    else if (name[name.length()-1] == 'N')
    {
        name.replace(name.end()-1, name.end(), "F");
    }
    return name;
}
tour::IDrawing* tour::TourGUI::requestImage(std::string name)
{
    return systemImages[name];
}

/*
    Inicializa o Allegro e todos os componentes utilizados
    Inicializa todas as imagens utilizadas ao longo do jogo
*/
void tour::TourGUI::initAllegro ()
{
    // Init
    {
        if(!al_init())
        {
            raiseError("failed to initialize allegro!\n", TourUtil::ErrorType::ALLEGRO);
        }
    }

    TourUtil::setResourceArchive();


    // Keyboard
    {
        if(!al_install_keyboard())
        {
            raiseError("failed to initialize the keyboard!\n", TourUtil::ErrorType::ADDON);
        }
    }
    // Mouse
    {
        if(!al_install_mouse())
        {
            raiseError("failed to initialize the mouse!\n", TourUtil::ErrorType::ADDON);
        }
    }
    {
        if(!al_init_primitives_addon())
        {
            raiseError("failed to initialize the primitive addons!\n", TourUtil::ErrorType::ADDON);
        }
    }
    // Timers
    {
        _timerDrawing = al_create_timer(1.0 / Config::FPS);
        if(!_timerDrawing)
        {
            raiseError("failed to create timerDrawing!\n", TourUtil::ErrorType::TIMER);
        }
        _timerPlaying = al_create_timer(1.0);
        if(!_timerPlaying)
        {
            raiseError("failed to create timerPlaying!\n", TourUtil::ErrorType::TIMER);
        }
        _timerAnimation = al_create_timer(1.0 * 5 *2 / Config::FPS);
        if(!_timerAnimation)
        {
            raiseError("failed to create timerAnimation!\n", TourUtil::ErrorType::TIMER);
        }
    }
    // Display
    {
        al_set_new_display_flags(ALLEGRO_RESIZABLE);
        al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

        _display = al_create_display(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
        if(!_display)
        {
            raiseError("failed to create display!\n", TourUtil::ErrorType::ALLEGRO);
        }
    }

    // Font
    {
        al_init_font_addon();
        if(!al_init_ttf_addon())
        {
            raiseError("failed to initialize the ttf addon!\n", TourUtil::ErrorType::ADDON);
        }

        _font = al_load_ttf_font(Config::systemPaths["fontPath"], 50, 0);
        if(!_font)
        {
            raiseError("failed to initialize the ttf font!\n", TourUtil::ErrorType::ADDON);
        }
    }
    // Audio
    {
        if(!al_install_audio())
        {
            raiseError("failed to initialize audio!\n", TourUtil::ErrorType::AUDIO);
        }
        if(!al_init_acodec_addon())
        {
            raiseError("failed to initialize audio codecs!\n", TourUtil::ErrorType::AUDIO);
        }

        if (!al_reserve_samples(1))
        {
            raiseError("failed to reserve samples!\n", TourUtil::ErrorType::AUDIO);
        }

        _musicIntro = al_load_sample(Config::systemPaths["soundPathIntro"]);

        if (!_musicIntro)
        {
            std::cout << al_get_current_directory() << std::endl;
            raiseError("failed to load audio clip sample!\n" , TourUtil::ErrorType::AUDIO);
        }

        /*_musicPlaying = al_load_sample(Config::systemPaths["soundPathPlaying"]);

        if (!_musicPlaying)
        {
            raiseError("failed to load audio clip sample!\n" , TourUtil::ErrorType::AUDIO);
        }*/
    }
    // Image Addon
    {
        if(!al_init_image_addon())
        {
            raiseError("failed to initialize image addon!", TourUtil::ErrorType::BITMAP);
        }
    }

    // Video Addon
    {
        if(!al_init_video_addon())
        {
            raiseError("failed to initialize video addon!", TourUtil::ErrorType::ADDON);
        }
    }

    std::string imageName;
    // Icon
    {
        imageName = "icon";
        loadSystemImage(imageName, 0, 0, 0);
    }
    // Answer Image
    {
        imageName = "correctAnswer";
        loadSystemImage(imageName, 331, 222, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, false);

        imageName = "incorrectAnswer";
        loadSystemImage(imageName, 278, 222, 0);
        addImageToScreen(imageName, Config::Screen::PLAY, false);
    }
    // Start Button
    {
        imageName = "startF";
        loadSystemImage(imageName, 425, 363, TourUtil::Action::MOUSE_OVER);
        addImageToScreen(imageName, Config::Screen::HOME);

        imageName = "startN";
        loadSystemImage(imageName, 419, 357, TourUtil::Action::GOTO_PLAY | TourUtil::Action::MOUSE_EXIT);
    }

    // About Button
    {
        imageName = "aboutF";
        loadSystemImage(imageName, 522, 445, TourUtil::Action::MOUSE_OVER);
        addImageToScreen(imageName, Config::Screen::HOME);

        imageName = "aboutN";
        loadSystemImage(imageName, 517, 440, TourUtil::Action::GOTO_ABOUT | TourUtil::Action::MOUSE_EXIT);
    }

    // Sound Button
    {
        imageName = "soundN";
        loadSystemImage(imageName, 1100, 10, TourUtil::Action::SOUND);
        addImageToScreen(imageName, Config::Screen::HOME);
        addImageToScreen(imageName, Config::Screen::ABOUT);
        addImageToScreen(imageName, Config::Screen::PLAY);

        imageName = "soundF";
        loadSystemImage(imageName, 1100, 10, TourUtil::Action::SOUND);
    }
    // aboutInfo
    {
        imageName = "aboutInfo";
        loadSystemImage(imageName, 1, 1, 0);
        addImageToScreen(imageName, Config::Screen::ABOUT);
    }
    // Back
    {
        imageName = "back";
        loadSystemImage(imageName, 20, 10, TourUtil::Action::GOTO_HOME);
        addImageToScreen(imageName, Config::Screen::HOME);
        addImageToScreen(imageName, Config::Screen::ABOUT);
        addImageToScreen(imageName, Config::Screen::PLAY);
    }
    {
        imageName = "logo";
        loadSystemImage(imageName, 0, 0, 0);
        addImageToScreen(imageName, Config::Screen::HOME);
    }

    // Event Queue
    {
        _eventQueue = al_create_event_queue();
        if(!_eventQueue)
        {
            raiseError("failed to create _eventQueue!\n", TourUtil::ErrorType::ALLEGRO);
        }
    }
    // Window properties
    {
        al_set_window_title(_display, Config::windowTitle);
        al_set_display_icon(_display, systemImages["icon"]->getBitmap());
        al_set_display_flag(_display, ALLEGRO_FULLSCREEN_WINDOW, true);
        al_acknowledge_resize(_display);
    }
    // Event registers
    {
        al_register_event_source(_eventQueue, al_get_display_event_source(_display));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timerDrawing));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timerPlaying));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timerAnimation));
        al_register_event_source(_eventQueue, al_get_keyboard_event_source());
        al_register_event_source(_eventQueue, al_get_mouse_event_source());
    }
    // Display setup
    {
        al_set_target_bitmap(al_get_backbuffer(_display));
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
    }
    // Start timers
    {
        al_start_timer(_timerDrawing);
        al_start_timer(_timerPlaying);
        al_start_timer(_timerAnimation);
    }

    changeToScreen(Config::Screen::HOME);

    setSound(TourUtil::Sound::INTRO);
    switchSound();
    _exitCode = 0;

    // recalcular
    int w, h;
    h = al_get_display_height(getDisplay());
    w = al_get_display_width(getDisplay());
    float aspect_ratio = 1;//al_get_video_aspect_ratio(getVideo());

    w = (int)(h * aspect_ratio);
    if (w > al_get_display_width(getDisplay()))
    {
        w = al_get_display_width(getDisplay());
        h = (int)(w / aspect_ratio);
    }
    for (auto &d : systemImages)
    {
        IDrawing* drawing = d.second;
        ALLEGRO_BITMAP* bitmap = drawing->getBitmap();
        if (bitmap)
        {
            int x,y;

            x = drawing->getPoint().X * 1.0 * w/Config::SCREEN_WIDTH;
            y = drawing->getPoint().Y * 1.0 * h/Config::SCREEN_HEIGHT;

            drawing->moveTo(Point(x,y));
        }
    }

    systemImages["aboutInfo"]->moveTo(Point(0.5*(w-systemImages["aboutInfo"]->getWidth()),
                                            0.5*(h-systemImages["aboutInfo"]->getHeight())));
    systemImages["logo"]->moveTo(Point(0.5*(w-systemImages["logo"]->getWidth()),
                                            0.5*(h-systemImages["logo"]->getHeight())));
}

void tour::TourGUI::resetPositions ()
{

}

void tour::TourGUI::loop ()
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(_eventQueue, &ev);

    if(ev.type == ALLEGRO_EVENT_TIMER)
    {
        if (ev.timer.source == _timerDrawing)
        {
            redraw = true;
        }
    }

    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        _exitCode = 1;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_ESCAPE:
            if (!_game.hasFinished())
                _game.finishGame();

            changeToScreen(Config::Screen::HOME);
            break;
            /*case ALLEGRO_KEY_F:
                fullscreen = !fullscreen;
                al_set_display_flag(_display, ALLEGRO_FULLSCREEN_WINDOW,
                                    fullscreen);
                break;*/
        }
    }
    else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
    {
        /*al_acknowledge_resize(_display);
        al_clear_to_color(al_map_rgb(0, 0, 0));*/
    }

    _currentScreen->checkEvents(ev);
    if(redraw && al_is_event_queue_empty(_eventQueue))
    {
        redraw = false;
        al_clear_to_color(al_map_rgb(0,0,0));
        //_currentScreen->recalculate();
        _currentScreen->draw();
        al_flip_display();
    }
}
/*
    Destr�i todos os componentes do Allegro
    Deve-se adicionar � esse m�todos qualquer componente do Allegro
    que necessite de uma desreferencia��o apropriada

    Essa fun��o � executada ao final do jogo ou caso a inicializa��o
    do Allegro falhe logo no in�cio da aplica��o
*/
void tour::TourGUI::shutdown ()
{
    if (_timerDrawing)    al_destroy_timer(_timerDrawing);
    if (_timerPlaying)    al_destroy_timer(_timerPlaying);
    if (_timerAnimation)    al_destroy_timer(_timerAnimation);
    if (_display)         al_destroy_display(_display);
    if (_eventQueue)     al_destroy_event_queue(_eventQueue);
    if (_musicPlaying)           al_destroy_sample(_musicPlaying);
    if (_musicIntro)           al_destroy_sample(_musicIntro);
    if (_video)         al_close_video(_video);

    for (auto &image: systemImages)
    {
        image.second->destroy();
    }
    systemImages.clear();

    for (auto &screen: screens)
    {
        delete screen.second;
    }
    screens.clear();

}


int tour::TourGUI::exitCode()
{
    return _exitCode;
}
