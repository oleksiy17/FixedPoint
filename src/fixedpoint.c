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

    prod = (my_sint64)a * (my_sint64)b;
    prod = prod << 1;
    acc = prod + (my_sint64)ROUNDING_BIT_32; // rounding bit

    if (((prod ^ (my_sint64)MAX_VAL_32) & MIN_VAL_64) == 0) //
    {
        acc = saturation64(&acc, &prod);
    }

    c = (my_sint32)(acc >> FRACTION_BASE + 1);

    return c;
}


my_sint64 mul64(const my_sint64 a, const my_sint64 b, const my_sint64 shift)
{
    my_sint64 prod;

    prod = a * b;

    prod = prod >> shift;

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
            
            if ((c & MIN_VAL_32) | (c & EMPTY_MASK))     //check if sign was changed or all "1" was shifted 
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

my_sint32 float_To_Fixed(float floatNum, my_uint8 shift)
{
    return (my_sint32)(floatNum * (1u << shift));
}


my_float fixed_To_Float(my_sint32 fixedNum, my_uint8 shift)
{
    return ((my_float)fixedNum / (my_float)(1u << shift));
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

        var_mul = mul64(new_denum, estimate, (my_sint64)ESTIMATE_Q20);     //  denumenator * x(n)
        var_sub = sub64((my_sint32)ONE, var_mul);   //  1 - (denumenator * x(n))
        var_mul = mul64(estimate, var_sub, (my_sint64)ESTIMATE_Q20);         //  x(n) * (1 - (denumenator * x(n)))
        estimate = add64(estimate, var_mul);        //  x(n + 1) = x(n) + x(n) * (1 - (denumenator * x(n)))
    }

    estimate = mul64(new_num, estimate, (my_sint64)ESTIMATE_Q20);

    ret = estimate << (FRACTION_BASE - ESTIMATE_Q20);

    return ret;
}

my_float div_f(const my_float numenator, const my_float denuminator)
{
    my_float result = numenator / denuminator;
    return result;
}


my_sint32 log2x(my_sint32 a)    // Input parameter in Q31
{
    my_sint32 Idx;          // may be a structure
    my_sint32 units;
    my_sint32 arr_dif;
    my_sint64 delta;
    my_sint32 result;

    Idx     = rsh32(a, (my_sint32)LOG_IDX_OFFSET);                              //  Find index of array by shifting right log value by 22
    units   = sub32(a, (my_uint32)lsh32(Idx, (my_sint32)LOG_IDX_OFFSET));       //  Find difference betveen number of units in given value and a nearest array value
    arr_dif = sub32(arr_log[Idx + 1], arr_log[Idx]);                            //  Find difference in nearest array values
    delta   = mul64((my_sint64)arr_dif, (my_sint64)units, (my_sint64)LOG_IDX_OFFSET);      //  Myltiplie number of units in given range on given range and divide it to total amount of units in range( shift right by 22 )
    result  = add32((my_sint32)delta, arr_log[Idx]);                            //  Add finded delta to nearest array value to complete interpolation

    return result;      //returning Q5.26 format
}

my_sint32 pow2x(my_sint32 a)            //input parameter in Q5.26
{
    my_sint32 Idx;
    my_sint32 units;
    my_sint32 arr_dif;
    my_sint64 delta;
    my_sint32 result;

    Idx   = rsh32(a, (my_sint32)POW_IDX_OFFSET);
    units = sub32(a, (my_uint32)lsh32(Idx, (my_sint32)POW_IDX_OFFSET));
    Idx   = -Idx;
    arr_dif = sub32(arr_pow[Idx], arr_pow[Idx + 1]);
    delta = mul64((my_sint64)arr_dif, (my_sint64)units, (my_sint64)POW_IDX_OFFSET);
    result = add32((my_sint32)delta, arr_pow[Idx]);
    
    return result;
}


my_sint32 my_pow(my_sint32 a, my_sint32 x)
{
    my_sint64 logRetVal;
    my_sint64 powProd;
    my_sint32 result;

    logRetVal = (my_sint64)log2x(a);
    powProd = mul64((my_sint64)logRetVal, (my_sint64)(rsh32(x, Q31_TO_Q26)) , (my_sint64)POW_BASE);
    result = (my_sint32)pow2x((my_sint32)powProd);

    return result;
}


