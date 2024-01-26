#include <iostream>
#include <set>
#include <memory>
#include <queue>
#include <functional>
#include <map>
#include <vector>

using FVertexIndex = int;

class FVertex
{
public:
    FVertex(FVertexIndex Index) : Index(Index) { }

public:
    FVertexIndex GetIndex() { return Index; }

    bool operator<(const FVertex& r) { return Index < r.Index; }

private:
    FVertexIndex Index;
};

using FEdgeIndex = int;

class FEdge
{
public:
    FEdge(FEdgeIndex Index, std::weak_ptr<FVertex> FirstVertex, std::weak_ptr<FVertex> SecondVertex, int Weight) : Index(Index), FirstVertex(FirstVertex), SecondVertex(SecondVertex), Weight(Weight) { }

public:
    int GetWeight() { return Weight; }

    bool operator<(const FEdge& r) { return Index < r.Index; }

    std::weak_ptr<FVertex> GetFirstVertex() { return FirstVertex; }

    std::weak_ptr<FVertex> GetSecondVertex() { return SecondVertex; }

    FEdgeIndex GetIndex() { return Index; }

private:
    FEdgeIndex Index;

    std::weak_ptr<FVertex> FirstVertex;

    std::weak_ptr<FVertex> SecondVertex;

    int Weight;
};

class FGraph
{
public:
    void GenerateGraph(int VertexCount);

    void RegisterEdge(FVertexIndex LeftVertexIndex, FVertexIndex RightVertexIndex, int EdgeWeight);

    std::weak_ptr<FVertex> GetVertex(FVertexIndex Index) { return *Vertexes.find(Index); }

    int GetVertexSize() { return Vertexes.size(); }

    class FWeakEdgeCompare
    {
    public:
        bool operator()(const std::weak_ptr<FEdge>& l, const std::weak_ptr<FEdge>& r) const { return l.lock()->operator<(*r.lock()); }
    };
    std::set<std::weak_ptr<FEdge>, FWeakEdgeCompare> GetEdges(std::weak_ptr<FVertex> Vertex);

private:
    class FSharedVertexCompare
    {
    public:
        using is_transparent = FVertexIndex;

        bool operator()(const std::shared_ptr<FVertex>& l, const std::shared_ptr<FVertex>& r) const { return l.get()->operator<(*r.get()); }

        bool operator()(const FVertexIndex& l, const std::shared_ptr<FVertex>& r) const { return l < r.get()->GetIndex(); }

        bool operator()(const std::shared_ptr<FVertex>& l, const FVertexIndex& r) const { return l.get()->GetIndex() < r; }
    };
    std::set<std::shared_ptr<FVertex>, FSharedVertexCompare> Vertexes;

    class FSharedEdgeCompare
    {
    public:
        bool operator()(const std::shared_ptr<FEdge>& l, const std::shared_ptr<FEdge>& r) const { return l->operator<(*r.get()); }
    };
    std::set<std::shared_ptr<FEdge>, FSharedEdgeCompare> Edges;

    class FWeakVertexCompare
    {
    public:
        bool operator()(const std::weak_ptr<FVertex>& l, const std::weak_ptr<FVertex>& r) const { return l.lock()->operator<(*r.lock()); }
    };
    std::map<std::weak_ptr<FVertex>, std::set<std::weak_ptr<FEdge>, FWeakEdgeCompare>, FWeakVertexCompare> EdgesConnectedToVertex;
};

void FGraph::GenerateGraph(int VertexCount)
{
    for(int i = 0; i < VertexCount; ++i)
    {
        std::shared_ptr<FVertex> Vertex = std::make_shared<FVertex>(i + 1);
        Vertexes.insert(Vertex);
        EdgesConnectedToVertex.insert(std::make_pair(Vertex, std::set<std::weak_ptr<FEdge>, FWeakEdgeCompare>()));
    }
}

void FGraph::RegisterEdge(FVertexIndex LeftVertexIndex, FVertexIndex RightVertexIndex, int EdgeWeight)
{
    int Index = Edges.size();
    std::weak_ptr<FVertex> LeftVertex = GetVertex(LeftVertexIndex);
    std::weak_ptr<FVertex> RightVertex = GetVertex(RightVertexIndex);
    std::shared_ptr<FEdge> Edge = std::make_shared<FEdge>(Index, LeftVertex, RightVertex, EdgeWeight);
    Edges.insert(Edge);

    {
        std::set<std::weak_ptr<FEdge>, FWeakEdgeCompare> &Edges = EdgesConnectedToVertex[LeftVertex];
        Edges.insert(Edge);
    }

    {
        std::set<std::weak_ptr<FEdge>, FWeakEdgeCompare> &Edges = EdgesConnectedToVertex[RightVertex];
        Edges.insert(Edge);
    }
}

std::set<std::weak_ptr<FEdge>, FGraph::FWeakEdgeCompare> FGraph::GetEdges(std::weak_ptr<FVertex> Vertex)
{
    return EdgesConnectedToVertex[Vertex];
}

