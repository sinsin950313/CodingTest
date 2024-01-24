#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <set>

struct FRectInfo
{
    FRectInfo(int Left, int Bottom, int Right, int Top) : Left(Left), Bottom(Bottom), Right(Right), Top(Top) {}

    int GetSize() const { return (Right - Left) * (Top - Bottom); }

    bool operator<(const FRectInfo& r) const
    {
        if(!((Left == r.Left) && (Right == r.Right) && (Top == r.Top) && (Bottom != r.Bottom)))
        {
            int Size = GetSize();
            int rSize = r.GetSize();
            if(Size != rSize)
            {
                return Size < rSize;
            }
            else
            {
                if(Left != r.Left)
                {
                    return Left < r.Left;
                }
                else if(Right != r.Right)
                {
                    return Right < r.Right;
                }
                else
                {
                    return Top < r.Top;
                }
            }
        }
        return true;
    }

    bool IsNotOverlap(const FRectInfo &RectInfo) const
    {
        return (RectInfo.Right <= Left) || (Right <= RectInfo.Left) || (RectInfo.Top <= Bottom) || (Top <= RectInfo.Bottom);
    }

    bool IsOverlap(const FRectInfo &RectInfo) const
    {
        return !IsNotOverlap(RectInfo);
    }

    std::vector<FRectInfo> operator-(FRectInfo RectInfo);

public:
    int Left, Right, Bottom, Top;
};

std::vector<FRectInfo> FRectInfo::operator-(FRectInfo RectInfo)
{
    std::vector<FRectInfo> Ret;
    if(!IsOverlap(RectInfo))
    {
        return Ret;
    }

    if(Left < RectInfo.Left)
    {
        Ret.push_back(FRectInfo(Left, Bottom, RectInfo.Left, Top));

        if(RectInfo.Right < Right)
        {
            Ret.push_back(FRectInfo(RectInfo.Right, Bottom, Right, Top));

            if(Bottom < RectInfo.Bottom)
            {
                Ret.push_back(FRectInfo(RectInfo.Left, Bottom, RectInfo.Right, RectInfo.Bottom));

                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Top, RectInfo.Right, Top));
                    // Ret.push_back(RectInfo);
                }
                else
                {
                    // Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Bottom, RectInfo.Right, Top));
                }
            }
            else
            {
                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Top, RectInfo.Right, Top));
                    // Ret.push_back(FRectInfo(RectInfo.Left, Bottom, RectInfo.Right, RectInfo.Top));
                }
                else
                {
                    // Ret.push_back(FRectInfo(RectInfo.Left, Bottom, RectInfo.Right, Top));
                }
            }
        }
        else
        {
            if(Bottom < RectInfo.Bottom)
            {
                Ret.push_back(FRectInfo(RectInfo.Left, Bottom, Right, RectInfo.Bottom));

                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Top, Right, Top));
                    // Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Bottom, Right, RectInfo.Top));
                }
                else
                {
                    // Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Bottom, Right, Top));
                }
            }
            else
            {
                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Top, Right, Top));
                    // Ret.push_back(FRectInfo(RectInfo.Left, Bottom, Right, RectInfo.Bottom));
                }
                else
                {
                    // Ret.push_back(FRectInfo(RectInfo.Left, Bottom, Right, Top));
                }
            }
        }
    }
    else
    {
        if(RectInfo.Right < Right)
        {
            Ret.push_back(FRectInfo(RectInfo.Right, Bottom, Right, Top));

            if(Bottom < RectInfo.Bottom)
            {
                Ret.push_back(FRectInfo(Left, Bottom, RectInfo.Right, RectInfo.Bottom));

                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(Left, RectInfo.Top, RectInfo.Right, Top));
                    // Ret.push_back(FRectInfo(Left, RectInfo.Bottom, RectInfo.Right, RectInfo.Top));
                }
                else
                {
                    // Ret.push_back(FRectInfo(Left, RectInfo.Bottom, RectInfo.Right, Top));
                }
            }
            else
            {
                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(Left, RectInfo.Top, RectInfo.Right, Top));
                    // Ret.push_back(FRectInfo(Left, Bottom, Right, RectInfo.Top));
                }
                else
                {
                    // Ret.push_back(FRectInfo(RectInfo.Left, RectInfo.Bottom, RectInfo.Right, Top));
                }
            }
        }
        else
        {
            if(Bottom < RectInfo.Bottom)
            {
                Ret.push_back(FRectInfo(Left, Bottom, Right, RectInfo.Bottom));

                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(Left, RectInfo.Top, Right, Top));
                    // Ret.push_back(FRectInfo(Left, RectInfo.Bottom, Right, RectInfo.Top));
                }
                else
                {
                    // Ret.push_back(FRectInfo(Left, RectInfo.Bottom, Right, Top));
                }
            }
            else
            {
                if(RectInfo.Top < Top)
                {
                    Ret.push_back(FRectInfo(Left, RectInfo.Top, Right, Top));
                    // Ret.push_back(FRectInfo(Left, Bottom, Right, RectInfo.Bottom));
                }
                else
                {
                    // Ret.push_back(FRectInfo(Left, Bottom, Right, Top));
                }
            }
        }
    }

    return Ret;
}

