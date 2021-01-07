#include "gameoflife.h"

#include <src/graphics/abstractrenderer.h>

size_t Matrix::w() const { return m_w; }
size_t Matrix::h() const { return m_h; }

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

Matrix::Matrix(size_t w, size_t h, size_t init_count) {
    std::srand(clock());
    m_w = w;
    m_h = h;
    m_data.resize(w * h);

    if(init_count && m_data.size() > 0) {
        const auto coef = double(init_count) / double(m_data.size());
        for(size_t y = 0; y < h; ++y) {
            for(size_t x = 0; x < w; ++x) {
                value(x, y) = (double(std::rand()) / double(std::numeric_limits<decltype (std::rand())>::max())) < coef;
            }
        }
    }
}




GameOfLife::GameOfLife() {
    timer = e172::ElapsedTimer(0);
    matrix = Matrix(256, 256, 256 * 8);

    rule = GOLRule { { 3 }, { 2, 3 } };
    //rule = GOLRule { { 3 }, { 1, 2, 3, 4, 5 } };
}

size_t GameOfLife::cellsCount(size_t x, size_t y, const Matrix &matrix) {
    matrix.value(x, y);

    return size_t(matrix.value(x + 1, y))
            + size_t(matrix.value(x + 1, y + 1))
            + size_t(matrix.value(x, y + 1))
            + size_t(matrix.value(x - 1, y + 1))
            + size_t(matrix.value(x - 1, y))
            + size_t(matrix.value(x - 1, y - 1))
            + size_t(matrix.value(x, y - 1))
            + size_t(matrix.value(x + 1, y - 1));
}

void GameOfLife::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(timer.check()) {
        for(size_t y = 0; y < matrix.h(); ++y) {
            for(size_t x = 0; x < matrix.w(); ++x) {
                const auto c = cellsCount(x, y, matrix);
                if(matrix.value(x, y) == false) {
                    if(rule.first.contains(c)) {
                        matrix.value(x, y) = true;
                    }
                } else {
                    if(!rule.second.contains(c)) {
                        matrix.value(x, y) = false;
                    }
                }
            }
        }
    }
}

void GameOfLife::render(e172::AbstractRenderer *renderer) {
    for(size_t y = 0; y < matrix.h(); ++y) {
        for(size_t x = 0; x < matrix.w(); ++x) {
            if(matrix.value(x, y)) {
                renderer->drawPixel({ double(x), double(y) }, 0xff8800);
            }
        }
    }
}

