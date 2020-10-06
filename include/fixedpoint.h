#include <stdint.h>
#include <stdio.h>
#include "math.h"

#define MAX_VAL_8       127
#define MIN_VAL_8       -128

#define MAX_VAL_16      32767
#define MIN_VAL_16      -32768

#define MAX_VAL_32      2147483647
#define MIN_VAL_32      -2147483648

#define MAX_VAL_64      9223372036854775807
#define MIN_VAL_64      -9223372036854775808

#define FRACTION_BASE   31
#define ESTIMATE_Q20    20
#define LOG_BASE        26
#define LOG_IDX_OFFSET  22
#define POW_IDX_OFFSET  22
#define POW_BASE        26

#define Q31_TO_Q26      5

#define Q20_SHIFT       11

#define EMPTY_MASK      0x00000000
#define T1              2.823529
#define T2              1.882352
#define NORM_FACTOR     0.15195522
#define ESTIMATE_VAL    0x80000
#define ONE             0xFFFFF
#define ROUNDING_BIT_32 0x80000000
#define ROUNDING_BIT_64 0x80000000

typedef unsigned char           my_uint8;
typedef unsigned short          my_uint16;
typedef unsigned int            my_uint32;
typedef unsigned long int       my_uint64;

typedef signed char             my_sint8;
typedef signed short            my_sint16;
typedef signed int              my_sint32;
typedef signed long long int    my_sint64;

typedef float                   my_float;


my_sint32 add32(const my_sint32 a, const my_sint32 b);
my_sint32 sub32(const my_sint32 a, const my_sint32 b);
my_sint32 mul32(const my_sint32 a, const my_sint32 b);
my_sint64 mac32(const my_sint32 a, const my_sint32 b, my_sint64 c);
my_sint64 msub32(const my_sint32 a, const my_sint32 b, my_sint64 c);
my_sint32 abs32(const my_sint32 a);
my_sint32 neg32(const my_sint32 a);
my_sint32 lsh32(const my_sint32 a, const my_sint32 b);
my_sint32 rsh32(const my_sint32 a, const my_sint32 b);
my_sint32 div32(const my_sint32 numenator, const my_sint32 denuminator);

my_sint64 add64(const my_sint64 a, const my_sint64 b);
my_sint64 sub64(const my_sint64 a, const my_sint64 b);
my_sint64 mul64(const my_sint64 a, const my_sint64 b, const my_sint64 shift);

my_sint32 saturation32(my_sint32* sum, my_sint32* term);
my_sint64 saturation64(my_sint64* sum, my_sint64* term);

my_uint32 float_To_Fixed(my_float floatNum, my_uint8 shift);
my_float fixed_To_Float(my_uint32 fixedNum, my_uint8 shift);

my_float add_f(const my_float a, const my_float b);
my_float sub_f(const my_float a, const my_float b);
my_float mul_f(const my_float a, const my_float b);
my_float mac_f(const my_float a, const my_float b, const my_float c);
my_float msub_f(const my_float a, const my_float b, const my_float c);
my_float abs_f(const my_float a);
my_float neg_f(const my_float a);
my_float div_f(const my_float numenator, const my_float denuminator);

my_sint32 log2x(my_sint32 a);
my_sint32 pow2x(my_sint32 a);
my_sint32 my_pow(my_sint32 a, my_sint32 x);
