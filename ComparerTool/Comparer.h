#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <future>
#include <map>
#include <stack>

namespace Comparer 
{
	struct Charm
	{
        uint32_t Slots[3];
        uint32_t Skills[2];
        uint32_t SkillLevels[2];
	};
	class Comparer 
	{
	private:
		//SkillId, SkillLv, DecoSize
		std::unordered_map<int, std::map<int, int, std::greater<int>>> _decoMap{};
	public:
		void SetDecoMap(std::unordered_map<int, std::map<int, int, std::greater<int>>> decoMap)
		{
			_decoMap = decoMap;
		}
		int Compare(const Charm& c1, const Charm& c2);
	private:
		bool MatchSkill(std::unordered_map<int, int> slots, std::unordered_map<int, int> skillPair, int skillCountHelper);
		std::vector<std::unordered_map<int, int>> Build(std::map<int, int, std::greater<int>> candidates, int target);
		void CombinationSum(std::vector<std::unordered_map<int, int>>& res, std::map<int, int, std::greater<int>> candidates, std::stack<int>& combination, int startSize, int target);

		void GenAll(std::vector<std::vector<std::unordered_map<int, int>>>& output, std::vector<std::vector<std::unordered_map<int, int>>> const & input, std::vector<std::unordered_map<int, int>>& cur, unsigned cur_row = 0);
	};
}