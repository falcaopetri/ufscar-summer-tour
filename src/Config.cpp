/*
    The Last: Too Fast
    ED - 2015/1
    UFSCar - S�o Carlos
*/
#include "Config.h"


const float tour::Config::FPS = 60*2;

const int tour::Config::SCREEN_WIDTH = 1280 * 0.9;
const int tour::Config::SCREEN_HEIGHT = 720 * 0.9;

const char* tour::Config::windowTitle = "UFSCar Summer Tour";

std::map<std::string, tour::Piece> tour::Config::places =
{
    { "ru", Piece("videos/ru.avi", "RU", 800)},
    { "sul", Piece("videos/sul.ogv", "Area Sul", 500)},
    { "banco", Piece("videos/banco.ogv", "Banco do Brasil", 225)},
    { "ginasio", Piece("videos/ginasio.ogv", "Quadra", 350)},
    { "laboratorio", Piece("videos/laboratorio.ogv", "Lab. do DTO", 200)},
    { "pq", Piece("videos/pq.ogv", "PQ", 275)},
    { "palquinho", Piece("videos/palquinho.ogv", "Palquinho", 100)},
    { "campo", Piece("videos/campo.ogv", "Campo", 200)},
    { "at2", Piece("videos/at2.ogv", "AT-2", 175)},
    { "at8", Piece("videos/at8.ogv", "AT-8", 100)},
    { "moradia", Piece("videos/moradia.ogv", "Moradia", 225)},
    { "pracinha", Piece("videos/pracinha.ogv", "Pracinha", 30)},

    { "norte", Piece("videos/norte.ogv", "Area Norte", 400)},
    { "bco", Piece("videos/bco.ogv", "BCo", 50)},
    { "materiais", Piece("videos/materiais.ogv", "Materiais", 400)},
    { "at5", Piece("videos/at5.ogv", "AT-5", 575)},
    { "dc", Piece("videos/dc.ogv", "DC", 400)},
    { "at7", Piece("videos/at7.ogv", "AT-7", 200)},
    { "rua", Piece("videos/rua.ogv", "Rua", 325)},
    { "professores", Piece("videos/professores.ogv", "Centro de Professores", 175)},
    { "at9", Piece("videos/at9.ogv", "AT-9", 250)},
    { "observatorio", Piece("videos/observatorio.ogv", "Observatorio", 275)},
    { "geronto", Piece("videos/geronto.ogv", "Gerontologia", 325)},
    { "nullen", Piece("videos/nullen.ogv", "NULLEN", 225)},
    { "use", Piece("videos/use.ogv", "USE", 450)}
};
const std::string tour::Config::TreeNodeNull = "";
const int tour::Config::TreeCount = 12;
std::string tour::Config::TreeDescription[][3] = {
    { "ru", "norte", "sul" },
    { "sul", "ginasio", "banco" },
    { "banco", "laboratorio", "campo" },
    { "ginasio", "pq", "palquinho" },
    { "pq", "at2", "at8" },
    { "at8", "moradia", "pracinha" },
    { "norte", "bco", "materiais" },
    { "materiais", "dc", "at5" },
    { "at5", "rua", "at7" },
    { "rua", "observatorio", "nullen" },
    { "dc", "at9", "professores" },
    { "at9", "use", "geronto" }
};


std::map<std::string, char*> tour::Config::systemPaths =
{
    { "soundPathIntro", "sounds/soundIntro.ogg"},
    { "fontPath", "fonts/erasitc.ttf"},
    { "dataFile", "data.dat"},

    { "aaabackgroundMenu",   "images/statics/aaBackgroundMenu.png"},
    { "aaabackgroundF",   "images/statics/aaBackgroundF.png"},
    { "aaabackgroundO",   "images/statics/aaBackgroundO.png"},

    { "logo",            "images/statics/logo.png"},
    { "icon",            "images/statics/icon.png" },

    { "startF",   "images/statics/startF.png" },
    { "startN",     "images/statics/startN.png" },

    { "correctAnswer",     "images/statics/correctAnswer.png" },
    { "incorrectAnswer",     "images/statics/incorrectAnswer.png" },

    { "aboutF",   "images/statics/aboutF.png" },
    { "aboutN",     "images/statics/aboutN.png" },

    { "soundF",       "images/statics/soundF.png" },
    { "soundN",        "images/statics/soundN.png" },

    { "aboutInfo",      "images/statics/aboutInfo.png" },
    { "back",           "images/statics/back.png" }
};
