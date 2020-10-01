#include "fixedpoint.h"
#include "tables.h"

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

    if (((a ^ b) & MIN_VAL_32))
    {
        c = saturation32(&c, &a);
    }

    return c;
}

my_sint64 add64(const my_sint64 a, const my_sint64 b)
{
    my_sint64 c;

    c = a + b;

    if (((a ^ b) & MIN_VAL_64) == 0)     //case for both positive or negative numbers
    {
        c = saturation64(&c, &a);
    }

    return c;   // positive + negative always returns right result
}

my_sint64 sub64(const my_sint64 a, const my_sint64 b)
{
    my_sint64 c;

    c = a - b;

    if (((a ^ b) & MIN_VAL_64))
    {
        c = saturation64(&c, &a);
    }

    return c;
}

my_sint32 mul32(const my_sint32 a, const my_sint32 b)
{
    my_sint64 acc;
    my_sint64 prod = 0;
    my_sint32 c;
    my_sint32 mul_1 = a;
    my_sint32 mul_2 = b;

    prod = (my_sint64)a * (my_sint64)b;
    prod = prod << 1;
    acc = prod + (my_sint64)ROUNDING_BIT_32; // rounding bit

    if (((prod ^ (my_sint64)MAX_VAL_32) & MIN_VAL_64) == 0) //
    {
        acc = saturation64(&acc, &prod);
    }

    c = (my_sint32)(acc >> FRACTION_BASE+1);

    return c;
}


my_sint64 mul64(const my_sint64 a, const my_sint64 b)
{
    my_sint64 prod ;
 
    prod = a * b;

    prod = prod >> ESTIMATE_Q20;

    return prod;
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

/****************************************************
*
*           DIVISION, LOG2, POW2, POW
*
*****************************************************/

my_sint32 div32(const my_sint32 numenator, const my_sint32 denuminator)
{
    my_uint32 i;
    my_uint32 ret;

    my_sint64 var_mul;
    my_sint64 var_sub;
    my_sint64 estimate;

    my_sint64 new_denum = denuminator;                              // Q31 denuminator in 64 bit integer;
    my_sint64 new_num = numenator;

    new_denum = new_denum >> (FRACTION_BASE - ESTIMATE_Q20);        // Q20 denuminator in 64 integer
    new_num = new_num >> (FRACTION_BASE - ESTIMATE_Q20);            // >> (31 - 20)
    estimate = ESTIMATE_VAL;                                        // ESTIMATE_VAL = 0x80000

    for (i = 0; i < 7; i++)
    {
        /*  x(n+1) = x(n) + x(n) * (1 - (denumenator * x(n))) */

        var_mul = mul64(new_denum, estimate);     //  denumenator * x(n)
        var_sub = sub64((my_sint32)ONE, var_mul);   //  1 - (denumenator * x(n))
        var_mul = mul64(estimate, var_sub);         //  x(n) * (1 - (denumenator * x(n)))
        estimate = add64(estimate, var_mul);        //  x(n + 1) = x(n) + x(n) * (1 - (denumenator * x(n)))
    }

    estimate = mul64(new_num, estimate);

    ret = estimate << (FRACTION_BASE - ESTIMATE_Q20);

    return ret;
}

my_float div_f(const my_float numenator, const my_float denuminator)
{
    my_float result = numenator / denuminator;
    return result;
}


my_sint32 log2x(my_sint32 a)
{
    my_sint32 new_a;

    new_a = a >> 4;

}
