#include <iostream>
#include <map>
#include <set>
#include <memory>
#include <limits>
#include <queue>
#include <cmath>

class FMap
{
public:
    void InstallGenerator(int Index, int X, int Y);

    void SetLimit(double Limit) { DoubleLimit = Limit * Limit; DoubleLimit = std::sqrt(DoubleLimit); }

    void Link(int Index1, int Index2);

    double Rebuild();

private:
    class FGenerator
    {
    public:
        FGenerator(int Index, int X, int Y) : Index(Index), Position(std::make_pair(X, Y)) {}

    public:
        std::pair<int, int> GetPosition() { return Position; }

        int GetIndex() { return Index; }

    private:
        int Index;

        std::pair<int, int> Position;
    };
    std::map<int, std::shared_ptr<FGenerator>> GeneratorMap;

    double DoubleLimit;

    class FCluster
    {
    public:
        FCluster(int Index) : Index(Index) { }

    public:
        void RegisterGenerator(std::weak_ptr<FGenerator> Generator) { LinkedGenerators.insert(Generator); }

        void MergeCluster(std::unique_ptr<FCluster>& Cluster)
        {
            for(std::weak_ptr<FGenerator> Generator : Cluster.get()->LinkedGenerators)
            {
                LinkedGenerators.insert(Generator);
            }
        }

        bool AlreadyRegisteredGenerator(std::weak_ptr<FGenerator> Generator) { return LinkedGenerators.find(Generator) != LinkedGenerators.end(); }

        std::vector<std::weak_ptr<FGenerator>> GetGenerators()
        {
            std::vector<std::weak_ptr<FGenerator>> Ret;
            for(std::weak_ptr<FGenerator> Generator : LinkedGenerators)
            {
                Ret.push_back(Generator);
            }
            return Ret;
        }

        int GetIndex() { return Index; }

    private:
        int Index;

        class FWeakGeneratorCompare
        {
        public:
            bool operator()(const std::weak_ptr<FGenerator>& l, const std::weak_ptr<FGenerator>& r) const { return l.lock()->GetIndex() < r.lock()->GetIndex(); }
        };
        std::set<std::weak_ptr<FGenerator>, FWeakGeneratorCompare> LinkedGenerators;
    };

    std::vector<std::unique_ptr<FCluster>> Clusters;

    std::vector<std::unique_ptr<FCluster>>::iterator FindCluster(std::weak_ptr<FGenerator> Generator);

    void MergeCluster(std::unique_ptr<FCluster>& From, std::unique_ptr<FCluster>& To);
};

void FMap::InstallGenerator(int Index, int X, int Y)
{
    std::shared_ptr<FGenerator> Generator = std::make_shared<FGenerator>(Index, X, Y);
    GeneratorMap.insert(std::make_pair(Index, Generator));

    std::unique_ptr<FCluster> Cluster = std::make_unique<FCluster>(Index);
    Cluster.get()->RegisterGenerator(Generator);

    Clusters.push_back(std::move(Cluster));
}

void FMap::Link(int Index1, int Index2)
{
    std::shared_ptr<FGenerator> Generator1 = GeneratorMap[Index1];
    std::shared_ptr<FGenerator> Generator2 = GeneratorMap[Index2];

    std::vector<std::unique_ptr<FCluster>>::iterator Cluster1Iter = FindCluster(Generator1);
    std::vector<std::unique_ptr<FCluster>>::iterator Cluster2Iter = FindCluster(Generator2);

    MergeCluster(*Cluster2Iter, *Cluster1Iter);
}

