#ifndef ENTITYSWITCH_H
#define ENTITYSWITCH_H

#include <src/entity.h>
#include <src/utility/ptr.h>

class EntitySwitch : public e172::Entity {
    std::vector<e172::ptr<e172::Entity> > m_entities;
public:
    EntitySwitch(const std::vector<e172::ptr<e172::Entity>> &entities);
    void disableAll();

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *) override;
};

#endif // ENTITYSWITCH_H
