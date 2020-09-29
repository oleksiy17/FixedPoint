#include "fixedpoint.h"

/****************************************************
*
*           FIXED POINT MATH OPERATIONS
*
*****************************************************/

my_sint32 add32(const my_sint32 a, const my_sint32 b)
{
    my_sint32 c;

    c = a + b;

    if (((a ^ b) & MIN_VAL_32) == 0)     //case for both positive or negative numbers
    {
        c = saturation32(&c, &a);
    }   

    return c;   // positive + negative always returns right result
}

my_sint32 sub32(const my_sint32 a, const my_sint32 b)
{
    my_sint32 c;
    
    c = a - b;

    if (((a ^ b) & MIN_VAL_32) == 1)
    {
        c = saturation32(&c, &a);
    }

    return c;
}


my_sint32 mul32(const my_sint32 a, const my_sint32 b)
{
    my_sint64 acc;
    my_sint64 prod;
    my_sint32 c;

    prod = (my_sint64)a * (my_sint64)b;
    prod = prod << 1;
    acc = prod + (my_sint64)MAX_VAL_32; 

    if (((prod ^ (my_sint64)MAX_VAL_32) & MIN_VAL_64) == 0)
    {
        acc = saturation64(&acc, &prod);
    }

    c = (my_sint32)(acc >> FRACTION_BASE);

    return c;
}

my_sint64 mac32(const my_sint32 a, const my_sint32 b, const my_sint64 c)
{
    my_sint64 acc;
    my_sint64 sum;

    acc = (my_sint64)a * (my_sint64)b;
    sum = acc + c;

    if (((acc ^ c) & MIN_VAL_64) == 0)
    {
        sum = saturation64(&sum, &acc);
    }

    return sum;
}

my_sint64 msub32(const my_sint32 a, const my_sint32 b, const my_sint64 c)
{
    my_sint64 acc;
    my_sint64 dif;

    acc = (my_sint64)a * (my_sint64)b;
    dif = acc - c;

    if (((acc ^ c) & MIN_VAL_64) == 1)
    {
        dif = saturation64(&dif, &acc);
    }

    return dif;
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
                c = MAX_VAL_32;
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

    if (b == MIN_VAL_32)
    {
        b = MAX_VAL_32;
    }

    if (b & MIN_VAL_32)
    {
        b *=(-1);
    }

    return b;
}

my_sint32 neg32(const my_sint32 a)
{
    my_sint32 b;

    b = a;

    if (b & MIN_VAL_8)
    {
        return b;
    }
    else
    {
        b = (b ^ 0xFF) + 1;                 // обратный код
        return b;
    } 
}

/****************************************************
*
*                SATURATION HANDLER
*
*****************************************************/

my_sint32 saturation32(my_sint32* sum, my_sint32* term)
{
    if ((*sum ^ *term) & MIN_VAL_32)
    {
        if (*term < 0)
        {
            *sum = MIN_VAL_32;
        }
        else
        {
            *sum = MAX_VAL_32;
        }
    }

    return *sum;
}

my_sint64 saturation64(my_sint64* sum, my_sint64* term)
{
    if ((*sum ^ *term) & MIN_VAL_64)
    {
        if (*term < 0)
        {
            *sum = MIN_VAL_64;
        }
        else
        {
            *sum = MAX_VAL_64;
        }
    }

    return *sum;
}

/****************************************************
*
*               DATA TYPES CONVERSION
*
*****************************************************/

my_sint32 float_To_Fixed(float floatNum)
{
    return (my_sint32)(floatNum * (1u << FRACTION_BASE));
}


my_float fixed_To_Float(my_sint32 fixedNum)
{
    return ((my_float)fixedNum / (my_float)(1u << FRACTION_BASE));
}


/****************************************************
*
*           FLOAT POINT MATH OPERATIONS
*
*****************************************************/

my_float add_f(const my_float a, const my_float b)
{
    return (a + b);
}


my_float sub_f(const my_float a, const my_float b)
{
    return (a - b);
}


my_float mul_f(const my_float a, const my_float b)
{
    return (a * b);
}


my_float mac_f(const my_float a, const my_float b, const my_float c)
{
    return (a * b) + c;
}


my_float msub_f(const my_float a, const my_float b, const my_float c)
{
    return (a * b) - c;
}


my_float abs_f(const my_float a)
{
    return ((a < 0) ? -a : a);
}


my_float neg_f(const my_float a)
{
    return ((a < 0) ? a : -a);
}