double FMap::Rebuild()
{
    using FDistance = double;

    int Size = static_cast<int>(GeneratorMap.size());

    std::unique_ptr<FDistance[]> Map = std::make_unique<FDistance[]>(Size);
    for(int i = 0; i < Size; ++i)
    {
        Map.get()[i] = std::numeric_limits<FDistance>::max() / 2;
    }

    auto GetGeneratorIndexLambda = [](int GeneratorIndex) { return GeneratorIndex - 1; };
    Map.get()[GetGeneratorIndexLambda(1)] = 0.0;

    std::shared_ptr<FGenerator> OriginGenerator = GeneratorMap[1];

    class FGeneratorDistancePairCompare
    {
    public:
        bool operator()(const std::pair<std::weak_ptr<FGenerator>, FDistance> &l, const std::pair<std::weak_ptr<FGenerator>, FDistance> &r) const
        {
            if(l.second != r.second)
            {
                return l.second > r.second;
            }
            else
            {
                return l.first.lock()->GetIndex() > r.first.lock()->GetIndex();
            }
        }
    };
    std::priority_queue<std::pair<std::weak_ptr<FGenerator>, FDistance>, std::vector<std::pair<std::weak_ptr<FGenerator>, FDistance>>, FGeneratorDistancePairCompare> PriorityQueue;
    for(std::weak_ptr<FGenerator> Generator : (*FindCluster(OriginGenerator))->GetGenerators())
    {
        Map.get()[GetGeneratorIndexLambda(Generator.lock()->GetIndex())] = 0.0;
        PriorityQueue.push(std::make_pair(Generator, 0.0));
    }

    class FGeneratorCompare
    {
    public:
        bool operator()(const std::weak_ptr<FGenerator>& l, const std::weak_ptr<FGenerator>& r) const { return l.lock()->GetIndex() < r.lock()->GetIndex(); }
    };
    std::set<std::weak_ptr<FGenerator>, FGeneratorCompare> Visited;
    while(!PriorityQueue.empty())
    {
        std::pair<std::weak_ptr<FGenerator>, FDistance> CurrentGeneratorData = PriorityQueue.top();
        PriorityQueue.pop();

        if(Visited.find(CurrentGeneratorData.first) != Visited.end())
        {
            continue;
        }
        Visited.insert(CurrentGeneratorData.first);

        std::vector<std::unique_ptr<FMap::FCluster>>::iterator CurrentClusterIter = FindCluster(CurrentGeneratorData.first);
        std::vector<std::unique_ptr<FMap::FCluster>>::iterator OriginClusterIter = FindCluster(OriginGenerator);
        if (CurrentClusterIter != OriginClusterIter)
        {
            for(auto Generator : (*CurrentClusterIter).get()->GetGenerators())
            {
                Map.get()[GetGeneratorIndexLambda(Generator.lock()->GetIndex())] = Map.get()[GetGeneratorIndexLambda(CurrentGeneratorData.first.lock()->GetIndex())];
            }
            MergeCluster(*CurrentClusterIter, *OriginClusterIter);
        }
        OriginClusterIter = FindCluster(OriginGenerator);

        auto GetMinimumDistance = [](const std::unique_ptr<FCluster>& l, const std::weak_ptr<FGenerator>& r)
        {
            FDistance Distance = std::numeric_limits<FDistance>::max();
            for(std::weak_ptr<FGenerator> lIter : l->GetGenerators())
            {
                FDistance Width = lIter.lock()->GetPosition().first - r.lock()->GetPosition().first;
                FDistance Height = lIter.lock()->GetPosition().second - r.lock()->GetPosition().second;
                Distance = std::fmin((Width * Width) + (Height * Height), Distance);
            }
            return std::sqrt(Distance);
        };
        for(std::unique_ptr<FCluster>& Cluster : Clusters)
        {
            int CurrentGeneratorIndex = GetGeneratorIndexLambda(CurrentGeneratorData.first.lock()->GetIndex());
            FDistance CurrentDistance = Map.get()[CurrentGeneratorIndex];
            if(Cluster.get() != (*OriginClusterIter).get())
            {
                FDistance Distance = GetMinimumDistance(Cluster, CurrentGeneratorData.first);
                if(Distance <= DoubleLimit)
                {
                    for (std::weak_ptr<FGenerator> Generator : Cluster->GetGenerators())
                    {
                        int NextGeneratorIndex = GetGeneratorIndexLambda(Generator.lock()->GetIndex());
                        Map.get()[NextGeneratorIndex] = std::fmin(Map.get()[NextGeneratorIndex], CurrentDistance + Distance);
                        PriorityQueue.push(std::make_pair(Generator, Map.get()[CurrentGeneratorIndex]));
                    }
                }
            }
        }
    }

    std::shared_ptr<FGenerator> TargetGenerator = GeneratorMap[static_cast<int>(GeneratorMap.size())];
    return Map.get()[GetGeneratorIndexLambda(TargetGenerator.get()->GetIndex())];
}

std::vector<std::unique_ptr<FMap::FCluster>>::iterator FMap::FindCluster(std::weak_ptr<FGenerator> Generator)
{
    for(std::vector<std::unique_ptr<FCluster>>::iterator Iter = Clusters.begin(); Iter != Clusters.end(); ++Iter)
    {
        if((*Iter).get()->AlreadyRegisteredGenerator(Generator))
        {
            return Iter;
        }
    }
    return Clusters.end();
}

void FMap::MergeCluster(std::unique_ptr<FCluster> &From, std::unique_ptr<FCluster> &To)
{
    if(From.get()->GetIndex() != To.get()->GetIndex())
    {
        To.get()->MergeCluster(From);

        for (std::vector<std::unique_ptr<FCluster>>::iterator Iter = Clusters.begin(); Iter != Clusters.end(); ++Iter)
        {
            if ((*Iter).get()->GetIndex() == From.get()->GetIndex())
            {
                Clusters.erase(Iter);
                break;
            }
        }
    }
}

class FInputProcessor
{
public:
    void Process(FMap& Map);
};

void FInputProcessor::Process(FMap& Map)
{
    int N, W;
    std::cin >> N >> W;

    double M;
    std::cin >> M;
    Map.SetLimit(M);

    for(int i = 1; i <= N; ++i)
    {
        int X, Y;
        std::cin >> X >> Y;
        Map.InstallGenerator(i, X, Y);
    }

    for(int i = 0; i < W; ++i)
    {
        int N1, N2;
        std::cin >> N1 >> N2;
        Map.Link(N1, N2);
    }
}

int Solve()
{
    FMap Map;

    FInputProcessor Processor;
    Processor.Process(Map);

    double fWire = Map.Rebuild();
    int iWire = static_cast<int>(fWire * 1000);
    std::cout << iWire;

    return 0;
}