int lower_one_mask(int n)
{
    const int w = sizeof(int) * 8;
    int ans = 0xffffffff;
    n != w && (ans = INT_MAX >> (w - n - 1));
    return ans;
}