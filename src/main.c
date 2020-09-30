#include "fixedpoint.h"
#include "math.h"
#
int main()
{
    /*my_uint32 mul1;
    my_uint32 mul2;
    my_uint32 prod;

    my_float flmul1;
    my_float flmul2;

    printf("int: %d\n", sizeof(my_uint32));
    printf("long int: %d\n", sizeof(my_sint64));
    flmul1 = 0.5;
    flmul2 = 0.5;
    printf("float add: %f * %f = %10f\n\n", flmul1, flmul2, mul_f(flmul1, flmul2));

    mul1 = float_To_Fixed(flmul1);
    mul2 = float_To_Fixed(flmul2);

    prod = mul32(mul1, mul2);
    printf("fixed add: %f * %f = %10f\n\n", flmul1, flmul2, fixed_To_Float(prod));
    */

    my_float a = 0.3;
    my_float b = 0.8;
    my_float c = a / b;

    //printf("Float %f / %f = %f\n", a, b, c);

    my_sint32 af = float_To_Fixed(a);
    my_sint32 bf = float_To_Fixed(b);
    my_sint32 cf = div32(af, bf);


    printf("Fixed %f / %f = %f\n", a, b, fixed_To_Float(cf));

    /*my_float sub1 = -0.8                                                                                                                      ;
    my_float sub2 = -0.7;
    my_float result = (sub1 - sub2);

    printf("Float sub %f - %f = %f\n\n", sub1, sub2, result);

    my_sint32 fsub1 = float_To_Fixed(sub1);
    my_sint32 fsub2 = float_To_Fixed(sub2);
    my_sint32 fresult = sub32(fsub1, fsub2);

    printf("Fixed sub %f - %f = %10f\n\n", sub1, sub2, fixed_To_Float(fresult));*/

    return 0;

}