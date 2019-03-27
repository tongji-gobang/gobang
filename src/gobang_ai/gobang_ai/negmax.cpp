#include <vector>
#include <climits>
#include <algorithm>

#include "board.h"


#define PInfinity INT_MAX
#define NInfinity -INT_MAX

using PointSet = vector<struct point>;
using CandidateSet = vector<struct candidate>;
/*
    初步想法，待搜索的位置的存储
*/
int board::Negmax(CandidateSet& candidates, int role, int depth, int alpha, int beta )
{
    this->currentSteps.clear();

    for ( int i = 0; i < candidates.size(); ++i )
    {
        auto p = candidates[i];
        this->put( p, role );
        PointSet steps(1, p);

        auto v = Pruning( depth - 1, -beta, -alpha, role == COM ? HUM : COM, 1, steps, 0 );

        v.score = -v.score;
        alpha = max( alpha, v.score );

        this->remove( p );
        p = v;
    }
    return alpha;
}

struct candidate board::Pruning( int depth, int alpha, int beta, int role, int step, PointSet& steps, int spread )
{
    // zobirst 部分  暂时放下

    auto score = this->evaluate( role );
    
    struct candidate leaf;
    leaf.score = score;
    leaf.step = step;
    leaf.steps = steps;

    // 暂时忽略每次深度遍历的结点数

    if ( depth <= 0 || score >= FIVE || score <= -FIVE )
        return leaf;
}

bool board::cache( int depth, const CandidateSet& score )
{

}

struct point board::Deeping( CandidateSet& candidates, int role, int depth )
{
    // 教程中加了超时计时器，暂时忽略
    int MaxScore;
    for ( int i = 2; i <= depth; i += 2 )
    {
        // 初始调用
        MaxScore = Negmax(candidates, role, depth, INT_MIN, INT_MAX );
        if ( MaxScore >=  FIVE )    // 搜索到能赢的棋
            break;
    }

    // 美化暂时未明白

    sort( candidates.begin(), candidates.end() );
    
    auto result = candidates.at(0);

    //中间暂未明白

    return result;
}
struct point board::DepthSearchAll( int role, int depth )
{
    // js中role可能未定义，这里暂时不用管

    PointSet temp = gen( role );
    CandidateSet candidates;

    auto ConCandidates = [] ( CandidateSet& candidates, const PointSet& temp )
    {
        for ( int i = 0; i < temp.size(); ++i )
            candidates.push_back( candidate(temp[i]) );
    } ;

    ConCandidates( candidates, temp );

    return Deeping( candidates, role, depth );
}
