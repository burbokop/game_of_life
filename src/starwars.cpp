#include "starwars.h"

#include <src/abstracteventhandler.h>
#include <src/graphics/abstractrenderer.h>
#include <src/math/cellularautomaton.h>
#include <src/math/math.h>

StarWars::StarWars() {
    timer = e172::ElapsedTimer(128);
}

void StarWars::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    (void)context;

    if(eventHandler->keySinglePressed(e172::ScancodeLeft)) {
        if(m_ruleIndex > 0) {
            --m_ruleIndex;
        }
    } else if(eventHandler->keySinglePressed(e172::ScancodeRight)) {
        if(m_ruleIndex < e172::CellularAutomaton::cooldownRules.size() - 1) {
            ++m_ruleIndex;
        }
    }

    const auto currentRule = e172::CellularAutomaton::cooldownRules[m_ruleIndex];

    if(eventHandler->keySinglePressed(e172::ScancodeBackSpace)) {
        for(size_t i = 0; i < matrixData.size(); ++i) {
            matrixData[i] = false;
        }
        e172::Math::randInit(matrixData.data(), matrixData.size(), 0.01, uint32_t(std::get<2>(currentRule) - 1));
    }


    if(timer.check(matrixProxy.width() > 0 && matrixProxy.height() > 0)) {
        e172::CellularAutomaton::proceed(matrixProxy, currentRule);
    }
}

void StarWars::render(e172::AbstractRenderer *renderer) {
    const size_t cooldown = std::get<2>(e172::CellularAutomaton::cooldownRules[m_ruleIndex]);
    {
        const auto cw = renderer->resolution().size_tX();
        const auto ch = renderer->resolution().size_tY();
        if(matrixProxy.width() != cw || matrixProxy.height() != ch) {
            matrixData.resize(cw * ch);
            e172::Math::randInit(matrixData.data(), matrixData.size(), 0.01, uint32_t(cooldown - 1));
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

    renderer->drawString("{ 1, 2, 3 } - change rule", { 4, 4 }, 0xffffff, e172::TextFormat(e172::TextFormat::AlignDefault, 10));

    renderer->drawString(
                "{ Arrows } - switch rule",
                { 4, renderer->resolution().y() - 24 },
                0xffffff,
                e172::TextFormat(e172::TextFormat::AlignDefault, 10)
                );
    renderer->drawString(
                "{ Backspace } - clear",
                { 4, renderer->resolution().y() - 12 },
                0xffffff,
                e172::TextFormat(e172::TextFormat::AlignDefault, 10)
                );
}
