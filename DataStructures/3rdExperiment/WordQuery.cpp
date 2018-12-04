#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

#include "Lib.h"


int main(int argc, char **argv)
{
    if (argc != 2) //未输入文件或输入参数超过一个
    {
        cerr << "Please input the file's path.\n";
        system("pause");
        return -1;
    }

    ifstream file(argv[1]); //使用ifstream打开目标文件
    if (!file)              //打开失败
    {
        cerr << "Can't open the file.\n";
        system("pause");
        return -1;
    }

    vector<string> source; //保存目标文件每一行的vector
    splitToLine(file, source);

    string pattern; //保存要查找的单词

    cout << "\nPlease input the word you want to query,this word must only consists of letter.When this program is working it will be converted to lowercase,and the result word must be separated from other letter.\n\ninput \"!exit\" to quit.\n";

    //该单词必须全部由字母组成，在查询单词时，将所有文本转化为小写，并且该单词必须与其他字母（用空格，标点符号，或在一行的开头或者结尾等）分隔开来，输入!exit退出
    while (cin >> pattern && pattern != EXIT) //循环直到收到EXIT
    {
        //检查是否为上面定义的单词
        if (!checkAndConvertWord(pattern)) //不是单词
        {
            cout << "\nThe pattern isn't a word.\n";
            break;
        }

        wordQuery(source, pattern);
        cout << "\nPlease input the word you want to query,input \"!exit\" to quit.\n"; //等待下一个查询的单词
    }

    system("pause");
    return 0;
}



void splitToLine(ifstream &file, vector<string> &source)
{
    string t;
    while (getline(file, t)) //从file中读取一行存到t中
    {
        for (char &c : t) //转换为小写
            c = tolower(c);
        source.emplace_back(t); //存放到source中
    }
}



inline bool checkAndConvertWord(string &s)
{
    for (char &c : s)
        if (!isalpha(c))
            return false;
        else
            c = tolower(c); //将s转换为小写

    return true;
}



inline void wordQuery(vector<string> &source, const string &pattern)
{
    int *badChar = getBadChar(pattern);
    int *goodSuffix = getGoodSuffix(pattern);

    int count = 0; //统计pattern出现的次数
    for (int i = 0; i < source.size(); ++i)
        count += BM(source[i], pattern, badChar, goodSuffix, i + 1);

    if (!count) //未出现
        cout << "\nThe pattern doesn't exist.\n";
    else
    {
        if (count > MAXSPILT) //格式控制，当查询结果大于MAXSPILT个时，输出大量空行，与前后结果分隔开来
            cout << "\nThe word: " << pattern << " occurs for " << count << " times.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        else
            cout << "\nThe word: " << pattern << " occurs for " << count << " times.\n";
    }

    //释放动态分配的辅助数组
    delete[] badChar;
    delete[] goodSuffix;
}



inline int BM(const string &s, const string &pattern, int *badChar, int *goodSuffix, int lineNumber)
{
    int count = 0; //当前一行中pattern出现的次数

    int start = 0; //当前pattern和s左端对齐的位置
    int cur;       //当前比较的位置

    while (start + pattern.length() <= s.length())
    {
        //从右端开始匹配
        for (cur = pattern.length() - 1; cur >= 0 && pattern[cur] == s[start + cur]; --cur)
            ;
        //完全匹配，且结果是上面定义的单词，即出现在开头位置，或前一个不是字母，或出现在末尾，或后一个不是字母
        if (cur == -1 && (!start || !isalpha(s[start - 1])) && (start + pattern.length() == s.length() || !isalpha(s[start + pattern.length()])))
        {
            cout << "line " << lineNumber << ",pos " << start << ":" << s << "\n\n"; //输出结果
            ++start;                                                                 //从当前位置的下一个继续匹配
            ++count;
        }
        else                                                              //未完全匹配
            start += max(goodSuffix[cur], cur - badChar[s[start + cur]]); //start前进到通过坏字符和好后缀得到的最佳位置
    }

    return count;
}



int *getBadChar(const string &pattern)
{
    int *badChar = new int['z' + 1]; //从a存到z

    //初始均设置为-1，即当坏字符不存在于pattern的情况下，让start前进一位
    for (int i = 'a'; i < 'z'; ++i)
        badChar[i] = -1;

    //坏字符存在于pattern,找到在pattern中最后出现的此字符,令此时比较位置于此位置对齐
    for (int i = 0; i < pattern.length(); ++i)
        badChar[pattern[i]] = i;

    return badChar;
}



int *getGoodSuffix(const string &pattern)
{
    const int len = pattern.length();
    const int lastIndex = len - 1;
    //suff[i] 表示在第i个位置之前（包括i）与pattern的后缀匹配的最长长度
    int suff[len];
    suff[len - 1] = len;

    for (int i = len - 2, num; i >= 0; --i) //num为匹配成功数
    {
        for (num = 0; num <= i && pattern[i - num] == pattern[len - num - 1]; ++num) //匹配成功时不断增加num
            ;
        suff[i] = num;
    }

    int *goodSuffix = new int[len];
    //初始情况为找不到子串和前缀
    for (int i = 0; i < len; ++i)
        goodSuffix[i] = len;
    //pattern存在最大前缀
    for (int i = lastIndex; i >= 0; --i)
        //存在我们想要的前缀
        if (suff[i] == i + 1)
            for (int j = 0; j < lastIndex - i; ++j)
                if (goodSuffix[j] == len)
                    goodSuffix[j] = lastIndex - i;

    //pattern中有子串匹配上好后缀
    for (int i = 0; i < lastIndex; ++i)
        goodSuffix[lastIndex - suff[i]] = lastIndex - i;

    return goodSuffix;
}