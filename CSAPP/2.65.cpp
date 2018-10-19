int odd_ones(unsigned x) //using while
{
    int ans = 0;
    while (x)
    {
        ++ans;
        x &= x - 1;
    }
    return ans & 1;
}

int odd_ones(unsigned x)
{
    x ^= x >> 16; //x右移16位，然后将x的高16位和低16位异或，忽略32位数结果里面不相干的高16位。
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x&1;
}