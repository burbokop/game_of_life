#include "gameoflife.h"

#include <src/graphics/abstractrenderer.h>

size_t Matrix::w() const { return m_w; }
size_t Matrix::h() const { return m_h; }

std::vector<bool> Matrix::data() const {
    return m_data;
}

std::vector<bool> &Matrix::data() {
    return m_data;
}

auto Matrix::value(size_t x, size_t y) {
    x %= m_w;
    y %= m_h;
    return m_data[y * m_w + x];
}

auto Matrix::value(size_t x, size_t y) const {
    x %= m_w;
    y %= m_h;
    return m_data[y * m_w + x];
}

Matrix::Matrix(size_t w, size_t h, double coef) {
    std::srand(clock());
    m_w = w;
    m_h = h;
    m_data.resize(w * h);

    if(coef && m_data.size() > 0) {
        for(size_t y = 0; y < h; ++y) {
            for(size_t x = 0; x < w; ++x) {
                value(x, y) = (double(std::rand()) / double(std::numeric_limits<decltype (std::rand())>::max())) < coef;
            }
        }
    }
}




GameOfLife::GameOfLife() {
    timer = e172::ElapsedTimer(8);
}

void GameOfLife::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(timer.check()) {
        e172::CellularAutomaton::proceed(matrix.w(), matrix.h(), matrix.data(), e172::CellularAutomaton::maze);
    }
}

void GameOfLife::render(e172::AbstractRenderer *renderer) {
    if(matrix.w() != renderer->resolution().size_tX() || matrix.h() != renderer->resolution().size_tY()) {
        matrix = Matrix(renderer->resolution().size_tX(), renderer->resolution().size_tY(), 256 * 16);
    }

    for(size_t y = 0; y < matrix.h(); ++y) {
        for(size_t x = 0; x < matrix.w(); ++x) {
            if(matrix.value(x, y)) {
                renderer->drawPixel({ double(x), double(y) }, 0xff8800);
            }
        }
    }
}

