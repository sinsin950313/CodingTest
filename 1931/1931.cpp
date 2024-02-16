#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

int Solve()
{
    int N = 0;
    std::cin >> N;

    std::vector<std::pair<int, int>> ConferenceList;
    for(int i = 0; i < N; ++i)
    {
        int Start = 0, End = 0;
        std::cin >> Start >> End;
        ConferenceList.push_back(std::make_pair(Start, End));
    }

    auto Compare = [](const std::pair<int, int>& l, const std::pair<int, int>& r)
    {
        if(l.second != r.second)
        {
            return l.second < r.second;
        }
        return l.first < r.first;
    };
    std::sort(ConferenceList.begin(), ConferenceList.end(), Compare);

    int MaximumCount = 0;
    int PivotTime = ConferenceList[0].first;
    for(std::pair<int, int>& Time : ConferenceList)
    {
        if(PivotTime <= Time.first)
        {
            PivotTime = Time.second;
            ++MaximumCount;
        }
    }
    std::cout << MaximumCount;

    return 0;
}