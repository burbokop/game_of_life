#include "gameoflife.h"

#include <src/graphics/abstractrenderer.h>

#include <src/math/math.h>

#include <src/abstracteventhandler.h>

#include <src/math/cellularautomaton.h>


GameOfLife::GameOfLife() {
    timer = e172::ElapsedTimer(64);
}

void GameOfLife::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    (void)context;
    if(eventHandler->keySinglePressed(e172::ScancodeLeft)) {
        if(m_ruleIndex > 0) {
            --m_ruleIndex;
        }
    } else if(eventHandler->keySinglePressed(e172::ScancodeRight)) {
        if(m_ruleIndex < e172::CellularAutomaton::booleanRules.size() - 1) {
            ++m_ruleIndex;
        }
    }

    if(timer.check(matrixProxy.width() > 0 && matrixProxy.height() > 0)) {
        e172::CellularAutomaton::proceed(matrixProxy, e172::CellularAutomaton::booleanRules[m_ruleIndex]);
    }
}

void GameOfLife::render(e172::AbstractRenderer *renderer) {
    {
        const auto cw = renderer->resolution().size_tX();
        const auto ch = renderer->resolution().size_tY();
        if(matrixProxy.width() != cw || matrixProxy.height() != ch) {
            matrixData.resize(cw * ch);
            e172::Math::randInit(matrixData.data(), matrixData.size(), 0.15, e172::boolean(true));
            matrixProxy = e172::MatrixProxy(cw, ch, matrixData.data());
        }
    }

    for(size_t y = 0; y < matrixProxy.height(); ++y) {
        for(size_t x = 0; x < matrixProxy.width(); ++x) {
            if(matrixProxy.value(x, y)) {
                renderer->drawPixel({ double(x), double(y) }, 0xff4000);
            }
        }
    }
}

