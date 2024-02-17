#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

int Solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::set<int> OriginSet;
    std::vector<int> OriginVector;
    for(int i =0; i < N; ++i)
    {
        int Val;
        std::cin >> Val;
        OriginSet.insert(Val);
        OriginVector.push_back(Val);
    }

    std::vector<int> CompressVector;
    for(int Val : OriginSet)
    {
        CompressVector.push_back(Val);
    }
    std::sort(CompressVector.begin(), CompressVector.end(), std::less<int>());

    std::map<int, int> CompressMap;
    for(int i = 0; i < CompressVector.size(); ++i)
    {
        CompressMap.insert(std::make_pair(CompressVector[i], i));
    }

    for(int Val : OriginVector)
    {
        std::cout << CompressMap[Val] << " ";
    }

    return 0;
}