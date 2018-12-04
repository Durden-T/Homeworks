#define EXIT "!exit" //退出标志

#define MAXSPILT 10 //当查询结果大于MAXSPILT个时，输出大量空行，与前后结果分隔开来

/*
@param
file:目标文件流
source:保存文本每一行的vector

@function
读取目标文件，将每一行转化为小写并存储在source中
*/
void splitToLine(ifstream &file, vector<string> &source);

/*
@param
s:目标字符串

@return:若是单词返回true，否则返回false

@function
并将s转化为小写，返回s是否为单词
*/
bool checkAndConvertWord(string &s);

/*
@param
source:保存文本每一行的vector
pattern:要查找的单词

@function
查找pattern并输出pattern出现的次数及位置
*/
void wordQuery(vector<string> &source, const string &pattern);

/*
@param
s:保存文本每一行的vector
pattern:要查找的单词
bc:BM算法使用的辅助坏字符数组
gs:BM算法使用的辅助好后缀数组
lineNumber:当前的行数

@return:在当前一行中pattern出现的次数

@function
使用BM算法在s中寻找p，每查找到一个便输出此时的行数与位置
*/
int BM(const string &s, const string &pattern, int *bc, int *gs, int lineNumber);

/*
@param
pattern:要查找的单词

@return:BM算法使用的辅助坏字符数组

@function
创建BM算法使用的辅助坏字符数组
*/
int *getBadChar(const string &pattern);

/*
@param
pattern:要查找的单词

@return:BM算法使用的辅助好后缀数组

@function
创建BM算法使用的辅助好后缀数组
*/
int *getGoodSuffix(const string &pattern);