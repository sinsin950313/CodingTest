#include <iostream>
#include <memory>
#include <limits>
#include <queue>
#include <set>
#include <functional>

class FMaze
{
public:
    void SetSize(int Width, int Height);

    void SetRoom(int x, int y, int Weight);

    int GetWidth() { return Width; }

    int GetHeight() { return Height; }

    int GetWeight(std::pair<int, int> From, std::pair<int, int> To);

private:
    int GetIndex(int x, int y) { return (y - 1) * Width + (x - 1);}

    int* GetRoom(int x, int y) { return &Room.get()[GetIndex(x, y)]; }

    bool IsIn(int x, int y);

private:
    int Width;

    int Height;

    std::unique_ptr<int[]> Room;
};

void FMaze::SetSize(int Width, int Height)
{
    this->Width = Width;
    this->Height = Height;

    Room = std::make_unique<int[]>(Width * Height);
}

void FMaze::SetRoom(int x, int y, int Weight)
{
    *GetRoom(x, y) = Weight;
}

int FMaze::GetWeight(std::pair<int, int> From, std::pair<int, int> To)
{
    std::unique_ptr<int[]> DijkstraMap = std::make_unique<int[]>(Width * Height);
    for(int i = 1; i <= Width; ++i)
    {
        for(int j = 1; j <= Height; ++j)
        {
            DijkstraMap.get()[GetIndex(i, j)] = std::numeric_limits<int>::max();
        }
    }
    DijkstraMap.get()[GetIndex(1, 1)] = 0;

    std::function<bool(const std::pair<int, int> &, const std::pair<int, int> &)> Function = [this, &DijkstraMap](const std::pair<int, int> &l, const std::pair<int, int> &r)
    {
        return DijkstraMap.get()[this->GetIndex(l.first, l.second)] > DijkstraMap.get()[this->GetIndex(r.first, r.second)];
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(Function)> Queue(Function);
    Queue.push(std::make_pair(1, 1));

    std::set<std::pair<int, int>> Visited;

    const int dx[] = {-1,  1,  0,  0};
    const int dy[] = { 0,  0,  1, -1};
    while (!Queue.empty())
    {
        std::pair<int, int> CurrentPos = Queue.top();
        Queue.pop();

        if(Visited.find(CurrentPos) != Visited.end())
        {
            continue;
        }
        Visited.insert(CurrentPos);

        for (int i = 0; i < 4; ++i)
        {
            int PosX = CurrentPos.first + dx[i];
            int PosY = CurrentPos.second + dy[i];
            if (IsIn(PosX, PosY))
            {
                int CurrentVal = DijkstraMap.get()[GetIndex(CurrentPos.first, CurrentPos.second)];
                int NextVal = Room.get()[GetIndex(PosX, PosY)];
                int BeforeVal = DijkstraMap.get()[GetIndex(PosX, PosY)];
                int NewVal = std::min(CurrentVal + NextVal, BeforeVal);
                DijkstraMap.get()[GetIndex(PosX, PosY)] = NewVal;

                std::pair<int, int> NewPos = std::make_pair(PosX, PosY);
                Queue.push(NewPos);
            }
        }
    }

    return DijkstraMap.get()[GetIndex(Width, Height)];
}

bool FMaze::IsIn(int x, int y)
{
    return (1 <= x) && (x <= GetWidth()) && (1 <= y) && (y <= GetHeight());
}

class FInputProcessor
{
public:
    void Process(FMaze& Maze);
};

void FInputProcessor::Process(FMaze& Maze)
{
    int Width, Height;
    std::cin >> Width >> Height;

    Maze.SetSize(Width, Height);

    for(int i = 1; i <= Height; ++i)
    {
        for(int j = 1; j <= Width; ++j)
        {
            char Val;
            std::cin >> Val;
            Maze.SetRoom(j, i, Val - '0');
        }
    }
}

int Solve()
{
    FInputProcessor Processor;

    FMaze Maze;
    Processor.Process(Maze);

    std::cout << Maze.GetWeight(std::make_pair(0, 0), std::make_pair(Maze.GetWidth(), Maze.GetHeight()));

    return 0;
}
