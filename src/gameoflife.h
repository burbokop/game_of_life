#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <e172/src/entity.h>
#include <src/math/cellularautomaton.h>
#include <src/time/elapsedtimer.h>


class Matrix {
    size_t m_w = 0;
    size_t m_h = 0;
    std::vector<bool> m_data;
public:
    Matrix() {}
    Matrix(size_t w, size_t h, double coef = 0.5);

    auto value(size_t x, size_t y);
    auto value(size_t x, size_t y) const;

    size_t w() const;
    size_t h() const;

    std::vector<bool> data() const;
    std::vector<bool> &data();
};


class GameOfLife : public e172::Entity {
    Matrix matrix;
    e172::ElapsedTimer timer;
public:
    GameOfLife();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GAMEOFLIFE_H
