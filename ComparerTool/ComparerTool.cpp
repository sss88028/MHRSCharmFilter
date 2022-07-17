// ComparerTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Comparer.h"
#include <vector>
#include <iostream>

int main()
{
    Comparer::Comparer c{};

    std::map<int, int, std::greater<int>> aSkill
    {
        {1, 1},
        {3, 4},
    };
    std::map<int, int, std::greater<int>> bSkill
    {
        {1, 2},
        {2, 4},
    };
    std::map<int, int, std::greater<int>> cSkill
    {
        {1, 3},
    };
    std::map<int, int, std::greater<int>> dSkill
    {
        {1, 2},
    };
    std::map<int, int, std::greater<int>> eSkill
    {
        {1, 2},
    };
    std::map<int, int, std::greater<int>> fSkill
    {
        {1, 2},
    };

    std::unordered_map<int, std::map<int, int, std::greater<int>>> decoMap
    {
        {1, aSkill},
        {2, bSkill},
        {3, cSkill},
        {4, dSkill},
        {5, eSkill},
        {6, fSkill},
    };

    c.SetDecoMap(decoMap);

    {
        Comparer::Charm c1
        {
            .Slots = {2, 2},
        };
        Comparer::Charm c2
        {
            .Slots = {4, 1},
        };

        std::cout << "Expect 0 ," << c.Compare(c1, c2) << "\n";;
    }
    {
        Comparer::Charm c1
        {
            .Slots = {2, 2},
        };
        Comparer::Charm c2
        {
            .Slots = {4, 2},
        };
        std::cout << "Expect 1 ," << c.Compare(c1, c2) << "\n";
        std::cout << "Expect -1 ," << c.Compare(c2, c1) << "\n";
    }
    {
        Comparer::Charm c1
        {
            .Slots = {4, 1},
            .Skills = {0, 0},
            .SkillLevels = {1, 0},
        };
        Comparer::Charm c2
        {
            .Slots = {0, 0},
            .Skills = {1, 0},
            .SkillLevels = {3, 0},
        };
        std::cout << "Expect -1 ," << c.Compare(c1, c2) << "\n";;
    }
    {
        Comparer::Charm c1
        {
            .Slots = {1, 1, 1},
            .Skills = {4, 0},
            .SkillLevels = {1, 0},
        };
        Comparer::Charm c2
        {
            .Slots = {2, 0, 0},
            .Skills = {1, 0},
            .SkillLevels = {3, 0},
        };
        std::cout << "Expect 0 ," << c.Compare(c1, c2) << "\n";;
    }
    {
        Comparer::Charm c1
        {
            .Slots = {3, 1, 1},
            .Skills = {3, 4},
            .SkillLevels = {2, 2},
        };
        Comparer::Charm c2
        {
            .Slots = {1, 1, 0},
            .Skills = {2, 0},
            .SkillLevels = {1, 0},
        };
        std::cout << "Expect -1 ," << c.Compare(c1, c2) << "\n";;
    }
    {
        Comparer::Charm c1
        {
            .Slots = {3, 1, 1},
            .Skills = {0, 0},
            .SkillLevels = {0, 0},
        };
        Comparer::Charm c2
        {
            .Slots = {0, 0, 0},
            .Skills = {5, 0},
            .SkillLevels = {1, 0},
        };
        std::cout << "Expect 0 ," << c.Compare(c1, c2) << "\n";;
    }

    {
        Comparer::Charm c1
        {
            .Slots = {4, 4, 4},
            .Skills = {0, 0},
            .SkillLevels = {0, 0},
        };
        Comparer::Charm c2
        {
            .Slots = {0, 0, 0},
            .Skills = {1, 2},
            .SkillLevels = {4, 5},
        };
        std::cout << "Expect 0 ," << c.Compare(c1, c2) << "\n";;
    }
    {
        Comparer::Charm c1
        {
            .Slots = {3, 1, 1},
            .Skills = {1, 0},
            .SkillLevels = {3, 0},
        };
        Comparer::Charm c2
        {
            .Slots = {0, 0, 0},
            .Skills = {1, 2},
            .SkillLevels = {1, 1},
        };
        std::cout << "Expect -1 ," << c.Compare(c1, c2) << "\n";;
    }
    {
        Comparer::Charm c1
        {
            .Slots = {3, 1, 1},
            .Skills = {5, 6},
            .SkillLevels = {2, 2},
        };
        Comparer::Charm c2
        {
            .Slots = {1, 1, 0},
            .Skills = {5, 1},
            .SkillLevels = {1, 1},
        };
        std::cout << "Expect -1 ," << c.Compare(c1, c2) << "\n";;
    }

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
