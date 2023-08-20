#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <unordered_map>
#include <map>
#include <array>


/*
一种空间节点数据库

1. 物质节点
2. 空间节点

物质节点，必然拥有一个空间节点，但是空间节点不一定拥有物质节点

空间节点，可以拥有多个物质节点，但是物质节点只能拥有一个空间节点，空间节点可以有多个子空间节点

*/

enum NodeType
{
    Matter,
    Space
};

struct MatterCoordinate
{
    double x = 0;
    double y = 0;
    double z = 0;
};
struct SpaceCoordinate
{
    double x = 0;
    double y = 0;
    double z = 0;
    double w = 0;
    double h = 0;
    double d = 0;
    
    static bool contain(MatterCoordinate& mc, SpaceCoordinate& sc)
    {
        return mc.x >= sc.x && mc.x <= sc.x + sc.w
            && mc.y >= sc.y && mc.y <= sc.y + sc.h
            && mc.z >= sc.z && mc.z <= sc.z + sc.d;
    }
    bool contain(MatterCoordinate& mc)
    {
        return mc.x >= x && mc.x <= x + w
            && mc.y >= y && mc.y <= y + h
            && mc.z >= z && mc.z <= z + d;
    }

    static bool intersect(SpaceCoordinate& sc1, SpaceCoordinate& sc2)
    {
        return sc1.x <= sc2.x + sc2.w && sc1.x + sc1.w >= sc2.x
            && sc1.y <= sc2.y + sc2.h && sc1.y + sc1.h >= sc2.y
            && sc1.z <= sc2.z + sc2.d && sc1.z + sc1.d >= sc2.z;
    }
    bool intersect(SpaceCoordinate& sc)
    {
        return x <= sc.x + sc.w && x + w >= sc.x
            && y <= sc.y + sc.h && y + h >= sc.y
            && z <= sc.z + sc.d && z + d >= sc.z;
    }

    SpaceCoordinate operator&(SpaceCoordinate& sc)
    {
        SpaceCoordinate ret;
        ret.x = std::max(x, sc.x);
        ret.y = std::max(y, sc.y);
        ret.z = std::max(z, sc.z);
        ret.w = std::min(x + w, sc.x + sc.w) - ret.x;
        ret.h = std::min(y + h, sc.y + sc.h) - ret.y;
        ret.d = std::min(z + d, sc.z + sc.d) - ret.z;
        return ret;
    }
    SpaceCoordinate operator+(SpaceCoordinate& sc)
    {
        SpaceCoordinate ret;
        ret.x = std::min(x, sc.x);
        ret.y = std::min(y, sc.y);
        ret.z = std::min(z, sc.z);
        ret.w = std::max(x + w, sc.x + sc.w) - ret.x;
        ret.h = std::max(y + h, sc.y + sc.h) - ret.y;
        ret.d = std::max(z + d, sc.z + sc.d) - ret.z;
        return ret;
    }
};


class Node
{
    public:
    std::string name;
    NodeType type;
    std::shared_ptr<Node> parent;
};

class SpaceInfo : public Node
{
    double space_curvature = 1.0;
};


class SpaceNode
{
    public:
    SpaceInfo info;
    public:
    class SapceStructure
    {
        std::shared_ptr<SpaceNode> top;
        std::shared_ptr<SpaceNode> up_front_left;
        std::shared_ptr<SpaceNode> up_front_right;
        std::shared_ptr<SpaceNode> up_back_left;
        std::shared_ptr<SpaceNode> up_back_center;
        std::shared_ptr<SpaceNode> up_back_right;
        std::shared_ptr<SpaceNode> down_front_left;
        std::shared_ptr<SpaceNode> down_front_center;
        std::shared_ptr<SpaceNode> down_front_right;
        std::shared_ptr<SpaceNode> down_back_left;
        std::shared_ptr<SpaceNode> down_back_center;
        std::shared_ptr<SpaceNode> bottom;

        const std::array<std::shared_ptr<SpaceNode>, 12> adjacents = { 
            top,
            up_front_left,
            up_front_right,
            up_back_left,
            up_back_center,
            up_back_right,
            down_front_left,
            down_front_center,
            down_front_right,
            down_back_left,
            down_back_center,
            bottom
        };


    };
    struct SapceSubdivision
    {
        std::array<std::shared_ptr<SpaceNode>, 1> center;
        // 12个相邻空间 共享大部分边界
        //std::array<std::shared_ptr<SpaceNode>, 12> adjacents;
        SapceStructure adjacents;
        // 12个部分归属于邻域子空间的边缘空间 共享小部分边界
        //std::array<std::shared_ptr<SpaceNode>, 12> adjacent_edges;
        SapceStructure adjacent_edges;
    };
    public:
    bool is_leaf = true;
    // 分割为1个中心空间+12个相邻空间+12个部分归属于邻域子空间的边缘空间
    std::array<std::shared_ptr<SpaceNode>, 25> childs;
    
    std::array<std::shared_ptr<SpaceNode>, 12> adjacents;
    std::shared_ptr<SpaceNode> parent;
};

class MatterNode : public Node
{
    public:
    std::shared_ptr<SpaceNode> space;
};
// 连通空间集合
class SpaceSet
{
    public:
    std::list<std::shared_ptr<SpaceNode>> spaces;
};

class YuMap
{
    public:
    std::map<std::string, std::shared_ptr<SpaceSet>> yus;
};


// 空间十二叉树
class SpaceTreeNode
{
    public:
    double depth = 0;
    double space_curvature = 1.0;
};


