#ifndef WIREWORLD_H
#define WIREWORLD_H

#include <src/entity.h>
#include <src/time/elapsedtimer.h>
#include <src/utility/matrixproxy.h>
#include <src/math/cellularautomaton.h>

class WireWorld : public e172::Entity {
    std::vector<e172::CellularAutomaton::WireWorldCell> matrixData;
    e172::MatrixProxy<e172::CellularAutomaton::WireWorldCell> matrixProxy;
    e172::ElapsedTimer timer;
    e172::Vector pencil;
public:
    WireWorld();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // WIREWORLD_H
