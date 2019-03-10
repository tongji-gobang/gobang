#include <vector>

#include "board.h"

using PointSet = vector<struct point>;
/*
    初步想法，待搜索的位置的存储
*/
int board::Negmax(PointSet& candidates, int role, int depth, int alpha, int beta )
{

}

auto Pruning( int depth, int alpha, int beta, int role )
{

}

struct point board::Deeping( PointSet& candidates, int role, int depth )
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

    

}
struct point board::DepthSearchAll( int role, int depth )
{
    // 教程源码中写法： role = role || R.com --- 这句恒为真，不知何意
    role = COM;

    PointSet candidates = gen( role );  // vector<point>

    return Deeping( candidates, role, depth );
}

