#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include "hiccup/infra/gof/Singleton.h"
#include "hiccup/infra/base/status.h"
#include <memory>
#include <map>

HICCUP_BEGIN

template<typename ID, typename ENTITY>
struct Repository {
    using EntityPtr = std::unique_ptr<ENTITY>;

    std::size_t size() const {
        return entities.size();
    }

    bool isEmpty() const {
        return entities.empty();
    }

    void clear() {
        entities.clear();
        // std::map<ID, EntityPtr>().swap(entities); // used when need to release memory immediately.
    }
protected:
    std::map<ID, EntityPtr> entities;
};

#define REPO_NAME(Entity) Entity##Repo
#define DEF_REPO_OF(ID, Entity) struct REPO_NAME(Entity) : ::HICCUP_NS::Singleton<REPO_NAME(Entity)>, \
                                                            ::HICCUP_NS::Repository<ID, Entity>
#define REPO_OF(Entity) REPO_NAME(Entity)::getInstance()

HICCUP_END

#endif