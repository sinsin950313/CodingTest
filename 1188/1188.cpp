#include <iostream>

int GCD(int A, int B)
{
    if(A < B)
    {
        A ^= B;
        B ^= A;
        A ^= B;
    }

    if(A % B == 0)
    {
        return B;
    }
    else
    {
        return GCD(B, A % B);
    }
}

int Solve()
{
    int N, M;
    std::cin >> N >> M;

    int Val = GCD(N, M);
    std::cout << Val * ((M / Val) - 1);

    return 0;
}