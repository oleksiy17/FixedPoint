#include <stdint.h>
#include <stdio.h>

#define MAX_VAL_8       127
#define MIN_VAL_8       -128

#define MAX_VAL_16      32767
#define MIN_VAL_16      -32768

#define MAX_VAL_32      2147483647
#define MIN_VAL_32      -2147483648

#define MAX_VAL_64      9223372036854775807
#define MIN_VAL_64      -9223372036854775808

typedef unsigned char           my_uint8;
typedef unsigned short          my_uint16;
typedef unsigned int            my_uint32;
typedef unsigned long int       my_uint64;

typedef signed char             my_sint8;
typedef signed short            my_sint16;
typedef signed int              my_sint32;
typedef signed long int         my_sint64;

typedef float                   my_float;


my_sint32 add8(const my_sint32 a, const my_sint32 b);
my_sint32 sub8(const my_sint32 a, const my_sint32 b);
my_sint32 mul8(const my_sint32 a, const my_sint32 b);
my_sint32 abs8(const my_sint32 a);
my_sint32 neg8(const my_sint32 a);
my_sint32 log2_fp(const my_sint32 a);





my_float add8_f(const my_float a, const my_float b);
my_float sub8_f(const my_float a, const my_float b);
my_float mul8_f(const my_float a, const my_float b);

my_float abs8_f(const my_float a);

my_float neg8_f(const my_float a);