//google popcount
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

int hakmem_popcount(unsigned int n)
{
    unsigned tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
    return ((tmp + (tmp >> 3)) & 030707070707) & 1;
}