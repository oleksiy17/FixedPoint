#include "fixedpoint.h"
#include "math.h"
#
int main()
{
    my_float a = 0.456;
    my_float x = 0.456;

    printf("log2(%f) = %f\n", a, log2f(a));

    my_sint32 b = float_To_Fixed(a, FRACTION_BASE);
    printf("%f %d\n", a, b);

    my_uint32 logor = log2x(b);
    printf("log2x(%f) = %f\n", a, fixed_To_Float(logor, LOG_BASE));
    
    my_sint32 pawer = pow2x(logor);
    printf("Pawer: %d %f\n", pawer, fixed_To_Float(pawer, FRACTION_BASE));


    my_sint32 result = my_pow(float_To_Fixed(a, FRACTION_BASE), float_To_Fixed(x, FRACTION_BASE));
    printf("result = %f", fixed_To_Float(result, FRACTION_BASE));

    return 0;
}

