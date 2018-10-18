int odd_ones(unsigned x)
{
    /*size_t count = 0;
    ......
    return count & 1;*/
    int ans = 0;
    while (x)
    {
        ++ans;
        x &= x - 1;
    }
    return ans&1;
}