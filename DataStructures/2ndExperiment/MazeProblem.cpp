#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#include "Lib.h"

int main()
{
    vector<Node *> all = {nullptr}; //保存所有节点，为使id与数组序号相符，初始插入一个空指针
    int start;
    initialMaze(all, start); //初始化迷宫 输入所有出口

    //dfs部分，解决基本问题
    /*if (!dfs(all[start], all))
    {
        cerr << "Cant go out of the maze.\n";
        system("pause");
        return -1;
    };*/
    bfs(all[start], all); //bfs部分，解决补充问题
    system("pause");
    return 0;
}

void initialMaze(vector<Node *> &all, int &start)
{
    cout << "Please input the input file's path name.\n";

    string input;
    cin >> input;
    ifstream in(input); //使用文件输入流控制格式
    int size;           //迷宫总节点数
    in >> size >> start;

    for (int i = 1; i < size; ++i) //id从1开始新建节点，插入all中
    {
        Node *t = new Node(i);
        all.push_back(t);
    }

    all[start]->visited = true; //dfs bfs中均是设置next节点的visited属性，因此在初始化迷宫中设置入口为visited

    int t;
    while (in >> t && t != End) //设置出口
        all[t]->isEnd = true;

    int source, next; //source 源节点 next 与source相连通的节点

    while (in >> source) //按迷宫连接节点
        while (in >> next && next != End)
            all[source]->next.push_back(next);
}

bool dfs(Node *cur, vector<Node *> &all)
{
    if (cur->isEnd) //找到出口
    {
        CountNShowPath(cur, all); //输出路径信息，返回
        return success;
    }

    for (int i : cur->next)   //遍历与cur连通的每个节点
        if (!all[i]->visited) //若此节点未被查看过
        {
            all[i]->visited = true; //设置visit
            all[i]->path = cur;     //更新path为cur节点

            if (dfs(all[i], all)) //若找到出口，立即返回
                return true;
        }

    return failed; //当前路径未找到出口 返回失败
}

void bfs(Node *start, vector<Node *> &all)
{
    queue<Node *> q;
    q.push(start); //建立队列，把出口放入队列中
    Node *cur;     //在循环外设置cur,使推出循环时仍有cur存在

    while (!q.empty())
    {
        cur = q.front();
        if (cur->isEnd) //找到最近出口 退出循环
            break;
        q.pop();

        for (int i : cur->next)   //遍历与cur连通的每个节点
            if (!all[i]->visited) //若此节点未被查看过
            {
                all[i]->visited = true; //设置visit
                all[i]->path = cur;     //更新path为cur节点
                q.push(all[i]);         //将此节点入队列
            }
    }

    CountNShowPath(cur, all); //输出路径信息
}

void CountNShowPath(Node *end, vector<Node *> &all)
{
    int length = -1; //因要求的是路径长度，初始应设置为-1
    string ans;      //路径

    while (end) //当end为nullptr(返回入口)时退出循环
    {
        ans.insert(0, to_string(end->id) + " -> "); //将id从int转换为string，插入到ans前
        ++length;
        end = end->path; //回退一个节点
    }

    cout << "length : " << length << "\npath : " << ans.substr(0, ans.size() - 4) << '\n'; //输出路径信息，因ans最后多了控制格式的"->",删除他们
}