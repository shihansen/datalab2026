/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~ ((~ x) | (~ y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~ (x & y)) & (~ (~x & ~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (! x) {
        if (! y)
            return 1;
        else 
            return 0;
    }

    if (! y)
        return 0;
    
    return !((x >> 31 & 1) ^ (y >> 31 & 1));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int ans = 0;
    int b1 = ((65535) < v) << 4;
    ans |= b1;
    v >>= b1;
    b1 = ((255) < v) << 3;
    ans |= b1;
    v >>= b1;    
    b1 = ((15) < v) << 2;
    ans |= b1;
    v >>= b1;
    b1 = ((3) < v) << 1;
    ans |= b1;
    v >>= b1;
    b1 = ((1) < v);
    ans |= b1;
    v >>= b1;
    return ans;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n <<= 3; m <<= 3;
    int b1 = (x >> n) & 255;
    int b2 = (x >> m) & 255;
    x ^= (b1 << n) ^ (b2 << n) ^ (b1 << m) ^ (b2 << m);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v & 0x55555555u) << 1) | ((v >> 1) & 0x55555555u);
    v = ((v & 0x33333333u) << 2) | ((v >> 2) & 0x33333333u);
    v = ((v & 0x0F0F0F0Fu) << 4) | ((v >> 4) & 0x0F0F0F0Fu);
    v = ((v & 0x00FF00FFu) << 8) | ((v >> 8) & 0x00FF00FFu);
    v = (v << 16) | (v >> 16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int v = !! n;
    int e = 0x7fffffff;
    return ((x >> n) & (e >> ((n + 31) & 31))) | (x & ((~v) + v + v));
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int ans = 0, b;
    b = (x >> 16) & 65535;
    b = (b + 1) & 65535;
    b = !b;
    ans = ans + (b << 4);
    x >>= (!b) << 4;

    b = (x >> 8) & 255;
    b = (b + 1) & 255;
    b = !b;
    ans = ans + (b << 3);
    x >>= (!b) << 3;   

    b = (x >> 4) & 15;
    b = (b + 1) & 15;
    b = !b;
    ans = ans + (b << 2);
    x >>= (!b) << 2;  

    b = (x >> 2) & 3;
    b = (b + 1) & 3;
    b = !b;
    ans = ans + (b << 1);
    x >>= (!b) << 1;

    b = (x >> 1) & 1;
    b = (b + 1) & 1;
    b = !b;
    ans = ans + (b);
    x >>= (!b);

    ans += x & 1;
    return ans;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned int ans = 0;

    if (x == -2147483648)
        return 0xcf000000u; 
    if (! x)
        return 0u;

    if (x < 0) {
        ans = 2147483648u;
        x = -x;
    }
        
    int h = 0;
    for (int i = 0; i < 31; i ++)
        if (x >> i)
            h = i;
    x -= (1 << h);
        
    ans |= (h + 127) << 23;

    if (h < 24) {
        ans |= x << (23 - h);
    } else {
        int p = h - 23;
        ans |= x >> p;
        unsigned msk = (1u << p) - 1;
        x &= msk;
        p --;
        p = 1 << p;
        if (x > p)
            ans += 1;
        else if (x == p) {
            ans += ans & 1;
        }
    }

    return ans;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 255u;
    if (exp == 255)
        return uf;
    int b = uf & 8388607u;
    if (exp == 0) {
        if (b < (1 << 22))
            return uf + b;
        return ((uf & 4286578688u) + (b << 1 & 8388607u) + (1u << 23));
    } else if (exp == 254) {
        return (uf + (1u << 23)) & 4286578688u;
    } 

    return uf + (1u << 23);        
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned exp = (uf2 >> 20) & 2047u;
    if (exp >= 1054)
        return 0x80000000;
    if (exp < 1023)
        return 0;
    exp -= 1023;
    unsigned ans = (uf2 & 1048575u) + (1u << 20);
    if (exp <= 20)
        ans >>= (20 - exp);
    else {
        ans <<= (exp - 20);
        ans |= uf1 >> (52 - exp);
    }

    if (uf2 >> 31)
        return -ans;
    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127)
        return 2139095040u;
    
    if (x < -149)
        return 0u;

    if (x < -126)
        return 1u << (x + 149);

    return (x + 127) << 23;
}
