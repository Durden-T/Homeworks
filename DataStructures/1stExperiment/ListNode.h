//带有头节点的循环链表 最后一个元素指向第一个元素
struct ListNode
{
    int id; //此人的id

    string name; //此人的名字

    string gender; //此人的性别

    int age; //此人的年龄

    ListNode *next; //下一个节点

    ListNode(int Id, const string &Name, const string &Gender, int Age) : id(Id), name(Name), gender(Gender), age(Age) //初始化节点信息
    {
    }
    ListNode(){}; //默认初始化函数 供头节点使用
};
