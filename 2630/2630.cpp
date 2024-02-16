#include <iostream>

std::pair<int, int> Divide(int Paper[128][128], int x, int y, int Size)
{
    int KeyValue = Paper[x][y];

    bool Divided = false;
    std::pair<int, int> PaperData = std::make_pair(0, 0);
    for(int i = x; i < x + Size; ++i)
    {
        for(int j = y; j < y + Size; ++j)
        {
            if(Paper[i][j] != KeyValue)
            {
                Divided = true;

                int NewSize = Size >> 1;
                {
                    std::pair<int, int> Temp = Divide(Paper, x, y, NewSize);
                    PaperData.first += Temp.first;
                    PaperData.second += Temp.second;
                }

                {
                    std::pair<int, int> Temp = Divide(Paper, x + NewSize, y, NewSize);
                    PaperData.first += Temp.first;
                    PaperData.second += Temp.second;
                }

                {
                    std::pair<int, int> Temp = Divide(Paper, x, y + NewSize, NewSize);
                    PaperData.first += Temp.first;
                    PaperData.second += Temp.second;
                }

                {
                    std::pair<int, int> Temp = Divide(Paper, x + NewSize, y + NewSize, NewSize);
                    PaperData.first += Temp.first;
                    PaperData.second += Temp.second;
                }

                break;
            }
        }

        if(Divided)
        {
            break;
        }
    }

    if(!Divided)
    {
        if(KeyValue == 0)
        {
            PaperData.first = 1;
        }
        else
        {
            PaperData.second = 1;
        }
    }

    return PaperData;
}

int Solve()
{
    int Size = 0;
    std::cin >> Size;

    int Paper[128][128];
    for(int i = 0; i < Size; ++i)
    {
        for(int j = 0; j < Size; ++j)
        {
            int Value = 0;
            std::cin >> Value;
            Paper[i][j] = Value;
        }
    }

    std::pair<int, int> Result = Divide(Paper, 0, 0, Size);

    std::cout << Result.first << std::endl << Result.second;

    return 0;
}