class FPrimSpanningAlgorithm
{
public:
    int Spanning(FGraph& Graph);
};

int FPrimSpanningAlgorithm::Spanning(FGraph &Graph)
{
    int Weight = 0;

    std::weak_ptr<FVertex> InitialVertex = Graph.GetVertex(1);

    class FWeakPointerVertex
    {
    public:
        bool operator()(const std::weak_ptr<FVertex>& l, const std::weak_ptr<FVertex>& r) const { return l.lock()->GetIndex() < r.lock()->GetIndex(); }
    };
    std::set<std::weak_ptr<FVertex>, FWeakPointerVertex> ConnectedVertex;
    ConnectedVertex.insert(InitialVertex);

    std::function<bool(const std::weak_ptr<FEdge>&, const std::weak_ptr<FEdge>&)> EdgeCompare;
    EdgeCompare = [](const std::weak_ptr<FEdge>& l, const std::weak_ptr<FEdge>& r)->bool
    {
        FVertexIndex lIndex = l.lock()->GetIndex();
        FVertexIndex rIndex = r.lock()->GetIndex();
        if(lIndex != rIndex)
        {
            int lWeight = l.lock()->GetWeight();
            int rWeight = r.lock()->GetWeight();
            if(lWeight != rWeight)
            {
                return lWeight > rWeight;
            }
            else
            {
                FVertexIndex lFirstVertexIndex = l.lock()->GetFirstVertex().lock()->GetIndex();
                FVertexIndex rFirstVertexIndex = r.lock()->GetFirstVertex().lock()->GetIndex();
                FVertexIndex rSecondVertexIndex = r.lock()->GetSecondVertex().lock()->GetIndex();

                if(lFirstVertexIndex != rFirstVertexIndex)
                {
                    return lFirstVertexIndex < rFirstVertexIndex;
                }
                else
                {
                    return lFirstVertexIndex < rSecondVertexIndex;
                }
            }
        }
        return false;
    };
    std::priority_queue<std::weak_ptr<FEdge>, std::vector<std::weak_ptr<FEdge>>, decltype(EdgeCompare)> PriorityQueue(EdgeCompare);

    {
        std::set<std::weak_ptr<FEdge>, FGraph::FWeakEdgeCompare> Edges = Graph.GetEdges(InitialVertex);
        for(auto Edge : Edges)
        {
            PriorityQueue.push(Edge);
        }
    }

    while(ConnectedVertex.size() != Graph.GetVertexSize())
    {
        std::weak_ptr<FEdge> Edge = PriorityQueue.top();
        PriorityQueue.pop();

        std::weak_ptr<FVertex> LeftVertex = Edge.lock()->GetFirstVertex();
        std::weak_ptr<FVertex> RightVertex = Edge.lock()->GetSecondVertex();
        if(ConnectedVertex.find(LeftVertex) != ConnectedVertex.end() &&
        ConnectedVertex.find(RightVertex) != ConnectedVertex.end())
        {
            continue;
        }

        Weight += Edge.lock()->GetWeight();

        std::weak_ptr<FVertex> NewVertex;
        if(ConnectedVertex.find(Edge.lock()->GetFirstVertex()) != ConnectedVertex.end())
        {
            NewVertex = Edge.lock()->GetSecondVertex();
        }
        else
        {
            NewVertex = Edge.lock()->GetFirstVertex();
        }
        ConnectedVertex.insert(NewVertex);

        std::set<std::weak_ptr<FEdge>, FGraph::FWeakEdgeCompare> PossibleEdges = Graph.GetEdges(NewVertex);

        for(auto& PossibleEdge : PossibleEdges)
        {
            std::weak_ptr<FVertex> PossibleLeftVertex = PossibleEdge.lock()->GetFirstVertex();
            std::weak_ptr<FVertex> PossibleRightVertex = PossibleEdge.lock()->GetSecondVertex();
            if(ConnectedVertex.find(PossibleLeftVertex) == ConnectedVertex.end() || ConnectedVertex.find(PossibleRightVertex) == ConnectedVertex.end())
            {
                PriorityQueue.push(PossibleEdge);
            }
        }
    }

    return Weight;
}

class InputProcessor
{
public:
    void Process(FGraph& Graph);
};

void InputProcessor::Process(FGraph& Graph)
{
    int VertexCount, EdgeCount;
    std::cin >> VertexCount >> EdgeCount;

    Graph.GenerateGraph(VertexCount);

    for(int i = 0; i < EdgeCount; ++i)
    {
        FVertexIndex LeftVertexIndex, RightVertexIndex;
        int EdgeWeight;
        std::cin >> LeftVertexIndex >> RightVertexIndex >> EdgeWeight;

        Graph.RegisterEdge(LeftVertexIndex, RightVertexIndex, EdgeWeight);
    }
}

void Solve()
{
    InputProcessor Processor;
    FGraph Graph;

    Processor.Process(Graph);

    FPrimSpanningAlgorithm Prim;
    std::cout << Prim.Spanning(Graph);
}
