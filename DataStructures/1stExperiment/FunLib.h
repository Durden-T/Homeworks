#define success true
#define failed false

/*
@param
head:循环链表的头节点
size:循环链表内的实际节点数

@function
收集输入信息并按信息创建循环链表,若有输入错误则在cerr中显示并退出
*/
bool createList(ListNode *head, int size);

/*
@param
head:循环链表的头节点
size:循环链表内的实际节点数

@return
若正常运行返回success，否则返回failed

@function
依次输出循环链表中各节点的信息
*/
void printInfo(ListNode *head, int size);

/*
@param
node:欲删除节点的前一个节点
head:头节点
size:循环链表内的实际节点数

@function
输出node后的节点id并删除此节点 
*/
void deleteAndCoutNextNode(ListNode *node, ListNode *head, int size);

/*
@param
head:循环链表的头节点
id:查找的节点的id
size:循环链表内的实际节点数

@return
如果能找到该节点,return 该节点,否则 return nullptr,并在cerr中输出错误信息

@function
查找id为参数id的节点，并返回该节点的前一个节点
*/
ListNode *findIdPrev(ListNode *head, int id, int size);

/*
@param
head:循环链表的头节点
size:循环链表内的实际节点数 (要改变size的值 所以采用引用传递)
start:开始报数的节点的id
interval:报数间隔,报interval的节点将被删除
remain:剩余节点的数量

@return
若正常运行返回success,否则返回false

@function
解决约瑟夫问题的主函数,从id为start的节点开始从1报数,每报到interval的节点被删除,输出该节点的id,由下一个节点从1继续报数,直到剩余remain个节点
*/
bool solveJosephusProblem(ListNode *head, int &size, int start, int interval, int remain);
