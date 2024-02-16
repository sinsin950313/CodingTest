#include <iostream>

int Solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N = 0, M = 0;
    std::cin >> N >> M;

    int AccumulateValue[100001] = { 0, };
    for(int i = 0; i < N; ++i)
    {
        int Value;
        std::cin >> Value;
        AccumulateValue[i + 1] = Value + AccumulateValue[i];
    }

    for(int i = 0; i < M; ++i)
    {
        int From, To;
        std::cin >> From >> To;
        std::cout << AccumulateValue[To] - AccumulateValue[From - 1] << "\n";
    }

    return 0;
}