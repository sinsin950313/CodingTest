#include <iostream>
#include <queue>

int Solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N = 0;
    std::cin >> N;

    std::priority_queue<int, std::vector<int>, std::greater<int>> PriorityQueue;
    for(int i = 0; i < N; ++i)
    {
        int Input;
        std::cin >> Input;

        if(Input == 0)
        {
            if(PriorityQueue.empty())
            {
                std::cout << 0 << "\n";
            }
            else
            {
                std::cout << PriorityQueue.top() << "\n";
                PriorityQueue.pop();
            }
        }
        else
        {
            PriorityQueue.push(Input);
        }
    }

    return 0;
}