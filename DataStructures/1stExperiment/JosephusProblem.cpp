#include <iostream>
#include <unordered_set> //处理重复id

using namespace std;

#include "ListNode.h"
#include "FunLib.h"
int main()
{
    /*
    head:循环链表的头节点
    size:循环链表内的实际节点数
    start:开始报数的节点的id
    interval:报数间隔,报interval的节点将被删除
    remain:剩余节点的数量
    */

    int size, start, interval, remain;
    ListNode *head = new ListNode;

    cout << "Please input the size of people,id of the people who start the game,interval count and the number of remain people in order.\n\n";

    /* 检测输入是否合法: 是否每个变量都有对应格式的输入; 总人数,报数间隔应该大于0; 剩余人数应该小于等于总人数，且大于等于0 */

    if (!(cin >> size >> start >> interval >> remain) || size <= 0 || interval <= 0 || remain > size || remain < 0)
    {
        cerr << "\nInput error.\n\n"; //在cerr中输出“输入错误”并退出
        system("pause");
        return -1;
    }

    if (createList(head, size) == failed) //收集输入信息并创建循环链表
    {
        system("pause");
        return -1; //发生错误 退出
    };

    printInfo(head, size); //输出原始的循环链表中的各节点的信息

    //解决约瑟夫问题的功能函数
    if (solveJosephusProblem(head, size, start, interval, remain) == failed)
    {
        system("pause");
        return -1; //发生错误 退出
    };

    cout << "\n\nRemain:";
    printInfo(head, size); //输出剩余节点信息

    system("pause");
    return 0;
}

bool createList(ListNode *head, int size)
{
    ListNode *cur = head; //利用cur遍历循环链表

    /* id,age,name,gender临时保存各节点的信息，count为实际遍历的节点数量，用于判断输入个数是否合法及输入是否结束 */

    int count = 0, id, age;
    string name, gender;

    unordered_set<int> idSet; //处理重复id
    cout << "\nPlease input the id,name,gender and age in order,gender should be male,female or other.\n\n";

    while (count < size && cin >> id >> name >> gender >> age) //检测输入是否结束及是否每个变量均有对应格式的输入
    {
        if (name.empty() || (gender != "male" && gender != "female" && gender != "other") || age < 0) //检测输入是否合法：性别应只有三种输入; 年龄应大于等于0
        {
            cerr << "\nInput error.\n\n"; //在cerr中输出“输入错误”并返回
            return failed;
        }

        if (idSet.count(id)) //id重复
        {
            cerr << "\nDuplicate id.\n\n"; //在cerr中输出“重复id”并返回
            return failed;
        }

        ++count;
        idSet.insert(id); //向set中插入此id

        //此节点创建完毕后创建下一个节点,并更新cur使其指向下一个节点
        cur->next = new ListNode(id, name, gender, age);
        cur = cur->next;
    }

    if (count != size) //发生了输入错误，提前退出循环
    {
        cerr << "\nInput error.\n\n"; //在cerr中输出“输入错误”并返回
        return failed;
    }

    cur->next = head->next; //最后一个节点指向第一个节点
    return success;
}

void printInfo(ListNode *head, int size)
{
    int count = 0;
    ListNode *cur = head->next;

    cout << "\n\nId\t"
         << "Name\t"
         << "Gender\t"
         << "Age\n";

    while (count < size) //检测是否全部遍历
    {
        cout << cur->id << '\t' << cur->name << '\t' << cur->gender << '\t' << cur->age << '\n';
        cur = cur->next;
        ++count;
    }
}

ListNode *findIdPrev(ListNode *head, int id, int size)
{
    int count = 0;
    ListNode *cur = head;

    /*
    count<=size : 判断是否遍历完全部节点
    cur->next->id != id : 在找到该节点的前一个节点时停止
    cur == head : 当欲查找的节点是第一个节点时,应返回最后一个节点而不是头节点,所以跳过头节点
     */

    while (count <= size && (cur == head || cur->next->id != id))
    {
        cur = cur->next;
        ++count;
    }

    if (count > size) //找不到该节点
    {
        cerr << id << "\n\nDoesn't exist.\n"; //在cerr中输出“该id不存在”并返回
        return nullptr;
    }
    return cur;
}

bool solveJosephusProblem(ListNode *head, int &size, int start, int interval, int remain)
{
    ListNode *cur = findIdPrev(head, start, size); //当报数等于间隔时，cur的下一个节点为被删除的节点
    int i = 1;                                     //记录报数

    if (!cur)
        return failed;

    cout << "\nDeleted id: ";

    while (size > remain) //当循环链表中总节点数等于剩余节点数时退出循环
    {
        if (i == interval) //报数等于间隔
        {
            deleteAndCoutNextNode(cur, head, size);
            --size; //更新总结点数
            i = 0;  //重置报数为0
        }
        else //否则cur指向下一个节点
            cur = cur->next;

        if (++i > interval) //若报数增加1后大于间隔，则重置报数为1
            i = 1;
    }

    return success;
}

void deleteAndCoutNextNode(ListNode *node, ListNode *head, int size)
{
    /* target为欲删除节点,tmp为欲删除节点的下一个节点,保存此节点,以免受target被删除的影响,找不到下一个节点 */

    ListNode *target = node->next, *tmp = target->next;

    cout << target->id << '\t';

    if (target == head->next) //若欲删除的节点为第一个节点
    {
        /*
        找到最后一个节点,使其指向第二个节点,删除目标节点，更新头节点使其指向新的第一个节点
        */
        ListNode *tail = findIdPrev(head, head->next->id, size);
        tail->next = tmp;
        delete target;
        head->next = tmp;
    }

    else //否则直接删除目标节点，并使目标节点的前一个节点指向目标节点的后一个节点
    {
        delete target;
        node->next = tmp;
    }
}
