#include "Comparer.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <thread>
#include <future>
#include <map>
#include <stack>

int Comparer::Comparer::Compare(const Charm& c1, const Charm& c2)
{
    std::unordered_map<int, int> skillPair{};
    for (auto i = 0; i < 2; ++i)
    {
        if (c1.Skills[i] != 0)
        {
            if (!skillPair.count(c1.Skills[i]))
            {
                skillPair[c1.Skills[i]] = 0;
            }
            skillPair[c1.Skills[i]] += c1.SkillLevels[i];
        }
        if (c2.Skills[i] != 0)
        {
            if (!skillPair.count(c2.Skills[i]))
            {
                skillPair[c2.Skills[i]] = 0;
            }
            skillPair[c2.Skills[i]] -= c2.SkillLevels[i];
        }
    }

    auto isSkillEqual = true;
    auto isSkillBigger = true;
    auto isSkillSmaller = true;
    for (auto p : skillPair)
    {
        isSkillEqual &= (p.second == 0);
        isSkillBigger &= (p.second > 0);
        isSkillSmaller &= (p.second < 0);
    }

    std::unordered_map<int, int> soltPair{};
    for (auto i = 0; i < 3; ++i)
    {
        if (c1.Slots[i] != 0)
        {
            if (!soltPair.count(c1.Slots[i]))
            {
                soltPair[c1.Slots[i]] = 0;
            }
            soltPair[c1.Slots[i]] += 1;

        }
        if (c2.Slots[i] != 0)
        {
            if (!soltPair.count(c2.Slots[i]))
            {
                soltPair[c2.Slots[i]] = 0;
            }
            soltPair[c2.Slots[i]] -= 1;
        }
    }
    std::unordered_map<int, int> c1SoltPair{};
    std::unordered_map<int, int> c2SoltPair{};
    for (auto pair : soltPair)
    {
        if (pair.second > 0)
        {
            for (auto i = 1; i <= pair.first; ++i)
            {
                if (!c1SoltPair.contains(i))
                {
                    c1SoltPair[i] = 0;
                }
                c1SoltPair[i] += pair.second;
            }
        }
        if (pair.second < 0)
        {
            for (auto i = 1; i <= pair.first; ++i)
            {
                if (!c2SoltPair.contains(i))
                {
                    c2SoltPair[i] = 0;
                }
                c2SoltPair[i] -= pair.second;
            }
        }
    }

    auto isSoltEqual = true;
    auto soltBiggerCount = 0;
    auto soltSmallerCount = 0;
    for (auto p : soltPair)
    {
        auto count = std::abs(p.second);

        isSoltEqual &= (p.second == 0);
        soltBiggerCount += (p.second > 0 ? count : 0);
        soltSmallerCount += (p.second < 0 ? count : 0);
    }
    if (isSkillEqual && isSoltEqual)
    {
        return -1;
    }
    if ((isSkillEqual || isSkillBigger) && soltBiggerCount > 0 && soltSmallerCount == 0)
    {
        return -1;
    }
    if ((isSkillEqual || isSkillSmaller) && soltSmallerCount > 0 && soltBiggerCount == 0)
    {
        return 1;
    }
    //Skill equal
    // slot 4 vs slot 3
    if (isSkillEqual && soltSmallerCount == soltBiggerCount)
    {
        auto isC1Bigger = true;
        auto tempC1Slot = c1SoltPair;
        for (auto c2Slot : c2SoltPair)
        {
            if (!tempC1Slot.contains(c2Slot.first) || tempC1Slot[c2Slot.first] < c2Slot.second)
            {
                isC1Bigger = false;
                break;
            }
            tempC1Slot[c2Slot.first] -= c2Slot.second;
        }
        auto isC2Bigger = true;
        auto tempC2Slot = c2SoltPair;
        for (auto c1Slot : c1SoltPair)
        {
            if (!tempC2Slot.contains(c1Slot.first) || tempC2Slot[c1Slot.first] < c1Slot.second)
            {
                isC2Bigger = false;
                break;
            }
            tempC2Slot[c1Slot.first] -= c1Slot.second;
        }

        if (isC2Bigger && isC1Bigger)
        {
            return 0;
        }
        if (isC1Bigger)
        {
            return -1;
        }
        if (isC2Bigger)
        {
            return 1;
        }
        return 0;
    }
    if (isSkillEqual && !isSoltEqual)
    {
        return 0;
    }

    auto isC1Bigger = isSkillSmaller && MatchSkill(c1SoltPair, skillPair, -1);
    auto isC2Bigger = isSkillBigger && MatchSkill(c1SoltPair, skillPair, 1);

    if (isC1Bigger && !isC2Bigger)
    {
        return -1;
    }
    else if (!isC1Bigger && isC2Bigger)
    {
        return 1;
    }

    return 0;
}

bool Comparer::Comparer::MatchSkill(std::unordered_map<int, int> slots, std::unordered_map<int, int> skillPair, int skillCountHelper)
{
    auto isCanSolve = true;
    std::vector<std::vector<std::vector<std::tuple<int, int>>>> tempDecoSet{};

    auto setPairCount = 0;
    for (auto skill : skillPair)
    {
        auto skillId = skill.first;
        if (skillId == 0)
        {
            continue;
        }
        if (!_decoMap.contains(skillId))
        {
            isCanSolve = false;
            break;
        }
        auto skillLv = skill.second * skillCountHelper;
        if (skillLv <= 0)
        {
            continue;
        }
        auto candidates = _decoMap.at(skillId);
        auto build = Build(candidates, skillLv);

        tempDecoSet.push_back(build);
        if (setPairCount == 0)
        {
            setPairCount = 1;
        }
        setPairCount *= build.size();
    }

    if (!isCanSolve)
    {
        return false;
    }
    for (auto i = 0; i < setPairCount; ++i)
    {
        auto canSolve = true;
        auto tempSoltPair = slots;
        for (auto set : tempDecoSet)
        {
            for (auto temp : set[i % set.size()])
            {
                auto needCount = get<1>(temp);
                auto decoSize = get<0>(temp);
                for (auto startSize = decoSize; startSize > 0; --startSize)
                {
                    if (tempSoltPair[startSize] < needCount)
                    {
                        canSolve = false;
                        break;
                    }
                    tempSoltPair[startSize] -= needCount;
                }
                if (!canSolve)
                {
                    break;
                }
            }
            if (canSolve)
            {
                return true;
            }
        }
    }
    return isCanSolve;
}

std::vector<std::vector<std::tuple<int, int>>> Comparer::Comparer::Build(std::map<int, int, std::greater<int>> candidates, int target)
{
    std::vector<std::vector<std::tuple<int, int>>> res{};
    std::stack<std::tuple<int, int>> combination{};
    CombinationSum(res, candidates, combination, target);
    return res;
}

void Comparer::Comparer::CombinationSum(std::vector<std::vector<std::tuple<int, int>>>& res, std::map<int, int, std::greater<int>> candidates, std::stack<std::tuple<int, int>>& combination, int target)
{
    if (target == 0)
    {
        std::vector<std::tuple<int, int>> temp{};
        std::stack<std::tuple<int, int>> copy(combination);
        while (!copy.empty()) 
        {
            auto p = copy.top();
            temp.push_back(p);
            copy.pop();
        }
        res.push_back(temp);
        return;
    }

    for (auto level = target; level > 0; --level)
    {
        if (!candidates.contains(level))
        {
            continue;
        }
        auto size = candidates.at(level);
        std::tuple<int, int> temp(size, target / level );
        combination.push(temp);
        CombinationSum(res, candidates, combination, target % level);
        combination.pop();
    }
}