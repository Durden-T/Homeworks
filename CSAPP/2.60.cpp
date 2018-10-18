unsigned replace_byte(unsigned x, int i, unsigned char b)
{

    x &= ~(0xff << (i * 8));
    x |= b << (i * 8);
    return x;
}