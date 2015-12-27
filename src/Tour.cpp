/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - São Carlos
*/
#include "GUI.h"
#include "TourGUI.h"
//
//void drawSoundButton ()
//{
//    // TODO
//    /*
//    if (soundOn)
//    {
//        drawImage("soundOn");
//        if (!isPlayingSound)
//        {
//            al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &musicId);
//            isPlayingSound = true;
//        }
//    }
//    else
//    {
//        drawImage("soundOff");
//        if (isPlayingSound)
//        {
//            al_stop_sample(&musicId);
//            isPlayingSound = false;
//        }
//    }*/
//}
//void drawMenuHome ()
//{/*
//    // Logo
//    {
//        drawImage("logo");
//    }
//    // Start Button
//    {
//        if(systemImages["startNoFocus"].hasFocus())   drawImage("startFocus");
//        else                                        drawImage("startNoFocus");
//    }
//    // About Button
//    {
//        if(systemImages["aboutNoFocus"].hasFocus())   drawImage("aboutFocus");
//        else                                        drawImage("aboutNoFocus");
//    }
//    // Sound
//    {
//        drawSoundButton();
//    }*/
//}
//
//void drawMenuDifficulty ()
//{/*
//    // Select difficulty
//    {
//        drawImage("selectDifficulty");
//    }
//    // Easy Button
//    {
//        if(systemImages["easyNoFocus"].hasFocus())    drawImage("easyFocus");
//        else                                        drawImage("easyNoFocus");
//    }
//    // Medium Button
//    {
//        if(systemImages["mediumNoFocus"].hasFocus())      drawImage("mediumFocus");
//        else                                            drawImage("mediumNoFocus");
//    }
//    // Hard Button
//    {
//        if(systemImages["hardNoFocus"].hasFocus())    drawImage("hardFocus");
//        else                                        drawImage("hardNoFocus");
//    }
//    // Insane Button
//    {
//        if(systemImages["insaneNoFocus"].hasFocus())  drawImage("insaneFocus");
//        else                                        drawImage("insaneNoFocus");
//    }
//    // Back Button
//    {
//        drawImage("back");
//    }
//    // Sound Button
//    {
//        drawSoundButton();
//    }*/
//}
//
//void drawMenuPlaying ()
//{
//    /*if (!game.hasFinished())
//    {
//        int time = game.getScore().getTiming();
//        string name = "image" + to_string(currentPiece.getId());
//
//        if (animate == 0)
//        {
//            drawImage(name);
//        }
//        else
//        {
//            alfa += 1;
//            if(alfa > 10)
//            {
//                animate = 0;
//                alfa=0;
//            }
//
//            if (animate == 1)
//            {
//                al_draw_tinted_bitmap(systemImages[name].getBitmap(),
//                                      al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa),
//                                      systemImages[name].getX(), systemImages[name].getY(), 0);
//            }
//            else if (animate == -1)
//            {
//                al_draw_tinted_bitmap(systemImages[name].getBitmap(),
//                                      al_map_rgba(245 + alfa, 245 + alfa, 245 + alfa, alfa),
//                                      systemImages[name].getX(), systemImages[name].getY(), 0);
//            }
//        }
//
//        if (time < 2 && showQuestionImage)
//        {
//        }
//        else if (time < 3)
//        {
//            if (showQuestionImage)
//            {
//                game.resetScore();
//                currentPiece = game.getCurrentPiece();
//                animate = -1;
//                showQuestionImage = false;
//            }
//            drawImage("gameQuestion");
//            drawImage("noYes");
//        }
//        else
//        {
//            drawImage("noYes");
//
//            string errorCounter = to_string(game.getScore().getErrorCounter());
//            al_draw_text(font, al_map_rgb(255,0,0), SCREEN_WIDTH*3/18, 0,ALLEGRO_ALIGN_CENTRE, errorCounter.c_str());
//
//            char timing[100];
//            sprintf(timing, "%d:%02d", time / 60, time % 60);
//            al_draw_text(font, al_map_rgb(255,255,255), SCREEN_WIDTH*52/72, 0, ALLEGRO_ALIGN_CENTRE, timing);
//        }
//
//        if (!gameAnswer)
//        {
//            al_draw_text(font, al_map_rgb(255,50,0), SCREEN_WIDTH*66/72, 0, ALLEGRO_ALIGN_CENTRE, "+5s");
//        }
//    }
//    else
//    {
//        game.finishGame();
//        currentMenu = Menu::END_PLAYING;
//    }*/
//}
//
//void drawMenuEndPlaying ()
//{
//    /*al_draw_text(font, al_map_rgb(0,0,0), SCREEN_WIDTH/2, (SCREEN_HEIGHT/2),ALLEGRO_ALIGN_CENTRE, "Total de Erros:");
//    al_draw_text(font, al_map_rgb(0,0,0), SCREEN_WIDTH/2, (SCREEN_HEIGHT/8),ALLEGRO_ALIGN_CENTRE, "Tempo Total:");
//
//    string errorCounter = to_string(game.getScore().getErrorCounter());
//    al_draw_text(font, al_map_rgb(255,50,0), SCREEN_WIDTH/2, (SCREEN_HEIGHT*5/8),ALLEGRO_ALIGN_CENTRE, errorCounter.c_str());
//
//    int time = game.getScore().getTiming();
//    char timing[100];
//    sprintf(timing, "%d:%02d", time / 60, time % 60);
//    al_draw_text(font, al_map_rgb(255,50,0), SCREEN_WIDTH/2, (SCREEN_HEIGHT/4),ALLEGRO_ALIGN_CENTRE, timing);
//
//    drawImage("back");*/
//}
//
//void drawMenuAbout ()
//{
//    /*drawImage("aboutInfo");
//    drawImage("back");*/
//}
///*
//    Desenha o Menu Atual
//*/
//void drawCurrentMenu ()
//{
//    /*drawImage("background");
//
//    if      (currentMenu == Menu::HOME)         drawMenuHome();
//    else if (currentMenu == Menu::DIFFICULTY)   drawMenuDifficulty();
//    else if (currentMenu == Menu::PLAYING)      drawMenuPlaying();
//    else if (currentMenu == Menu::END_PLAYING)  drawMenuEndPlaying();
//    else if (currentMenu == Menu::ABOUT)        drawMenuAbout();
//
//    al_flip_display();*/
//}
///*
//void answerGame (bool answer)
//{
//    gameAnswer = game.answer(answer);
//    currentPiece = game.getCurrentPiece();
//    showQuestionImage = false;
//    animate = -1;
//    alfa = 0;
//}*/
//
//
//
//
///*
//    A vida de um jogo utilizando o Allegro é definida por:
//    1. Inicialização dos componentes do Allegro
//    2. Loop de jogo
//    3. Remoção de todos os componentes criados
//*/
int main(int argc, char **argv)
{
    TourGUI game;

    game.initAllegro();
    while (game.exitCode() == 0) {
        game.loop();
    }
    game.shutdown();

    return game.exitCode();
}


    /*{
        video = al_open_video(filename);
        if(!video)
        {
            raiseError("failed to create display!\n", TourUtil::ErrorType::ALLEGRO);
        }
    }
   al_start_video(video, al_get_default_mixer());
video_display(video);*/
