#include <iostream>
#include <string>
#include <queue>
#include <string>
#include <cstring>

int Solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    bool Visited[10000];

    int T;
    std::cin >> T;
    while(T--)
    {
        int A, B;
        std::cin >> A >> B;

        std::memset(Visited, false, sizeof(Visited));

        std::queue<std::pair<int, std::string>> WorkingQueue;
        WorkingQueue.push(std::make_pair(A, ""));
        while(!WorkingQueue.empty())
        {
            std::pair<int, std::string> CurrentNode = WorkingQueue.front();
            WorkingQueue.pop();

            if(CurrentNode.first == B)
            {
                std::cout << CurrentNode.second << "\n";
                break;
            }

            {
                std::pair<int, std::string> NextNode;
                NextNode.second = CurrentNode.second + "D";
                NextNode.first = (CurrentNode.first * 2) % 10000;
                if(Visited[NextNode.first] == false)
                {
                    Visited[NextNode.first] = true;
                    WorkingQueue.push(NextNode);
                }
            }

            {
                std::pair<int, std::string> NextNode;
                NextNode.second = CurrentNode.second + "S";
                NextNode.first = CurrentNode.first - 1 < 0 ? 9999 : CurrentNode.first - 1;
                if(Visited[NextNode.first] == false)
                {
                    Visited[NextNode.first] = true;
                    WorkingQueue.push(NextNode);
                }
            }

            {
                std::pair<int, std::string> NextNode;
                NextNode.second = CurrentNode.second + "L";
                NextNode.first = (CurrentNode.first % 1000) * 10 + CurrentNode.first / 1000;
                if(Visited[NextNode.first] == false)
                {
                    Visited[NextNode.first] = true;
                    WorkingQueue.push(NextNode);
                }
            }

            {
                std::pair<int, std::string> NextNode;
                NextNode.second = CurrentNode.second + "R";
                NextNode.first = CurrentNode.first / 10 + (CurrentNode.first % 10) * 1000;
                if(Visited[NextNode.first] == false)
                {
                    Visited[NextNode.first] = true;
                    WorkingQueue.push(NextNode);
                }
            }
        }
    }

    return 0;
}