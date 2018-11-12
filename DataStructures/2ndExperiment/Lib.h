#include "Node.h"

#define End -1 //处理输入文件中结尾

enum //默认构造整型变量 failed=0,success=1,startPoint=2
{
    failed,
    success
};

/*
@param
all:保存所有节点的数组
start:为引用，入口节点id

@function
初始化迷宫，并把出口信息标记在出口节点上
*/
void initialMaze(vector<Node *> &all, int &start);

/*
@param
cur:开始dfs的节点
all:保存所有节点的数组

@return
若找到出口返回success，否则返回failed

@function
深度优先搜索，若找到出口则立即返回，通过对返回值的判断使递归立即停止；对搜索过的节点标记，防止再次搜索
*/
bool dfs(Node *cur, vector<Node *> &all);

/*
@param
start:开始dfs的节点
all:保存所有节点的数组

@function
广度优先搜索，利用队列特性，在这种情况下第一个找到的出口一定是最近的出口，并且路径长度也是从入口到这个出口中最近的(解决补充的两个问题);对搜索过的节点标记，防止再次搜索
*/
void bfs(Node *start, vector<Node *> &all);

/*
@param
end:出口
all:保存所有节点的数组

@function
从出口开始逆向输出路径，并统计长度
*/
void CountNShowPath(Node *end, vector<Node *> &all);