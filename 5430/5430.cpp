#include <iostream>
#include <string>
#include <vector>

int Solve()
{
    int T;
    std::cin >> T;

    for(int i = 0; i < T; ++i)
    {
        std::string Functions;
        std::cin >> Functions;

        int InputCount;
        std::cin >> InputCount;

        std::string Input;
        std::cin >> Input;

        std::vector<int> DeQueue;
        std::string Val;
        for(int i = 0; i < Input.size(); ++i)
        {
            if(std::isdigit(Input[i]))
            {
                Val += Input[i];
            }
            else
            {
                if(!Val.empty())
                {
                    DeQueue.push_back(std::stoi(Val));
                    Val.clear();
                }
            }
        }

        bool IsReversed = false;
        int LeftIndex = 0;
        int RightIndex = DeQueue.size() - 1;

        bool IsError = false;;
        for(int j = 0; j < Functions.size(); ++j)
        {
            if(Functions[j] == 'R')
            {
                IsReversed = !IsReversed;
            }
            if(Functions[j] == 'D')
            {
                if(RightIndex < LeftIndex)
                {
                    IsError = true;
                    break;
                }
                else
                {
                    if(IsReversed)
                    {
                        --RightIndex;
                    }
                    else
                    {
                        ++LeftIndex;
                    }
                }
            }
        }

        if(IsError)
        {
            std::cout << "error" << std::endl;
        }
        else
        {
            std::cout << "[";

            int LastIndex = -1;
            if(IsReversed)
            {
                for(int i = RightIndex; LeftIndex < i; --i)
                {
                    std::cout << DeQueue[i] << ",";
                }
                if(LeftIndex <= RightIndex)
                {
                    LastIndex = LeftIndex;
                }
            }
            else
            {
                for(int i = LeftIndex; i < RightIndex; ++i)
                {
                    std::cout << DeQueue[i] << ",";
                }
                if(LeftIndex <= RightIndex)
                {
                    LastIndex = RightIndex;
                }
            }

            if(LastIndex != -1)
            {
                std::cout << DeQueue[LastIndex];
            }

            std::cout << "]" << std::endl;
        }
    }

    return 0;
}