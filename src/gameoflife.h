#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <e172/src/entity.h>
#include <src/time/elapsedtimer.h>

class Matrix {
    size_t m_w;
    size_t m_h;
    std::vector<bool> m_data;
public:
    Matrix() {}
    Matrix(size_t w, size_t h, bool init_rand = false);

    auto value(size_t x, size_t y);
    auto value(size_t x, size_t y) const;

    size_t w() const;
    size_t h() const;
};


class GameOfLife : public e172::Entity {
    e172::ElapsedTimer timer;
    Matrix matrix;
public:
    GameOfLife();
    static size_t cellsCount(size_t x, size_t y, const Matrix &matrix);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GAMEOFLIFE_H
