#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <e172/src/entity.h>
#include <src/math/cellularautomaton.h>
#include <src/time/elapsedtimer.h>
#include <src/utility/matrixproxy.h>
#include <e172/src/utility/boolean.h>

class GameOfLife : public e172::Entity {
    std::vector<e172::boolean> matrixData;
    e172::MatrixProxy<e172::boolean> matrixProxy;
    e172::ElapsedTimer timer;
public:
    GameOfLife();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GAMEOFLIFE_H
