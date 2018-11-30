#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#include "Lib.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Please input the file address.\n";
        system("pause");
        return -1;
    }

    ifstream file(argv[1]);
    if (!file)
    {
        cerr << "Can't open the file.\n";
        system("pause");
        return -1;
    }

    vector<string> source;
    splitToLine(file, source);

    string pattern;
    cout << "\nPlease input the text you want to query,input \"!exit\" to quit.\n";
    while (cin >> pattern && pattern != EXIT)
    {
        textQuery(source, pattern);
        cout << "\nPlease input the text you want to query,input \"!exit\" to quit.\n";
    }

    system("pause");
    return 0;
}

void splitToLine(ifstream &file, vector<string> &source)
{
    string t;
    while (getline(file, t))
        source.emplace_back(t);
}

inline void textQuery(vector<string> &source, const string &pattern)
{
    int *bc = getBc(pattern);
    int *gs = getGs(pattern);

    int count = 0;
    for (int i = 0; i < source.size(); ++i)
        count += BM(source[i], pattern, bc, gs, i + 1);

    if (!count)
        cout << "\nCan't find the text.\n";
    else
    {
        if (count > MAXSPILT)
            cout << "\nThe text: " << pattern << " occurs for " << count << " times.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        else
            cout << "\nThe text: " << pattern << " occurs for " << count << " times.\n";
    }

    delete[] bc;
    delete[] gs;
}

inline int BM(const string &s, const string &p, int *bc, int *gs, int lineNumber)
{
    int count = 0;

    //start指向了当前pattern和text对齐的位置
    int start = 0;
    //cur指向了当前比较的位置
    int cur;
    while (start + p.length() <= s.length())
    {
        //如果匹配成功，cur就会来到-1的位置上
        //start + cur 指向了text上当前比较的字符
        for (cur = p.length() - 1; cur >= 0; --cur)
            /*if (p[cur] == '?')
            {
            }
            else */
            if (p[cur] != s[start + cur] && p[cur] != '*')
                break;

        if (cur == -1)
        {
            //cout << "line " << lineNumber << ",pos " << start << ":" << s << "\n\n";
            cout << "line " << lineNumber << ",pos " << start << ":" << s.substr(start,p.length()) << "\n\n";
            ++start;
            ++count;
        }
        else
            start += max(gs[cur], cur - bc[s[start + cur]]);
        //start += max(gs[cur], (int)(bc[s[start + cur]]-(p.length()-1-cur)));
    }

    return count;
}

int *getBc(const string &p)
{
    //128是字符表的规模大小(ACSII)
    int *bc = new int[128];

    for (int i = 0; i < 128; ++i)
        bc[i] = -1;

    for (int i = 0; i < p.length(); ++i)
        bc[p[i]] = i;

    return bc;
}

int *getGs(const string &p)
{
    const int len = p.length();
    const int lastIndex = len - 1;
    int suff[len];
    suff[len - 1] = len;

    for (int i = len - 2, num; i >= 0; --i)
    {
        for (num = 0; num <= i && (p[i - num] == p[len - num - 1] || p[i - num] == '*' || p[len - num - 1] == '*'); ++num)
            ;
        suff[i] = num;
    }

    int *gs = new int[len];
    //找不到对应的子串和前缀
    for (int i = 0; i < len; ++i)
        gs[i] = len;
    //找前缀
    for (int i = lastIndex; i >= 0; --i)
        //存在我们想要的前缀
        if (suff[i] == i + 1)
            for (int j = 0; j < lastIndex - i; ++j)
                if (gs[j] == len)
                    gs[j] = lastIndex - i;

    //找中间的匹配子串
    for (int i = 0; i < lastIndex; ++i)
        gs[lastIndex - suff[i]] = lastIndex - i;

    return gs;
}