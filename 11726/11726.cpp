#include <iostream>

long long Calculate(long long DP[1001], int n)
{
    if(DP[n] == 0)
    {
        DP[n] = (Calculate(DP, n - 1) + Calculate(DP, n - 2)) % 10007;
    }
    return DP[n];
}

int Solve()
{
    long long DP[1001] { 0, 1, 2, };

    int n;
    std::cin >> n;

    std::cout << (Calculate(DP, n) % 10007);

    return 0;
}