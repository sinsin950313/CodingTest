#include <iostream>
#include <vector>
#include <algorithm>

int Solve()
{
    int N = 0;
    std::cin >> N;

    std::vector<int> Waiting;
    for(int i = 0; i < N; ++i)
    {
        int Time;
        std::cin >> Time;
        Waiting.push_back(Time);
    }
    std::sort(Waiting.begin(), Waiting.end(), std::less<int>());

    int TotalCount = 0;
    int WaitingCount = 0;
    for(int Time : Waiting)
    {
        TotalCount += (Time + WaitingCount);
        WaitingCount += Time;
    }
    std::cout << TotalCount;

    return 0;
}