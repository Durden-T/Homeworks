int int_size_is_32(void)
{
    int set_msb = 1 << 15, beyond_msb = set_msb * 2, s = (beyond_msb >> 1) * beyond_msb, b = s * 2;
    return set_msb && beyond_msb && s && !b;
}