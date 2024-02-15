#include <iostream>
#include <queue>
#include <utility>

std::pair<int, int> MoveLeft(std::pair<int, int> Data)
{
    return std::make_pair(Data.first - 1, Data.second + 1);
}

std::pair<int, int> MoveRight(std::pair<int, int> Data)
{
    return std::make_pair(Data.first + 1, Data.second + 1);
}

std::pair<int, int> MoveWarp(std::pair<int, int> Data)
{
    return std::make_pair(Data.first * 2, Data.second + 1);
}

int Solve()
{
    int N = 0, K = 0;

    std::cin >> N >> K;
    std::pair<int, int> CurrentData = std::make_pair(N, 0);
    std::queue<std::pair<int, int>> WorkingQueue;
    WorkingQueue.push(CurrentData);

    bool Visited[100001];
    for(int i = 0; i < 100001; ++i)
    {
        Visited[i] = false;
    }

    while (CurrentData.first != K)
    {
        CurrentData = WorkingQueue.front();
        WorkingQueue.pop();

        {
            std::pair<int, int> NewPos = MoveWarp(CurrentData);
            if (0 <= NewPos.first && NewPos.first <= 100000)
            {
                if (Visited[NewPos.first] == false)
                {
                    WorkingQueue.push(NewPos);
                    Visited[NewPos.first] = true;
                }
            }
        }

        {
            std::pair<int, int> NewPos = MoveLeft(CurrentData);
            if (0 <= NewPos.first && NewPos.first <= 100000)
            {
                if (Visited[NewPos.first] == false)
                {
                    WorkingQueue.push(NewPos);
                    Visited[NewPos.first] = true;
                }
            }
        }

        {
            std::pair<int, int> NewPos = MoveRight(CurrentData);
            if (0 <= NewPos.first && NewPos.first <= 100000)
            {
                if (Visited[NewPos.first] == false)
                {
                    WorkingQueue.push(NewPos);
                    Visited[NewPos.first] = true;
                }
            }
        }
    }
    std::cout << CurrentData.second;

    return 0;
}