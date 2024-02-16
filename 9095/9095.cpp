#include <iostream>

int Calculate(int Value, int DP[11])
{
    int Index = Value - 1;
    if(DP[Index] == 0)
    {
        DP[Index] = Calculate(Value - 1, DP) + Calculate(Value - 2, DP) + Calculate(Value - 3, DP);
    }
    return DP[Index];
}

int Solve()
{
    int DP[11] { 1, 2, 4, 7, };

    int T = 0;
    std::cin >> T;

    for(int i = 0; i < T; ++i)
    {
        int Val;
        std::cin >> Val;
        std::cout << Calculate(Val, DP) << std::endl;
    }

    return 0;
}