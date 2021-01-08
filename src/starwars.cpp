#include "starwars.h"

#include <src/graphics/abstractrenderer.h>
#include <src/math/cellularautomaton.h>
#include <src/math/math.h>

StarWars::StarWars() {
    timer = e172::ElapsedTimer(128);
}

void StarWars::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    (void)context;
    (void)eventHandler;
    if(timer.check(matrixProxy.width() > 0 && matrixProxy.height() > 0)) {
        e172::CellularAutomaton::proceed(matrixProxy, e172::CellularAutomaton::starWars);
    }
}

void StarWars::render(e172::AbstractRenderer *renderer) {
    {
        const auto cw = renderer->resolution().size_tX();
        const auto ch = renderer->resolution().size_tY();
        if(matrixProxy.width() != cw || matrixProxy.height() != ch) {
            matrixData.resize(cw * ch);
            e172::Math::randInit(matrixData.data(), matrixData.size(), 0.01, uint32_t(3));
            matrixProxy = e172::MatrixProxy(cw, ch, matrixData.data());
        }
    }

    for(size_t y = 0; y < matrixProxy.height(); ++y) {
        for(size_t x = 0; x < matrixProxy.width(); ++x) {
            const auto value = matrixProxy.value(x, y);
            if(value > 0) {
                e172::Color color = 0xffffff;
                if(value == 1) {
                    color = 0x0000ff;
                } else if(value == 2) {
                    color = 0x00ff00;
                } else if(value == 3) {
                    color = 0xff0000;
                }
                renderer->drawPixel({ double(x), double(y) }, color);
            }
        }
    }
}
