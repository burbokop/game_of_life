#ifndef STARWARS_H
#define STARWARS_H

#include <src/entity.h>
#include <src/utility/matrixproxy.h>
#include <src/time/elapsedtimer.h>

class StarWars : public e172::Entity {
    std::vector<uint32_t> matrixData;
    e172::MatrixProxy<uint32_t> matrixProxy;
    e172::ElapsedTimer timer;
public:
    StarWars();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // STARWARS_H
