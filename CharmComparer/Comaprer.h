#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <future>

struct Charm
{
    uint32_t Slots[3];
    uint32_t Skills[2];
    uint32_t SkillLevels[2];
};

class CharmComparer 
{
};