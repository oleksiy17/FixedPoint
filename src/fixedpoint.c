#include "fixedpoint.h"
#include "math.h"

my_sint32 add8_fp(const my_sint32 a, const my_sint32 b)
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

my_sint32 sub8_fp(const my_sint32 a, const my_sint32 b)
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


my_sint32 mul8_fp(const my_sint32 a, const my_sint32 b)
{
    my_sint64 acc;
    my_sint32 c;

    acc = (my_sint64)a * (my_sint64)b;
    acc = acc << 1;
    acc += 0x80000000;
    
    c = (my_sint32)(acc >> 8);

    return c;
}

my_sint32 abs8(const my_sint32 a)
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

my_sint32 neg8_fp(const my_sint32 a)
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