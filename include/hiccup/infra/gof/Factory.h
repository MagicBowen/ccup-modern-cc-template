#ifndef __FACTORY__H__
#define __FACTORY__H__

#include "hiccup/infra/gof/Singleton.h"
#include <memory>

HICCUP_BEGIN

template<typename Entity>
struct Factory {
    template<typename ...TS>
    auto create(TS && ...params) {
        return std::make_unique<Entity>(std::forward<TS>(params)...);
    }
};

#define FACTORY_NAME(Entity) Entity##Factory
#define DEF_FACTORY_OF(Entity) struct FACTORY_NAME(Entity) : ::HICCUP_NS::Singleton<FACTORY_NAME(Entity)>, \
                                                             ::HICCUP_NS::Factory<Entity>
#define FACTORY_OF(Entity) FACTORY_NAME(Entity)::getInstance()
HICCUP_END

#endif