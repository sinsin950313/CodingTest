#include <map>
#include <string>
#include <iostream>

int Solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::map<std::string, std::string> NumberToNameDictionary;
    std::map<std::string, std::string> NameToNumberDictionary;

    int N = 0, M = 0;
    std::cin >> N >> M;
    for(int i = 0; i < N; ++i)
    {
        std::string Name;
        std::cin >> Name;
        NumberToNameDictionary.insert(std::make_pair(std::to_string(i + 1), Name));
        NameToNumberDictionary.insert(std::make_pair(Name, std::to_string(i + 1)));
    }

    for(int i = 0; i < M; ++i)
    {
        std::string Input;
        std::cin >> Input;
        if('0' <= Input[0] && Input[0] <= '9')
        {
            std::cout << NumberToNameDictionary[Input] << "\n";
        }
        else
        {
            std::cout << NameToNumberDictionary[Input] << "\n";
        }
    }

    return 0;
}