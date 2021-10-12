#include "wireworld.h"

#include <src/abstracteventhandler.h>
#include <src/graphics/abstractrenderer.h>

WireWorld::WireWorld() {
    timer = e172::ElapsedTimer(1000);
}

void WireWorld::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    (void)context;
    if(eventHandler->keySinglePressed(e172::ScancodeLeft)) {
        pencil.decrementX();
    } else if(eventHandler->keySinglePressed(e172::ScancodeRight)) {
        pencil.incrementX();
    }

    if(eventHandler->keySinglePressed(e172::ScancodeUp)) {
        pencil.decrementY();
    } else if(eventHandler->keySinglePressed(e172::ScancodeDown)) {
        pencil.incrementY();
    }

    if(eventHandler->keyHolded(e172::ScancodeMinus)) {
        timer = e172::ElapsedTimer(timer.interval() - 1);
    } else if(eventHandler->keyHolded(e172::ScancodeEquals)) {
        timer = e172::ElapsedTimer(timer.interval() + 1);
    }

    if(eventHandler->keyHolded(e172::ScancodeE)) {
        matrixProxy.value(pencil) = e172::CellularAutomaton::Empty;
    } else if(eventHandler->keyHolded(e172::ScancodeW)) {
        matrixProxy.value(pencil) = e172::CellularAutomaton::Wire;
    } else if(eventHandler->keyHolded(e172::ScancodeS)) {
        matrixProxy.value(pencil) = e172::CellularAutomaton::Signal;
    }

    if(timer.check(matrixProxy.width() > 0 && matrixProxy.height() > 0)) {
        e172::CellularAutomaton::proceed(matrixProxy, e172::CellularAutomaton::wireWorld);
    }
}

void WireWorld::render(e172::AbstractRenderer *renderer) {
    {
        const auto cw = renderer->resolution().size_tX();
        const auto ch = renderer->resolution().size_tY();
        if(matrixProxy.width() != cw || matrixProxy.height() != ch) {
            matrixData.resize(cw * ch);
            matrixProxy = e172::MatrixProxy(cw, ch, matrixData.data());
        }
    }

    for(size_t y = 0; y < matrixProxy.height(); ++y) {
        for(size_t x = 0; x < matrixProxy.width(); ++x) {
            const auto& c = matrixProxy.value(x, y);
            if(c == e172::CellularAutomaton::Wire) {
                renderer->drawPixel({ double(x), double(y) }, 0xff8800);
            } else if(c == e172::CellularAutomaton::Signal) {
                renderer->drawPixel({ double(x), double(y) }, 0x00ff88);
            } else if(c == e172::CellularAutomaton::SignalEnd) {
                renderer->drawPixel({ double(x), double(y) }, 0x0000ff);
            }
        }
    }

    renderer->drawPixel(pencil, 0x88ffffff);

    renderer->drawString("{ 1, 2, 3 } - change rule", { 4, 4 }, 0xffffff, e172::TextFormat(e172::TextFormat::AlignDefault, 10));
    renderer->drawString("interval: " + std::to_string(timer.interval()), { 4, 16 }, 0xffffff, e172::TextFormat(e172::TextFormat::AlignDefault, 12));

    renderer->drawString(
                "{ W } - wire, { S } - singnal, { E } - clear",
                { 4, renderer->resolution().y() - 38 },
                0xffffff,
                e172::TextFormat(e172::TextFormat::AlignDefault, 12)
                );
    renderer->drawString(
                "{ Arrows } - move, { +/- } - change inteval",
                { 4, renderer->resolution().y() - 20 },
                0xffffff,
                e172::TextFormat(e172::TextFormat::AlignDefault, 12)
                );
}
