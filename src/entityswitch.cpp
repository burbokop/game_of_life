#include "entityswitch.h"

#include <src/abstracteventhandler.h>


EntitySwitch::EntitySwitch(const std::vector<e172::ptr<Entity> > &entities) {
    m_entities = entities;
    disableAll();
}

void EntitySwitch::disableAll() {
    for(const auto& e : m_entities) {
        e->setEnabled(false);
    }
}

void EntitySwitch::proceed(e172::Context *, e172::AbstractEventHandler *eventHandler) {
    if(eventHandler->keySinglePressed(e172::Scancode1) && m_entities.size() > 0) {
        disableAll();
        m_entities[0]->setEnabled(true);
    } else if(eventHandler->keySinglePressed(e172::Scancode2) && m_entities.size() > 1) {
        disableAll();
        m_entities[1]->setEnabled(true);
    } else if(eventHandler->keySinglePressed(e172::Scancode3) && m_entities.size() > 2) {
        disableAll();
        m_entities[2]->setEnabled(true);
    } else if(eventHandler->keySinglePressed(e172::Scancode4) && m_entities.size() > 3) {
        disableAll();
        m_entities[3]->setEnabled(true);
    }
}

void EntitySwitch::render(e172::AbstractRenderer *) {}
