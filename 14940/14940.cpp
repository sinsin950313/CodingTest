#include <iostream>
#include <utility>
#include <queue>
#include <limits>

bool IsIn(int Row, int Col, int Width, int Height)
{
    return 0 <= Row && Row < Height && 0 <= Col && Col < Width;
}

int Map[1000][1000];

int Solve()
{
    const int cBlocked = 0;
    const int cConnected = std::numeric_limits<int>::max();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::pair<int, int> Start;
    for (int Row = 0; Row < n; ++Row)
    {
        for (int Col = 0; Col < m; ++Col)
        {
            int Val;
            std::cin >> Val;
            if (Val == 0)
            {
                Map[Row][Col] = cBlocked;
            }
            else if (Val == 1)
            {
                Map[Row][Col] = cConnected;
            }
            else if (Val == 2)
            {
                Start = std::make_pair(Row, Col);
                Map[Row][Col] = 0;
            }
        }
    }

    std::queue<std::pair<int, int>> WorkingQueue;
    WorkingQueue.push(Start);

    const int dRow[4]{-1, 1, 0, 0};
    const int dCol[4]{0, 0, -1, 1};
    while (!WorkingQueue.empty())
    {
        std::pair<int, int> CurrentNode = WorkingQueue.front();
        WorkingQueue.pop();

        for (int i = 0; i < 4; ++i)
        {
            int NextRow = CurrentNode.first + dRow[i];
            int NextCol = CurrentNode.second + dCol[i];

            if (IsIn(NextRow, NextCol, m, n))
            {
                if (Map[NextRow][NextCol] != cBlocked && Map[NextRow][NextCol] == cConnected)
                {
                    Map[NextRow][NextCol] = Map[CurrentNode.first][CurrentNode.second] + 1;
                    WorkingQueue.push(std::make_pair(NextRow, NextCol));
                }
            }
        }
    }

    for (int Row = 0; Row < n; ++Row)
    {
        for (int Col = 0; Col < m; ++Col)
        {
            if (Map[Row][Col] == cConnected)
            {
                std::cout << -1 << " ";
            }
            else
            {
                std::cout << Map[Row][Col] << " ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}