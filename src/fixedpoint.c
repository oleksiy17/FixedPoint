#include "fixedpoint.h"
#include "math.h"

my_sint32 add32_fp(const my_sint32 a, const my_sint32 b)
{
    my_sint32 c;

    c = a + b;

    if (((a ^ b) & MIN_VAL_8) == 0)     //case for both positive or negative numbers
    {
        if ((c ^ a) & MIN_VAL_8)
        {
            if (a < 0)
            {
                c = MIN_VAL_8;
            }
            else
            {
                c = MAX_VAL_8;
            }
        }
    }   

    return c;   // positive + negative always returns right result
}

my_sint32 sub32_fp(const my_sint32 a, const my_sint32 b)
{
    my_sint32 c;
    
    c = a - b;

    if (((a ^ b) & MIN_VAL_8))
    {
        if ((c ^ a) & MIN_VAL_8)
        {
            if (a < 0)
            {
                c = MIN_VAL_8;
            }
            else
            {
                c = MAX_VAL_8;
            }
        }
    }
    return c;
}


my_sint32 mul32_fp(const my_sint32 a, const my_sint32 b)
{
    my_sint64 acc;
    my_sint32 c;

    acc = (my_sint64)a * (my_sint64)b;
    acc = acc << 1;
    acc += 0x80000000;
    
    c = (my_sint32)(acc >> FRACTION_BASE);

    return c;
}

my_sint64 mac32(const my_sint32 a, const my_sint32 b, my_sint64 c)
{
    c = c + ((my_sint64)a * (my_sint64)b);

    return c;
}

my_sint64 msub32(const my_sint32 a, const my_sint32 b, my_sint64 c)
{
    c = c - ((my_sint64)a * (my_sint64)b);

    return c;
}


my_sint32 lsh32(const my_sint32 a, const my_sint32 b)
{
    my_sint32 c;
    c = 0;

    if (a & MIN_VAL_32)     //case for negative numbers
    {
        c = a << b;
        c = c | MIN_VAL_32;     // always add a sign bit
    }

    if (((a & MIN_VAL_32) == 0))    // case for positive numbers
    {
        if (a | EMPTY_MASK)         // if number is 0 return 0 and skip calculation
        {
            c = a << b;
            
            if ((c & MIN_VAL_32) | (c | EMPTY_MASK))     //check if sign was changed or all "1" was shifted 
            {
                c = 0x7FFFFFFF;
            }
        }
    }

    return c;
}


my_sint32 rsh32(const my_sint32 a, const my_sint32 b)
{
    my_uint32 i;
    my_sint32 c;
    c = 0;

    if (a & MIN_VAL_32)
    {
        for (i = 0; i < b; i++)
        {
            c = a >> 1;
            c = c | MIN_VAL_32;
        }
    }

    c = a >> b;

    return c;
}

my_sint32 abs32(const my_sint32 a)
{
    my_sint32 b;

    b = a;

    if (b == MIN_VAL_8)
    {
        b = MAX_VAL_8;
    }

    if (b & MIN_VAL_8)
    {
        b *=(-1);
    }

    return b;
}

my_sint32 neg32_fp(const my_sint32 a)
{
    my_sint32 b;

    b = a;

    if (b & MIN_VAL_8)
    {
        return b;
    }
    else
    {
        b = (b ^ 0xFF) + 1;
        return b;
    } 
}

my_sint32 log2_fp(const my_sint32 a)
{

}



my_float mul8_f(const my_float a, const my_float b)
{
    float acc;

}