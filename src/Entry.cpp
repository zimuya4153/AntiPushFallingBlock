#pragma once

#include "Entry.h"

#include <ll/api/memory/Hook.h>
#include <ll/api/mod/RegisterHelper.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/actor/projectile/FallingBlockActor.h>
#include <mc/world/level/block/actor/PistonBlockActor.h>
#include <memory>

LL_TYPE_INSTANCE_HOOK(
    MoveEntityLastProgressHook,
    HookPriority::Normal,
    PistonBlockActor,
    &PistonBlockActor::moveEntityLastProgress,
    void,
    Actor& entity,
    Vec3   delta
) {
    if (entity.isType(ActorType::FallingBlock) || entity.isType(ActorType::ItemEntity)) return;
    origin(entity, delta);
}

namespace AntiPushFallingBlock {

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() { return true; }

bool Entry::enable() {
    ll::memory::HookRegistrar<MoveEntityLastProgressHook>().hook();
    getSelf().getLogger().info(
        fmt::format(fmt::fg(fmt::color::red), "请注意，本mod修改了游戏特性，可能会导致一些机器损坏。")
    );
    return true;
}

bool Entry::disable() {
    ll::memory::HookRegistrar<MoveEntityLastProgressHook>().unhook();
    return true;
}

bool Entry::unload() { return true; }

} // namespace AntiPushFallingBlock

LL_REGISTER_MOD(AntiPushFallingBlock::Entry, AntiPushFallingBlock::instance);