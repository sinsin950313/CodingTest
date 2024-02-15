#include <iostream>
#include <utility>
#include <queue>

bool DecreaseByDivide3(std::pair<int, int> PairValue, std::pair<int, int>& ReturnValue)
{
    if(PairValue.first % 3 == 0)
    {
        ReturnValue = std::make_pair(PairValue.first / 3, PairValue.second + 1);
        return true;
    }
    return false;
}

bool DecreaseByDivide2(std::pair<int, int> PairValue, std::pair<int, int>& ReturnValue)
{
    if(PairValue.first % 2 == 0)
    {
        ReturnValue = std::make_pair(PairValue.first / 2, PairValue.second + 1);
        return true;
    }
    return false;
}

bool DecreaseBySub1(std::pair<int, int> PairValue, std::pair<int, int>& ReturnValue)
{
    ReturnValue = std::make_pair(PairValue.first - 1, PairValue.second + 1);
    return true;
}

int Solve()
{
    int Val = 0;
    std::cin >> Val;

    std::pair<int, int> CalculateValue = std::make_pair(Val, 0);
    std::queue<std::pair<int, int>> WorkingQueue;
    WorkingQueue.push(CalculateValue);
    while(CalculateValue.first != 1)
    {
        CalculateValue = WorkingQueue.front();
        WorkingQueue.pop();

        {
            std::pair<int, int> ReturnValue;
            if (DecreaseByDivide3(CalculateValue, ReturnValue))
            {
                WorkingQueue.push(ReturnValue);
            }
        }

        {
            std::pair<int, int> ReturnValue;
            if (DecreaseByDivide2(CalculateValue, ReturnValue))
            {
                WorkingQueue.push(ReturnValue);
            }
        }

        {
            std::pair<int, int> ReturnValue;
            if (DecreaseBySub1(CalculateValue, ReturnValue))
            {
                WorkingQueue.push(ReturnValue);
            }
        }
    }
    std::cout << CalculateValue.second;

    return 0;
}