class FRect
{
public:
    FRect(int Index, int X1, int Y1, int X2, int Y2) : RectIndex(Index), RectInfo(X1, Y1, X2, Y2) { CompositeRectList.insert(RectInfo); }

    bool IsNotOverlap(const FRect& Rect) const;

    bool IsOverlap(const FRect& Rect) const;

    int GetSize() const
    {
        int Size = 0;
        for(auto& CompositeRect : CompositeRectList)
        {
            Size += CompositeRect.GetSize();
        }
        return Size;
    }

    bool operator<(const FRect& r) const
    {
        int lRemainSize = GetSize();
        int rRemainSize = r.GetSize();
        if(lRemainSize == rRemainSize)
        {
            return RectIndex < r.RectIndex;
        }
        else
        {
            return lRemainSize > rRemainSize;
        }
    }

    int GetIndex() { return RectIndex; }

    void operator-(FRect& Rect);

private:
    const int RectIndex;

    FRectInfo RectInfo;

    std::set<FRectInfo> CompositeRectList;
};

bool FRect::IsNotOverlap(const FRect &Rect) const
{
    return (Rect.RectInfo.Right <= RectInfo.Left) || (RectInfo.Right <= Rect.RectInfo.Left) || (Rect.RectInfo.Top <= RectInfo.Bottom) || (RectInfo.Top <= Rect.RectInfo.Bottom);
}

bool FRect::IsOverlap(const FRect &Rect) const
{
    return !IsNotOverlap(Rect);
}

void FRect::operator-(FRect &Rect)
{
    std::set<FRectInfo> SubbedCompositeRectList;
    for(FRectInfo CompositeRect : CompositeRectList)
    {
        if(CompositeRect.IsOverlap(Rect.RectInfo))
        {
            std::vector<FRectInfo> NewCompositeRectList = CompositeRect - Rect.RectInfo;
            for(FRectInfo& Info : NewCompositeRectList)
            {
                SubbedCompositeRectList.insert(Info);
            }
        }
        else
        {
            SubbedCompositeRectList.insert(CompositeRect);
        }
    }
    CompositeRectList = SubbedCompositeRectList;
}

class FRectSelector
{
public:
    std::vector<std::weak_ptr<FRect>> Select(std::vector<std::shared_ptr<FRect>>& Rects, int SelectCount);
};

std::vector<std::weak_ptr<FRect>> FRectSelector::Select(std::vector<std::shared_ptr<FRect>>& Rects, int SelectCount)
{
    auto Compare = [](const std::shared_ptr<FRect>& l, const std::shared_ptr<FRect>& r) { return l.get()->operator<(*r.get()); };
    std::sort(Rects.begin(), Rects.end(), Compare);

    std::vector<std::weak_ptr<FRect>> Selected(Rects.begin(), Rects.begin() + SelectCount);

    return Selected;
}

class FInputProcessor
{
public:
    int Process(std::vector<std::shared_ptr<FRect>>& Rects);
};

int FInputProcessor::Process(std::vector<std::shared_ptr<FRect>>& Rects)
{
    int TotalBoxCount, SelectCount;
    std::cin >> TotalBoxCount >> SelectCount;

    for(int i = 0; i < TotalBoxCount; ++i)
    {
        int X1, Y1, X2, Y2;
        std::cin >> X1 >> Y1 >> X2 >> Y2;

        std::shared_ptr<FRect> NewRectInfo = std::make_shared<FRect>(i + 1, X1, Y1, X2, Y2);
        for(auto& RectInfo : Rects)
        {
            if(RectInfo.get()->IsOverlap(*NewRectInfo.get()))
            {
                RectInfo.get()->operator-(*NewRectInfo.get());
            }
        }
        Rects.push_back(NewRectInfo);
    }

    return SelectCount;
}

void Solve()
{
    std::vector<std::shared_ptr<FRect>> Rects;

    FInputProcessor InputProcessor;
    int SelectCount = InputProcessor.Process(Rects);

    FRectSelector RectSelector;
    std::vector<std::weak_ptr<FRect>> Selected = RectSelector.Select(Rects, SelectCount);

    std::vector<int> Output;
    for(int i = 0; i < SelectCount; ++i)
    {
        Output.push_back(Selected[i].lock()->GetIndex());
    }
    std::sort(Output.begin(), Output.end());

    for(auto val : Output)
    {
        std::cout << val << " ";
    }
}
