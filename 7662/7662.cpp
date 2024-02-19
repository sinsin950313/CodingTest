#include <iostream>
#include <set>
#include <queue>
#include <limits>

struct FData
{
    int Index;

    int Value;
};

int Solve()
{
    int T;
    std::cin >> T;

    while(T--)
    {
        struct FDataCompare
        {
            bool operator()(const FData &l, const FData &r) const { return l.Index < r.Index; }
        };
        std::set<FData, FDataCompare> DataSet;

        struct FDataMinComare
        {
            bool operator()(const FData &l, const FData &r)
            {
                if (l.Value != r.Value)
                {
                    return r.Value < l.Value;
                }
                return l.Index < r.Index;
            }
        };
        std::priority_queue<FData, std::vector<FData>, FDataMinComare> MinPriorityQueue;

        struct FDataMaxComare
        {
            bool operator()(const FData &l, const FData &r)
            {
                if (l.Value != r.Value)
                {
                    return l.Value < r.Value;
                }
                return l.Index < r.Index;
            }
        };
        std::priority_queue<FData, std::vector<FData>, FDataMaxComare> MaxPriorityQueue;

        int Q;
        std::cin >> Q;

        int Index = 0;
        while(Q--)
        {
            std::string Order;
            int Val;
            std::cin >> Order >> Val;

            if(Order == "I")
            {
                FData Data;
                Data.Index = Index;
                Data.Value = Val;

                ++Index;

                DataSet.insert(Data);
                MinPriorityQueue.push(Data);
                MaxPriorityQueue.push(Data);
            }
            else
            {
                if(Val == 1)
                {
                    bool Erased = false;
                    if(!DataSet.empty())
                    {
                        while (!Erased)
                        {
                            FData Data = MaxPriorityQueue.top();
                            MaxPriorityQueue.pop();

                            if(DataSet.find(Data) != DataSet.end())
                            {
                                DataSet.erase(Data);
                                Erased = true;
                            }
                        }
                    }
                }
                else
                {
                    bool Erased = false;
                    if(!DataSet.empty())
                    {
                        while (!Erased)
                        {
                            FData Data = MinPriorityQueue.top();
                            MinPriorityQueue.pop();

                            if(DataSet.find(Data) != DataSet.end())
                            {
                                DataSet.erase(Data);
                                Erased = true;
                            }
                        }
                    }
                }
            }
        }

        int MinValue = std::numeric_limits<int>::max();
        int MaxValue = std::numeric_limits<int>::min();
        for(const FData& Data : DataSet)
        {
            MinValue = std::min(Data.Value, MinValue);
            MaxValue = std::max(Data.Value, MaxValue);
        }

        if(DataSet.empty())
        {
            std::cout << "EMPTY" << std::endl;
        }
        else
        {
            std::cout << MaxValue << " " << MinValue << std::endl;
        }
    }

    return 0;
}