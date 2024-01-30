#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

const int cNotFound = -1;

int Find(std::vector<int> &Values, int TargetValue)
{
    int Left = 0;
    int Right = Values.size() - 1;

    while (Left <= Right)
    {
        int Middle = (Left + Right) / 2;

        if (TargetValue < Values[Middle])
        {
            Right = Middle - 1;
        }
        else if (Values[Middle] < TargetValue)
        {
            Left = Middle + 1;
        }
        else
        {
            return Middle;
        }
    }
    return cNotFound;
}

int Solve()
{
    int Count;
    std::cin >> Count;

    if (Count < 3)
    {
        std::cout << 0;
    }

    else
    {
        std::vector<int> Values;
        std::map<int, int> Datas;
        for (int i = 0; i < Count; ++i)
        {
            int Val;
            std::cin >> Val;
            Values.push_back(Val);

            if (Datas.find(Val) == Datas.end())
            {
                Datas.insert(std::make_pair(Val, 0));
            }
            Datas[Val] += 1;
        }

        std::sort(Values.begin(), Values.end());
        std::set<int> Check;

        int Result = 0;
        for (int i = 0; i < Count - 1; ++i)
        {
            for (int j = i + 1; j < Count; ++j)
            {
                int Val = Values[i] + Values[j];
                if (Check.find(Val) == Check.end())
                {
                    int Index = Find(Values, Val);

                    if (Index != cNotFound)
                    {
                        Check.insert(Val);
                        Result += Datas[Val];

                        if (Values[i] == 0 || Values[j] == 0)
                        {
                            if (Values[i] == 0 && Values[j] == 0)
                            {
                                if (Datas[Val] == 2)
                                {
                                    Result -= 2;
                                    Check.erase(Val);
                                }
                            }
                            else
                            {
                                if (Datas[Val] == 1)
                                {
                                    Result -= 1;
                                    Check.erase(Val);
                                }
                            }
                        }
                    }
                }

            }
        }
        std::cout << Result;

        return 0;
    }
}