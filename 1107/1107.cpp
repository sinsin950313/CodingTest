#include <iostream>
#include <string>

bool IsPossibleChannel(bool IsButtonBroken[10], int Channel)
{
    std::string ChannelString = std::to_string(Channel);
    for(int i = 0; i < ChannelString.size(); ++i)
    {
        if(IsButtonBroken[ChannelString[i] - '0'] == true)
        {
            return false;
        }
    }
    return true;
}

int Solve()
{
    int TargetChannel;
    std::cin >> TargetChannel;

    int BrokenButtonCount;
    std::cin >> BrokenButtonCount;

    bool IsButtonBroken[10];
    for(int i = 0; i < 10; ++i)
    {
        IsButtonBroken[i] = false;
    }

    for(int i = 0; i < BrokenButtonCount; ++i)
    {
        int Index;
        std::cin >> Index;
        IsButtonBroken[Index] = true;
    }

    int MinDelta = std::abs(TargetChannel - 100);
    for(int i = 0; i < 1000000; ++i)
    {
        if(IsPossibleChannel(IsButtonBroken, i))
        {
            MinDelta = std::min(MinDelta, (std::abs(TargetChannel - i) + (int)std::to_string(i).size()));
        }
    }

    std::cout << MinDelta;

    return 0;
}