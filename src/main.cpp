#include "entityswitch.h"
#include "gameoflife.h"
#include "starwars.h"
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

    StarWars starWars;
    app.addEntity(&starWars);

    WireWorld wireWorld;
    app.addEntity(&wireWorld);

    EntitySwitch entitySwitch({ &gameOfLife, &starWars, &wireWorld });
    app.addEntity(&entitySwitch);

    gameOfLife.setEnabled(true);

    return app.exec();
}
