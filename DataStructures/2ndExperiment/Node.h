struct Node
{
    int id;                    //此节点的id
    bool isEnd = false;        //标记是否为出口
    bool visited = false;      //标记是否遍历过，避免再次遍历陷入死循环
    Node *path = nullptr;      //记录上一个位置，最后逆向输出路径
    vector<int> next;          //记录连通的各个节点
    Node(int _id) : id(_id){}; //初始化id
    Node();                    //默认初始化函数
};