#include <iostream>
#include <queue>
#include <set>

int Solve()
{
    bool Network[101][101];
    for(int i = 1; i < 101; ++i)
    {
        for(int j = 1; j < 101; ++j)
        {
            Network[i][j] = false;
        }
    }

    int Computers = 0;
    std::cin >> Computers;

    int Connections = 0;
    std::cin >> Connections;
    for(int i = 0; i < Connections; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        Network[l][r] = true;
        Network[r][l] = true;
    }

    std::set<int> VirusedComputers;

    std::queue<int> VirusReservedComputers;
    VirusReservedComputers.push(1);
    while(!VirusReservedComputers.empty())
    {
        int CurrentComputer = VirusReservedComputers.front();
        VirusReservedComputers.pop();

        if(VirusedComputers.find(CurrentComputer) != VirusedComputers.end())
        {
            continue;
        }
        VirusedComputers.insert(CurrentComputer);

        for(int i = 1; i <= Computers; ++i)
        {
            if(Network[CurrentComputer][i])
            {
                VirusReservedComputers.push(i);
            }
        }
    }
    std::cout << VirusedComputers.size() - 1;

    return 0;
}