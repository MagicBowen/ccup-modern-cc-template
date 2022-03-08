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

    Status add(const ID& id, EntityPtr ptr) {
        if (find(id)) return HICCUP_FAILURE;

        auto ret = entities.emplace(id, std::move(ptr));
        return ret.second ? HICCUP_SUCCESS : HICCUP_FAILURE;
    }

    void del(const ID& id) {
        entities.erase(id);
    }

    const ENTITY* find(const ID& id) const {
        return const_cast<Repository*>(this)->find(id);
    }

    ENTITY* find(const ID& id) {
        auto result = entities.find(id);
        return (result == entities.end()) ? nullptr : result->second.get();
    }

    template<typename PRED>
    const ENTITY* findBy(PRED && pred) const {
        return const_cast<Repository*>(this)->findBy(std::forward<PRED>(pred));
    }

    template<typename PRED>
    ENTITY* findBy(PRED && pred) {
        auto result = std::find_if(entities.begin(), entities.end(), [pred=std::forward<PRED>(pred)](const auto& item) {
            return pred(*item.second.get());
        });
        return (result == entities.end()) ? nullptr : result->second.get();
    }

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