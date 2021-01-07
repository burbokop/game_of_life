#include "gameoflife.h"

#include <src/gameapplication.h>
#include <src/sdleventhandler.h>
#include <src/sdlgraphicsprovider.h>




int main(int argc, char **argv) {
    e172::GameApplication app(argc, argv);

    app.setEventHandler(new SDLEventHandler());
    SDLGraphicsProvider graphicsProvider(app.arguments(), "game_of_life", 128, 128);
    app.setGraphicsProvider(&graphicsProvider);


    GameOfLife gameOfLife;
    app.addEntity(&gameOfLife);

    return app.exec();
}
