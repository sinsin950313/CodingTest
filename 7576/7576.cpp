#include <iostream>
#include <limits>
#include <queue>
#include <set>

struct Node
{
    int WorkingDay;

    bool IsWorked;
};

Node Container[1001][1001];

bool IsIn(int Width, int Height, int Row, int Col)
{
    return 0 <= Col && Col < Width && 0 <= Row && Row < Height;
}

int Solve()
{
    int N, M;
    std::cin >> M >> N;

    const int cMaxDay = std::numeric_limits<int>::max();
    const int cBlocked = -1;

    std::queue<std::pair<int, int>> WorkingQueue;
    int TotalTomatoCount = 0;
    int WorkingTomatoCount = 0;
    for(int Row = 0; Row < N; ++Row)
    {
        for(int Col = 0; Col < M; ++Col)
        {
            int Val;
            std::cin >> Val;
            if(Val == 1)
            {
                WorkingQueue.push(std::make_pair(Row, Col));
                Container[Row][Col].IsWorked = true;
                Container[Row][Col].WorkingDay = 0;
                ++TotalTomatoCount;
            }
            else if(Val == -1)
            {
                Container[Row][Col].IsWorked = true;
                Container[Row][Col].WorkingDay = 0;
            }
            else
            {
                Container[Row][Col].IsWorked = false;
                Container[Row][Col].WorkingDay = cMaxDay;
                ++TotalTomatoCount;
            }
        }
    }

    const int dRow[4] {-1, 1, 0, 0};
    const int dCol[4] {0, 0, -1, 1};

    int MaxDay = 0;
    while(!WorkingQueue.empty())
    {
        std::pair<int, int> CurrentNode = WorkingQueue.front();
        WorkingQueue.pop();

        ++WorkingTomatoCount;

        MaxDay = Container[CurrentNode.first][CurrentNode.second].WorkingDay;

        for(int i = 0; i < 4; ++i)
        {
            int CurrentRow = CurrentNode.first + dRow[i];
            int CurrentCol = CurrentNode.second + dCol[i];
            if(IsIn(M, N, CurrentRow, CurrentCol))
            {
                if(Container[CurrentRow][CurrentCol].IsWorked == false)
                {
                    Container[CurrentRow][CurrentCol].WorkingDay = Container[CurrentNode.first][CurrentNode.second].WorkingDay + 1;
                    Container[CurrentRow][CurrentCol].IsWorked = true;
                    WorkingQueue.push(std::make_pair(CurrentRow, CurrentCol));
                }
            }
        }
    }
    std::cout << (WorkingTomatoCount == TotalTomatoCount ? MaxDay : -1);

    return 0;
}