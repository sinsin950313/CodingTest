#include <iostream>
#include <limits>

int Map[500][500];
bool Visited[500][500];

bool IsIn(int Height, int Width, int Row, int Col)
{
    return 0 <= Row && Row < Height && 0 <= Col && Col < Width;
}

int DFS(int Height, int Width, int Row, int Col, int Depth, int Sum)
{
    if(IsIn(Height, Width, Row, Col))
    {
        if(Depth == 3)
        {
            return Map[Row][Col] + Sum;
        }
        else
        {
            Visited[Row][Col] = true;

            int MaxValue = Sum;
            const int dRow[4] {-1, 1, 0, 0};
            const int dCol[4] {0, 0, -1, 1};
            for(int i = 0; i < 4; ++i)
            {
                if(!Visited[Row + dRow[i]][Col + dCol[i]])
                {
                    MaxValue = std::max(MaxValue, DFS(Height, Width, Row + dRow[i], Col + dCol[i], Depth + 1, Sum + Map[Row][Col]));
                }
            }

            Visited[Row][Col] = false;

            return MaxValue;
        }
    }
    return 0;
}

int HalfCrossUp(int Height, int Width, int Row, int Col)
{
    if(IsIn(Height, Width, Row, Col - 1) && IsIn(Height, Width, Row + 1, Col) && IsIn(Height, Width, Row, Col - 1))
    {
        return Map[Row][Col - 1] + Map[Row][Col] + Map[Row + 1][Col] + Map[Row][Col + 1];
    }
    return 0;
}

int HalfCrossDown(int Height, int Width, int Row, int Col)
{
    if(IsIn(Height, Width, Row, Col - 1) && IsIn(Height, Width, Row - 1, Col) && IsIn(Height, Width, Row, Col - 1))
    {
        return Map[Row][Col - 1] + Map[Row][Col] + Map[Row - 1][Col] + Map[Row][Col + 1];
    }
    return 0;
}

int HalfCrossLeft(int Height, int Width, int Row, int Col)
{
    if(IsIn(Height, Width, Row, Col - 1) && IsIn(Height, Width, Row - 1, Col) && IsIn(Height, Width, Row + 1, Col))
    {
        return Map[Row][Col - 1] + Map[Row][Col] + Map[Row - 1][Col] + Map[Row + 1][Col];
    }
    return 0;
}

int HalfCrossRight(int Height, int Width, int Row, int Col)
{
    if(IsIn(Height, Width, Row, Col + 1) && IsIn(Height, Width, Row - 1, Col) && IsIn(Height, Width, Row + 1, Col))
    {
        return Map[Row][Col + 1] + Map[Row][Col] + Map[Row - 1][Col] + Map[Row + 1][Col];
    }
    return 0;
}

int Solve()
{
    int N, M;
    std::cin >> N >> M;

    for(int Row = 0; Row < N; ++Row)
    {
        for(int Col = 0; Col < M; ++Col)
        {
            int Val;
            std::cin >> Val;
            Map[Row][Col] = Val;
        }
    }

    int MaxValue = 0;
    for(int Row = 0; Row < N; ++Row)
    {
        for(int Col = 0; Col < M; ++Col)
        {
            MaxValue = std::max(DFS(N, M, Row, Col, 0, 0), MaxValue);
            MaxValue = std::max(HalfCrossUp(N, M, Row, Col), MaxValue);
            MaxValue = std::max(HalfCrossDown(N, M, Row, Col), MaxValue);
            MaxValue = std::max(HalfCrossLeft(N, M, Row, Col), MaxValue);
            MaxValue = std::max(HalfCrossRight(N, M, Row, Col), MaxValue);
        }
    }
    std::cout << MaxValue << std::endl;

    return 0;
}