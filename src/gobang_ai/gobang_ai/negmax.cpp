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

}
struct point board::DepthSearchAll( int role, int depth )
{
    // 教程源码中写法： role = role || R.com --- 这句恒为真，不知何意
    role = COM;

    auto candidates = gen( role );  // vector<point>

    return deeping( candidates, role, depth );
}

