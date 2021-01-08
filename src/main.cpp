#include "gameoflife.h"
#include "wireworld.h"

#include <src/additional.h>
#include <src/gameapplication.h>
#include <src/sdleventhandler.h>
#include <src/sdlgraphicsprovider.h>


#include <iostream>
int main(int argc, char **argv) {
    e172::GameApplication app(argc, argv);

    app.setEventHandler(new SDLEventHandler());
    SDLGraphicsProvider graphicsProvider(app.arguments(), "game_of_life", 300, 300);
    app.setGraphicsProvider(&graphicsProvider);

    GameOfLife gameOfLife;
    app.addEntity(&gameOfLife);

    WireWorld wireWorld;
    app.addEntity(&wireWorld);

    return app.exec();
}
