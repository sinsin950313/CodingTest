#include <iostream>
#include <set>
#include <string>

int Solve()
{
    int N = 0, M = 0;
    std::cin >> N >> M;

    std::set<std::string> NotHeared;
    for(int i = 0; i < N; ++i)
    {
        std::string Name;
        std::cin >> Name;
        NotHeared.insert(Name);
    }

    std::set<std::string> NotSeen;
    int Count = 0;
    for(int i = 0; i < M; ++i)
    {
        std::string Name;
        std::cin >> Name;
        if(NotHeared.find(Name) != NotHeared.end())
        {
            NotSeen.insert(Name);
            ++Count;
        }
    }

    std::cout << Count << std::endl;
    for(std::string Name : NotSeen)
    {
        std::cout << Name << std::endl;
    }

    return 0;
}