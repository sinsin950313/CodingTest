#include <iostream>
#include <set>
#include <queue>

int Solve()
{
    bool Path[1001][1001];
    for(int i = 0; i < 1001; ++i)
    {
        for(int j = 0; j < 1001; ++j)
        {
            Path[i][j] = false;
        }
    }

    int N, M;
    std::cin >> N >> M;

    for(int i = 0; i < M; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        Path[l][r] = true;
        Path[r][l] = true;
    }

    int Count = 0;
    std::set<int> CheckedNode;
    for(int i = 1; i <= N; ++i)
    {
        if(CheckedNode.find(i) == CheckedNode.end())
        {
            std::queue<int> WorkingQueue;
            WorkingQueue.push(i);

            while(!WorkingQueue.empty())
            {
                int CurrentNode = WorkingQueue.front();
                WorkingQueue.pop();

                CheckedNode.insert(CurrentNode);

                for(int j = 1; j <= N; ++j)
                {
                    if(Path[CurrentNode][j])
                    {
                        WorkingQueue.push(j);
                        Path[CurrentNode][j] = false;
                        Path[j][CurrentNode] = false;
                    }
                }
            }

            ++Count;
        }
    }

    std::cout << Count;

    return 0;
}