int int_size_is_32(void)
{
    int set_msb = 1 << 31, beyond_msb = set_msb * 2;
    return set_msb && !beyond_msb;
}